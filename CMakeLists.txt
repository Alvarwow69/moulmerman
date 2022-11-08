## CMAKE VAR
## <=====================================>
cmake_minimum_required( VERSION 3.17...3.22 )

project( Moulmerman
        VERSION
        0.1
        DESCRIPTION
        "Bomberman made for Game Design at Chung Ang Univ 2022"
        LANGUAGES
        CXX
        )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/ )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/ )
set(PREFIX_MESSAGE "[${PROJECT_NAME}] ")
## <=====================================>


## SOURCE FOLDERS
set( SRC_FOLDERS
        ${CMAKE_SOURCE_DIR}/sources/
        ${CMAKE_SOURCE_DIR}/sources/scenes/
        ${CMAKE_SOURCE_DIR}/sources/script/
        ${CMAKE_SOURCE_DIR}/sources/script/generator/
        )
## INCLUDE FOLDERS
set( INC_FOLDERS
        ${CMAKE_SOURCE_DIR}/libraries/
        ${CMAKE_SOURCE_DIR}/libraries/module/
        ${CMAKE_SOURCE_DIR}/libraries/core/
        ${CMAKE_SOURCE_DIR}/libraries/freetype/
        ${CMAKE_SOURCE_DIR}/includes/
        ${CMAKE_SOURCE_DIR}/includes/scenes/
        ${CMAKE_SOURCE_DIR}/includes/script/
        )

message(${PREFIX_MESSAGE} "Build type set to: " ${CMAKE_BUILD_TYPE})
message(${PREFIX_MESSAGE} "Current cmake location: " ${CMAKE_CURRENT_SOURCE_DIR})
message(${PREFIX_MESSAGE} "Project location: " ${CMAKE_SOURCE_DIR})

if (WIN32)
    message(${PREFIX_MESSAGE} "Windows system detected, prepare project...")
    include(.cmake_windows.cmake)
elseif(UNIX)
    message(${PREFIX_MESSAGE} "Linux system detected, prepare project...")
    include(.cmake_linux.cmake)
else()
    message(FATAL_ERROR "System not supported!")
endif()