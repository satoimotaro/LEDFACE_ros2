from setuptools import setup

package_name = 'ledface_launch'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    py_modules=[],
    include_package_data=True,
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='satoimo',
    maintainer_email='satoimo3taro183@gmail.com',
    description='Launch file for image publisher + dot filter',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [],
    },
    data_files=[
        ('share/' + package_name, ['package.xml']),    
        ('share/ament_index/resource_index/packages', ['resource/ledface_launch']),
        ('share/' + package_name + '/launch', ['launch/ledface_launch.py']),
    ],
)
