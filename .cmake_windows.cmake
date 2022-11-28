set( EXEC moulmerman )
set( EXT cpp )

add_definitions(-DYAML_CPP_STATIC_DEFINE)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(DEBUG_SUFFIX "d")
else()
    set(DEBUG_SUFFIX "")
endif()

## IMPORTED SHARED LIBRARY NAME
set( SHARED_LIB_NAME
        Jsnp
        SWEngine-OpenGLModule${DEBUG_SUFFIX}
        glfw
        sndfile
        freetype
        )

## IMPORTED SHARED LIBRARY LOCATION
set( SHARED_LIB_LOCATION
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/Jsnp.dll
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/SWEngine-OpenGLModule${DEBUG_SUFFIX}.dll
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/glfw3.dll
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/sndfile.dll
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/freetype.dll
        )
## IMPORTED SHARED LIBRARY lib file
set( SHARED_LIB
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/Jsnp.lib
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/SWEngine-OpenGLModule${DEBUG_SUFFIX}.lib
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/glfw3.lib
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/sndfile.lib
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/freetype.lib
        )

### IMPORTED STATIC LIBRARY NAME
set( STATIC_LIB_NAME
        yaml-cpp${DEBUG_SUFFIX}
        )

## IMPORTED STATIC LIBRARY .lib file
set( STATIC_LIB
        ${CMAKE_SOURCE_DIR}/libraries/${CMAKE_BUILD_TYPE}/yaml-cpp${DEBUG_SUFFIX}.lib
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
## <=====================================>

## ADD PARAMETER
## <=====================================>
if (UNIX)
    target_compile_options(${EXEC} PRIVATE -g3)
endif (UNIX)
if(MSVC)
    target_compile_options(${EXEC} PRIVATE "/MP")
endif()
## <=====================================>


## SHARED LIBRARY LINKING
## <=====================================>
list(LENGTH SHARED_LIB_NAME  list_len)
math(EXPR LIST_LEN "${list_len} - 1")

foreach(ctr RANGE ${LIST_LEN})
    list(GET SHARED_LIB_NAME ${ctr} lib)
    list(GET SHARED_LIB_LOCATION ${ctr} loc)
    list(GET SHARED_LIB ${ctr} filelib)
    message(${lib} ${loc} ${filelib})
    add_library(${lib} SHARED IMPORTED)
    file(COPY ${loc} DESTINATION ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}/)
    set_target_properties(${lib} PROPERTIES
            IMPORTED_LOCATION ${loc}
            IMPORTED_IMPLIB ${filelib}
            )
endforeach()
target_link_libraries(${EXEC}
        PUBLIC
        ${SHARED_LIB_NAME}
        )
## <=====================================>

## STATIC LIBRARY LINKING
## <=====================================>
list(LENGTH STATIC_LIB_NAME  list_len)
math(EXPR LIST_LEN "${list_len} - 1")

foreach(ctr RANGE ${LIST_LEN})
    list(GET STATIC_LIB_NAME ${ctr} lib)
    list(GET STATIC_LIB ${ctr} filelib)
    message(${filelib})
    add_library(${lib} STATIC IMPORTED)
    set_target_properties(${lib} PROPERTIES
            IMPORTED_LOCATION ${filelib}
            )
endforeach()
target_link_libraries(${EXEC}
        PUBLIC
        ${STATIC_LIB_NAME}
        )
## <=====================================>


## PACKAGE LINKING
## <=====================================>
## <=====================================>