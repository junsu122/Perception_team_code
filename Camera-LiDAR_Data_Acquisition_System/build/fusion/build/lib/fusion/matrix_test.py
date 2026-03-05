#!/usr/bin/env python3



import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseStamped, Pose
import numpy as np
import array
from collections import namedtuple
import sys
from typing import Iterable, List, NamedTuple, Optional

import numpy as np
try:
    from numpy.lib.recfunctions import (structured_to_unstructured, unstructured_to_structured)
except ImportError:
    from sensor_msgs_py.numpy_compat import (structured_to_unstructured,
                                             unstructured_to_structured)

from sensor_msgs.msg import PointCloud2, PointField
from std_msgs.msg import Header


_DATATYPES = {}
_DATATYPES[PointField.INT8] = np.dtype(np.int8)
_DATATYPES[PointField.UINT8] = np.dtype(np.uint8)
_DATATYPES[PointField.INT16] = np.dtype(np.int16)
_DATATYPES[PointField.UINT16] = np.dtype(np.uint16)
_DATATYPES[PointField.INT32] = np.dtype(np.int32)
_DATATYPES[PointField.UINT32] = np.dtype(np.uint32)
_DATATYPES[PointField.FLOAT32] = np.dtype(np.float32)
_DATATYPES[PointField.FLOAT64] = np.dtype(np.float64)

DUMMY_FIELD_PREFIX = 'unnamed_field'



def inverse(matrix):
    return np.linalg.pinv(matrix)

def read_points(
        cloud: PointCloud2,
        field_names: Optional[List[str]] = None,
        skip_nans: bool = False,
        uvs: Optional[Iterable] = None,
        reshape_organized_cloud: bool = False) -> np.ndarray:
    """
    Read points from a sensor_msgs.PointCloud2 message.

    :param cloud: The point cloud to read from sensor_msgs.PointCloud2.
    :param field_names: The names of fields to read. If None, read all fields.
                        (Type: Iterable, Default: None)
    :param skip_nans: If True, then don't return any point with a NaN value.
                      (Type: Bool, Default: False)
    :param uvs: If specified, then only return the points at the given
        coordinates. (Type: Iterable, Default: None)
    :param reshape_organized_cloud: Returns the array as an 2D organized point cloud if set.
    :return: Structured NumPy array containing all points.
    """
    assert isinstance(cloud, PointCloud2), \
        'Cloud is not a sensor_msgs.msg.PointCloud2'

    # Cast bytes to numpy array
    points = np.ndarray(
        shape=(cloud.width * cloud.height, ),
        dtype=dtype_from_fields(cloud.fields, point_step=cloud.point_step),
        buffer=cloud.data)

    # Keep only the requested fields
    if field_names is not None:
        assert all(field_name in points.dtype.names for field_name in field_names), \
            'Requests field is not in the fields of the PointCloud!'
        # Mask fields
        points = points[list(field_names)]

    # Swap array if byte order does not match
    if bool(sys.byteorder != 'little') != bool(cloud.is_bigendian):
        points = points.byteswap(inplace=True)

    # Check if we want to drop points with nan values
    if skip_nans and not cloud.is_dense:
        # Init mask which selects all points
        not_nan_mask = np.ones(len(points), dtype=bool)
        for field_name in points.dtype.names:
            # Only keep points without any non values in the mask
            not_nan_mask = np.logical_and(
                not_nan_mask, ~np.isnan(points[field_name]))
        # Select these points
        points = points[not_nan_mask]

    # Select points indexed by the uvs field
    if uvs is not None:
        # Don't convert to numpy array if it is already one
        if not isinstance(uvs, np.ndarray):
            uvs = np.fromiter(uvs, int)
        # Index requested points
        points = points[uvs]

    # Cast into 2d array if cloud is 'organized'
    if reshape_organized_cloud and cloud.height > 1:
        points = points.reshape(cloud.width, cloud.height)

    return points


def read_points_numpy(
        cloud: PointCloud2,
        field_names: Optional[List[str]] = None,
        skip_nans: bool = False,
        uvs: Optional[Iterable] = None,
        reshape_organized_cloud: bool = False) -> np.ndarray:
    """
    Read equally typed fields from sensor_msgs.PointCloud2 message as a unstructured numpy array.

    This method is better suited if one wants to perform math operations
    on e.g. all x,y,z fields.
    But it is limited to fields with the same dtype as unstructured numpy arrays
    only contain one dtype.

    :param cloud: The point cloud to read from sensor_msgs.PointCloud2.
    :param field_names: The names of fields to read. If None, read all fields.
                        (Type: Iterable, Default: None)
    :param skip_nans: If True, then don't return any point with a NaN value.
                      (Type: Bool, Default: False)
    :param uvs: If specified, then only return the points at the given
        coordinates. (Type: Iterable, Default: None)
    :param reshape_organized_cloud: Returns the array as an 2D organized point cloud if set.
    :return: Numpy array containing all points.
    """
    assert all(cloud.fields[0].datatype == field.datatype for field in cloud.fields[1:]
               if field_names is None or field.name in field_names), \
        'All fields need to have the same datatype. Use `read_points()` otherwise.'
    structured_numpy_array = read_points(
        cloud, field_names, skip_nans, uvs, reshape_organized_cloud)
    return structured_to_unstructured(structured_numpy_array)


