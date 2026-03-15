import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/junsu/Perception_team_code/yolo_seg_python_package/install/yolo'
