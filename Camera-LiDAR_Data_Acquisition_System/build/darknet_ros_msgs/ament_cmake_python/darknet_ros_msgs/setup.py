from setuptools import find_packages
from setuptools import setup

setup(
    name='darknet_ros_msgs',
    version='1.1.5',
    packages=find_packages(
        include=('darknet_ros_msgs', 'darknet_ros_msgs.*')),
)