def read_points_list(
        cloud: PointCloud2,
        field_names: Optional[List[str]] = None,
        skip_nans: bool = False,
        uvs: Optional[Iterable] = None) -> List[NamedTuple]:
    """
    Read points from a sensor_msgs.PointCloud2 message.

    This function returns a list of namedtuples. It operates on top of the
    read_points method. For more efficient access use read_points directly.

    :param cloud: The point cloud to read from. (Type: sensor_msgs.PointCloud2)
    :param field_names: The names of fields to read. If None, read all fields.
                        (Type: Iterable, Default: None)
    :param skip_nans: If True, then don't return any point with a NaN value.
                      (Type: Bool, Default: False)
    :param uvs: If specified, then only return the points at the given
                coordinates. (Type: Iterable, Default: None]
    :return: List of namedtuples containing the values for each point
    """
    assert isinstance(cloud, PointCloud2), \
        'cloud is not a sensor_msgs.msg.PointCloud2'

    if field_names is None:
        field_names = [f.name for f in cloud.fields]

    Point = namedtuple('Point', field_names)

    return [Point._make(p) for p in read_points(cloud, field_names,
                                                skip_nans, uvs)]


def dtype_from_fields(fields: Iterable[PointField], point_step: Optional[int] = None) -> np.dtype:
    """
    Convert a Iterable of sensor_msgs.msg.PointField messages to a np.dtype.

    :param fields: The point cloud fields.
                   (Type: iterable of sensor_msgs.msg.PointField)
    :param point_step: Point step size in bytes. Calculated from the given fields by default.
                       (Type: optional of integer)
    :returns: NumPy datatype
    """
    # Create a lists containing the names, offsets and datatypes of all fields
    field_names = []
    field_offsets = []
    field_datatypes = []
    for i, field in enumerate(fields):
        # Datatype as numpy datatype
        datatype = _DATATYPES[field.datatype]
        # Name field
        if field.name == '':
            name = f'{DUMMY_FIELD_PREFIX}_{i}'
        else:
            name = field.name
        # Handle fields with count > 1 by creating subfields with a suffix consiting
        # of "_" followed by the subfield counter [0 -> (count - 1)]
        assert field.count > 0, "Can't process fields with count = 0."
        for a in range(field.count):
            # Add suffix if we have multiple subfields
            if field.count > 1:
                subfield_name = f'{name}_{a}'
            else:
                subfield_name = name
            assert subfield_name not in field_names, 'Duplicate field names are not allowed!'
            field_names.append(subfield_name)
            # Create new offset that includes subfields
            field_offsets.append(field.offset + a * datatype.itemsize)
            field_datatypes.append(datatype.str)

    # Create dtype
    dtype_dict = {
            'names': field_names,
            'formats': field_datatypes,
            'offsets': field_offsets
    }
    if point_step is not None:
        dtype_dict['itemsize'] = point_step
    return np.dtype(dtype_dict)


