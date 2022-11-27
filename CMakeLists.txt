project(ToolboxPlaneMessages)

include(FetchContent)

FetchContent_Declare(
        nanopb
        GIT_REPOSITORY "https://github.com/nanopb/nanopb.git"
        GIT_TAG "master"
)
FetchContent_Populate(nanopb)
set(CMAKE_MODULE_PATH ${nanopb_SOURCE_DIR}/extra)
find_package(Nanopb REQUIRED)

set(TOOLBOX_PLANE_MESSAGES
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/FlightComputer.proto
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/FlightController.proto
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/Nav.proto
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/PDB.proto
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/Remote.proto
        ${CMAKE_CURRENT_LIST_DIR}/Definitions/FlightControllerSetpoint.proto)

nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS ${TOOLBOX_PLANE_MESSAGES})
add_library(ToolboxPlaneMessageDefs STATIC ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(ToolboxPlaneMessageDefs PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${NANOPB_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC  MessageEncoding.c MessageDecoding.c)
target_link_libraries(${PROJECT_NAME} PUBLIC ToolboxPlaneMessageDefs)
