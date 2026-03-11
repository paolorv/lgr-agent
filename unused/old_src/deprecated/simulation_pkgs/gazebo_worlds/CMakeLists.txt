cmake_minimum_required(VERSION 3.8)
project(gazebo_worlds)

find_package(ament_cmake REQUIRED)

install(
	DIRECTORY agri
	DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(ament_cmake)

ament_package()
