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
        ${CMAKE_CURRENT_LIST_DIR}/FlightComputer.proto
        ${CMAKE_CURRENT_LIST_DIR}/FlightController.proto
        ${CMAKE_CURRENT_LIST_DIR}/LoRa.proto
        ${CMAKE_CURRENT_LIST_DIR}/Nav.proto
        ${CMAKE_CURRENT_LIST_DIR}/PDB.proto
        ${CMAKE_CURRENT_LIST_DIR}/Taranis.proto
        ${CMAKE_CURRENT_LIST_DIR}/FlightControllerSetpoint.proto)

nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS ${TOOLBOX_PLANE_MESSAGES})
add_library(${PROJECT_NAME} STATIC ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${NANOPB_INCLUDE_DIRS})
