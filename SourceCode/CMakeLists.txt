cmake_minimum_required(VERSION 3.14)

project(Revelation)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} *)
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${SUBDIR})
        if(${SUBDIR} STREQUAL "Include")
            include_directories(${CMAKE_SOURCE_DIR}/${SUBDIR})
        elseif(EXISTS ${CMAKE_SOURCE_DIR}/${SUBDIR}/CMakeLists.txt)
            message("-- Add subdirectory: ${SUBDIR}")
            add_subdirectory(${SUBDIR})
        endif()
    endif()
endforeach()

# resource copy
if(CMAKE_CONFIGURATION_TYPES)
    set(RENDERER_RES_DST ${REVELATION_OUTPUT_DIR}/$<CONFIG>/resources)
else()
    set(RENDERER_RES_DST ${REVELATION_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/resources)
endif()

set(REVELATION_RES_DST ${PROJECT_BINARY_DIR}/Revelation/resources)

add_custom_target(RevelationResourceCopy)

set(RENDERER_RESOURCE_DIRS font image qss settings)
foreach(dir IN LISTS RENDERER_RESOURCE_DIRS)

    add_custom_command(TARGET RevelationResourceCopy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
                ${RENDERER_RES_DST}/${dir}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/../resources/${dir}
                ${RENDERER_RES_DST}/${dir}

        COMMAND ${CMAKE_COMMAND} -E remove_directory
                ${REVELATION_RES_DST}/${dir}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/../resources/${dir}
                ${REVELATION_RES_DST}/${dir}
    )
endforeach()

set_property(TARGET RevelationResourceCopy PROPERTY FOLDER ResourceCopy)
