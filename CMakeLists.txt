cmake_minimum_required(VERSION 3.0)
set(PROJ_NAME convert_swat)
project(${PROJ_NAME} CXX)

set(CMAKE_CXX_STANDARD 14)
if ($ENV{C_IDENTIFIER} MATCHES PC)
    set(CMAKE_PREFIX_PATH D:\\libtorch)
else ()
    if (MSVC)
        set(CMAKE_PREFIX_PATH C:\\Users\\17110\\libtorch)
    else ()
        set(CMAKE_PREFIX_PATH /root/libtorch)
    endif ()
endif ()
message(${CMAKE_PREFIX_PATH})

find_package(Torch REQUIRED)

add_executable(${PROJ_NAME} main.cpp src/ProgressBar.cpp headers/ProgressBar.h)
target_link_libraries(${PROJ_NAME} "${TORCH_LIBRARIES}")
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET ${PROJ_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:${PROJ_NAME}>)
endif (MSVC)