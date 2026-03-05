from setuptools import find_packages, setup

package_name = 'fusion'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='junsu',
    maintainer_email='junsu@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    test_suite='tests',
    entry_points={
        'console_scripts': [
        'cap = fusion.capture:main',
        'roi = fusion.roi_pls:main',
        'mtest = fusion.matrix_test:main',
        'test = fusion.testsub:main',
        'double = fusion.cam_lidar_double_cap:main',
        'track = fusion.lidar_track:main',
        'top = fusion.top_view:main',
        ],
    },
)
