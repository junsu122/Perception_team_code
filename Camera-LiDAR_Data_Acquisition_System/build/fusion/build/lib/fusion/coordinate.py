#!/usr/bin/env python

import rclpy 
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
 
class CoordinateConverter(Node):
  def __init__(self):
    super().__init__('CoordinateConverter')
    self.subscription = self.create_subscription(
      Int32MultiArray, 
      'laneCoordinate', 
      self.coordinateCallback, 
      10)
     # prevent unused variable warning

  
  def coordinateCallback(self, msg):
    if msg is not None:
      x1,y1,x2,y2 = msg
      print("x1",x1)
      print("y1",y1)
      print("x2",x2)
      print("y2",y2)




  


def main(args=None):
  
  rclpy.init(args=args)
  node = CoordinateConverter()
  
  rclpy.spin(node)
  node.destroy_node()
  
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()