cmake_minimum_required(VERSION 3.21)

project(CS0045_Module5Act LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

if(NOT APPLE)
    find_package(GLEW REQUIRED)
endif()

function(add_module5_program source_file)
    get_filename_component(program_name "${source_file}" NAME_WE)
    get_filename_component(part_dir "${source_file}" DIRECTORY)
    get_filename_component(part_name "${part_dir}" NAME)
    set(target_name "${part_name}_${program_name}")

    add_executable("${target_name}" "${source_file}")
    target_link_libraries("${target_name}" PRIVATE OpenGL::GL GLUT::GLUT)

    if(NOT APPLE)
        target_link_libraries("${target_name}" PRIVATE GLEW::GLEW)
    endif()

    set_target_properties("${target_name}" PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${part_name}"
    )
endfunction()

file(GLOB PART_A_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/SourceCode/PartA/*.cpp"
)
file(GLOB PART_B_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/SourceCode/PartB/*.cpp"
)

foreach(source_file IN LISTS PART_A_SOURCES PART_B_SOURCES)
    add_module5_program("${source_file}")
endforeach()
