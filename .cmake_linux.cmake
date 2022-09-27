set( EXEC incaribus )
set( EXT cpp )

## IMPORTED SHARED LIBRARY NAME
set( SHARED_LIB_NAME
        Jsnp
        SWEngine-OpenGLModule
        glfw
        yaml-cpp
        openal
        sndfile
        )
## IMPORTED SHARED LIBRARY LOCATION
set( SHARED_LIB_LOCATION
        ${CMAKE_SOURCE_DIR}/libraries/libJsnp.so
        ${CMAKE_SOURCE_DIR}/libraries/libSWEngine-OpenGLModule.so
        ${CMAKE_SOURCE_DIR}/libraries/libglfw.so
        ${CMAKE_SOURCE_DIR}/libraries/libyaml-cpp.so
        ${CMAKE_SOURCE_DIR}/libraries/libopenal.so
        ${CMAKE_SOURCE_DIR}/libraries/libsndfile.so
        )
## <=====================================>


## GET SOURCES
## <=====================================>
foreach(filePath ${SRC_FOLDERS})
    string(APPEND TMP "${filePath}*.${EXT};")
endforeach()
file(GLOB SRC ${TMP})
## <=====================================>


## OUTPUT
## <=====================================>
## EXECUTABLE
add_executable(${EXEC} ${SRC})

## or SHARED LIB
# add_library(${EXEC} SHARED ${SRC})

## or STATIC LIB
# add_library(${EXEC} STATIC ${SRC})
## <=====================================>


## ADD INCLUDES
## <=====================================>
target_include_directories(${EXEC} PRIVATE ${INC_FOLDERS})
include_directories (/usr/include/freetype2)
target_link_libraries(${EXEC} PUBLIC ${FT})
## <=====================================>

## ADD PARAMETER
## <=====================================>
if (UNIX)
    target_compile_options(${EXEC} PRIVATE -g3)
endif (UNIX)
## <=====================================>


## SHARED LIBRARY LINKING
## <=====================================>
list(LENGTH SHARED_LIB_NAME  list_len)
math(EXPR LIST_LEN "${list_len} - 1")

foreach(ctr RANGE ${LIST_LEN})
    list(GET SHARED_LIB_NAME ${ctr} lib)
    list(GET SHARED_LIB_LOCATION ${ctr} loc)
    add_library(${lib} SHARED IMPORTED)
    set_target_properties(${lib} PROPERTIES
            IMPORTED_LOCATION ${loc}
            )
endforeach()
target_link_libraries(${EXEC}
        PUBLIC
        ${SHARED_LIB_NAME}
        )
## <=====================================>


## PACKAGE LINKING
## <=====================================>
## <=====================================>