def create_cloud(
        header: Header,
        fields: Iterable[PointField],
        points: Iterable,
        point_step: Optional[int] = None) -> PointCloud2:
    """
    Create a sensor_msgs.msg.PointCloud2 message.

    :param header: The point cloud header. (Type: std_msgs.msg.Header)
    :param fields: The point cloud fields.
                   (Type: iterable of sensor_msgs.msg.PointField)
    :param points: The point cloud points. List of iterables, i.e. one iterable
                   for each point, with the elements of each iterable being the
                   values of the fields for that point (in the same order as
                   the fields parameter)
    :param point_step: Point step size in bytes. Calculated from the given fields by default.
                       (Type: optional of integer)
    :return: The point cloud as sensor_msgs.msg.PointCloud2
    """
    # Check if input is numpy array
    if isinstance(points, np.ndarray):
        # Check if this is an unstructured array
        if points.dtype.names is None:
            assert all(fields[0].datatype == field.datatype for field in fields[1:]), \
                'All fields need to have the same datatype. Pass a structured NumPy array \
                    with multiple dtypes otherwise.'
            # Convert unstructured to structured array
            points = unstructured_to_structured(
                points,
                dtype=dtype_from_fields(fields, point_step))
        else:
            assert points.dtype == dtype_from_fields(fields, point_step), \
                'PointFields and structured NumPy array dtype do not match for all fields! \
                    Check their field order, names and types.'
    else:
        # Cast python objects to structured NumPy array (slow)
        points = np.array(
            # Points need to be tuples in the structured array
            list(map(tuple, points)),
            dtype=dtype_from_fields(fields, point_step))

    # Handle organized clouds
    assert len(points.shape) <= 2, \
        'Too many dimensions for organized cloud! \
            Points can only be organized in max. two dimensional space'
    height = 1
    width = points.shape[0]
    # Check if input points are an organized cloud (2D array of points)
    if len(points.shape) == 2:
        height = points.shape[1]

    # Convert numpy points to array.array
    memory_view = memoryview(points)
    casted = memory_view.cast('B')
    array_array = array.array('B')
    array_array.frombytes(casted)

    # Put everything together
    cloud = PointCloud2(
        header=header,
        height=height,
        width=width,
        is_dense=False,
        is_bigendian=sys.byteorder != 'little',
        fields=fields,
        point_step=points.dtype.itemsize,
        row_step=(points.dtype.itemsize * width))
    # Set cloud via property instead of the constructor because of the bug described in
    # https://github.com/ros2/common_interfaces/issues/176
    cloud.data = array_array
    return cloud


def create_cloud_xyz32(header: Header, points: Iterable) -> PointCloud2:
    """
    Create a sensor_msgs.msg.PointCloud2 message with (x, y, z) fields.

    :param header: The point cloud header. (Type: std_msgs.msg.Header)
    :param points: The point cloud points. (Type: Iterable)
    :return: The point cloud as sensor_msgs.msg.PointCloud2.
    """
    fields = [PointField(name='x', offset=0,
                         datatype=PointField.FLOAT32, count=1),
              PointField(name='y', offset=4,
                         datatype=PointField.FLOAT32, count=1),
              PointField(name='z', offset=8,
                         datatype=PointField.FLOAT32, count=1)]
    return create_cloud(header, fields, points)

########################################Main code here#################################################################################################

class FusionTest(Node):
    def __init__(self):
        super().__init__('matrix_test')
        self.lidar_subscription = self.create_subscription(
            PointCloud2,
            '/velodyne_points',
            # 'cropbox_filtered',
            self.lidar_callback,
            10
        )

        self.coord_pub = self.create_publisher(PointCloud2, 'transformed_points', 10)

        self. vel_list = [] 
        self. RTlc = np.array([[0.0000000,  -1.0000000,  0.0000000,  0.65182369], 
                                [ 0.0000000,  0.0000000,  -1.0000000 , 0.01996529], 
                                [ 1.0000000, 0.0000000,  0.0000000, -10.20860643],
                                [0.,0.,0.,1.]])
        
        #camera matrix
        self.Mc = np.array([[484.112610, 0.000000, 302.908797,0.],
                           [0.000000, 488.804047, 268.598022,0.],  
                           [0.000000, 0.000000, 1.000000,0.]]) 


    def lidar_callback(self,msg):
        scale = 5.2
        self.camera_points_1 = np.array([0,0,1]) #real_points
        self.camera_points_2 = np.array([0,480,1])
        self.camera_points_3 = np.array([640,0,1])
        self.camera_points_4 = np.array([640,480,1])
        self.camera_points_5 = np.array([152,281,1])

        camera_points = [self.camera_points_1, self.camera_points_2, self.camera_points_3, self.camera_points_4, self.camera_points_5]
        transformed_points = []
        for camera_point in camera_points:
            res = np.dot(inverse(self.RTlc), np.dot(inverse(self.Mc),camera_point.T))
            #transformed camera points (3d points)
            real_x = scale*res[0]
            real_y = scale*res[1]
            real_z = scale*res[2]
            print(real_x,real_y,real_z)
            
            transformed_point = np.array([real_x,real_y,real_z])
            transformed_points.append(transformed_point)
            # transformed_points = np.concatenate((transformed_points,(np.array([real_x,real_y,real_z]))),axis=0)


        # publish PointCloud2 msg
        header = msg.header
        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        # create PointCloud2 msg
        transformed_points_msg = create_cloud(header, fields, transformed_points)

        # publish transformed points
        self.coord_pub.publish(transformed_points_msg)


    
def main(args = None):
    rclpy.init(args=args)
    node = FusionTest()

    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()



