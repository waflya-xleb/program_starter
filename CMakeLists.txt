cmake_minimum_required( VERSION 4.0.1 )

message( "Starting compiling 'imagine a very cool project name'" )

project( Just_Project
	LANGUAGES CXX C)

set ( CMAKE_CXX_STANDARD 23 )

set ( "${PROJECT_NAME}_BINARY_DIR" bin )
set ( "${PROJECT_NAME}_SOURCE_DIR" . )
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT_NAME}_BINARY_DIR} )
set ( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT_NAME}_BINARY_DIR}/lib )

add_executable( program_starter program_starter.c shm_system/utils.c ipc_system/decoder.c )

add_executable( err_manager err_man/error_manager.c shm_system/utils.c ipc_system/decoder.c )


add_library( theLib SHARED theLib/theLib.cpp )
add_library( thetheLib SHARED thetheLib/thetheLib.cpp )

add_executable( program program_test/program.cpp )
add_executable( program_2 program_test/program_2.cpp )

#target_link_libraries( program_2 theLib )
