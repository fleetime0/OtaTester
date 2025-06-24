cmake_minimum_required(VERSION 3.14)

project(otatester)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

include(Build3rdparty)
Build3rdparty()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -ldl")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}-output" CACHE STRING "install prefix" FORCE)
endif()

set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")

set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/3rdparty")

find_package(CommonAPI 3.2.0 REQUIRED)
find_package(CommonAPI-SomeIP 3.2.0 REQUIRED)
find_package(vsomeip3 3.4.10 REQUIRED)
find_package(nlohmann_json 3.12.0 REQUIRED)

include(GNUInstallDirs)

# set(FIDL_DIR ${CMAKE_SOURCE_DIR}/fidl)
# set(GEN_COMMON_CORE_DIR ${CMAKE_SOURCE_DIR}/tool/commonapi_core_generator/commonapi-core-generator-linux-x86_64)
# set(GEN_COMMON_SOMEIP_DIR ${CMAKE_SOURCE_DIR}/tool/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64)

set(GEN_SRC_DIR ${CMAKE_SOURCE_DIR}/src-gen)
# set(GEN_COMMON_CORE ${GEN_COMMON_CORE_DIR} -sk -d ${GEN_SRC_DIR} ${FIDL_DIR}/OtaTester.fidl)
# set(GEN_COMMON_SOMEIP ${GEN_COMMON_SOMEIP_DIR} -d ${GEN_SRC_DIR} ${FIDL_DIR}/OtaTester.fdepl)

# execute_process(
#   COMMAND ${GEN_COMMON_CORE}
#   RESULT_VARIABLE result
# )

# if(NOT result EQUAL "0")
#   message(FATAL_ERROR "GEN_COMMON_API failed: ${result}")
# endif()

# execute_process(
#   COMMAND ${GEN_COMMON_SOMEIP}
#   RESULT_VARIABLE result
# )

# if(NOT result EQUAL "0")
#   message(FATAL_ERROR "GEN_COMMON_API_SOMEIP failed: ${result}")
# endif()

add_library(otatester SHARED
  src/ota_helper.cpp
  src/ota_helper_py.cpp
	${GEN_SRC_DIR}/v1/commonapi/ota/FOTAMPUUpdateSomeIPProxy.cpp
  ${GEN_SRC_DIR}/v1/commonapi/ota/FOTAMPUUpdateSomeIPDeployment.cpp
)

target_include_directories(otatester 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${GEN_SRC_DIR}
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
)

target_link_libraries(otatester PRIVATE
  CommonAPI
  vsomeip3
	CommonAPI-SomeIP
	nlohmann_json::nlohmann_json
)

add_executable(otaclient src/client.cpp)

target_link_libraries(otaclient PRIVATE
  otatester
)

install(TARGETS otatester
  EXPORT OtaTesterTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT OtaTesterTargets
  FILE OtaTesterTargets.cmake
  NAMESPACE OtaTester::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OtaTester
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/cmake/OtaTesterConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/OtaTesterConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OtaTester
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/OtaTesterConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OtaTester
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/etc/
  DESTINATION etc
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/3rdparty/lib/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS otaclient
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
