import numpy as np

def pixel_to_image_plane(u, v, camera_matrix):
    # Pixel coordinates in homogeneous form
    pixel_coordinates = np.array([u, v, 1])

    # Inverse of the camera matrix
    K_inv = np.linalg.inv(camera_matrix)

    # Project pixel coordinates to NDC (ignoring depth)
    ndc_coordinates = np.dot(K_inv, pixel_coordinates)

    # Image plane coordinates
    x = ndc_coordinates[0] / ndc_coordinates[2]
    y = ndc_coordinates[1] / ndc_coordinates[2]

    return x, y

# Example usage
# pixel_u = 320  # example pixel u-coordinate
# pixel_v = 240  # example pixel v-coordinate
# focal_length_x = 500.0  # example focal length in x-direction
# focal_length_y = 500.0  # example focal length in y-direction
# principal_point_x = 320.0  # example principal point in x-direction
# principal_point_y = 240.0  # example principal point in y-direction

# Camera matrix
camera_matrix = np.array([[484.112610, 0.000000, 302.908797],
                           [0.000000, 488.804047, 268.598022],
                           [0.000000, 0.000000, 1.000000]]) 

# Convert pixel to image plane coordinates (ignoring depth)
image_plane_coordinates = pixel_to_image_plane(127,176, camera_matrix)

# print("Pixel coordinates:", (pixel_u, pixel_v))
print("Image plane coordinates (ignoring depth):", image_plane_coordinates)
