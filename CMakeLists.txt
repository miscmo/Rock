cmake_minimum_required(VERSION 3.0)
project(rock)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/jsoncpp-1.8.4)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/sqlite-3.28.0)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/tinyxml2-7.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated  -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated  -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/apps/rock/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/jsoncpp-1.8.4/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/sqlite-3.28.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/tinyxml2-7.0.1)
link_directories(/apps/rock/lib)
link_directories(/apps/rock/lib64)

option(BUILD_TEST "ON for complile test" ON)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(MySQL REQUIRED)
if(MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})
endif()

find_package(Protobuf)
if(Protobuf_FOUND)
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

set(LIB_SRC
    rock/address.cc
    rock/bytearray.cc
    rock/config.cc
    rock/db/fox_thread.cc
    rock/db/mysql.cc
    rock/db/redis.cc
    rock/db/sqlite3.cc
    rock/ds/bitmap.cc
    rock/ds/roaring_bitmap.cc
    rock/ds/roaring.c
    rock/ds/util.cc
    rock/email/email.cc
    rock/email/smtp.cc
    rock/env.cc
    rock/daemon.cc
    rock/fd_manager.cc
    rock/fiber.cc
    rock/http/http.cc
    rock/http/http_connection.cc
    rock/http/http_parser.cc
    rock/http/http_session.cc
    rock/http/http_server.cc
    rock/http/servlet.cc
    rock/http/servlets/config_servlet.cc
    rock/http/servlets/status_servlet.cc
    rock/http/session_data.cc
    rock/http/ws_connection.cc
    rock/http/ws_session.cc
    rock/http/ws_server.cc
    rock/http/ws_servlet.cc
    rock/hook.cc
    rock/iomanager.cc
    rock/library.cc
    rock/log.cc
    rock/module.cc
    rock/mutex.cc
    rock/ns/name_server_module.cc
    rock/ns/ns_client.cc
    rock/ns/ns_protocol.cc
    rock/protocol.cc
    rock/rock/rock_protocol.cc
    rock/rock/rock_server.cc
    rock/rock/rock_stream.cc
    rock/scheduler.cc
    rock/socket.cc
    rock/stream.cc
    rock/streams/async_socket_stream.cc
    rock/streams/socket_stream.cc
    rock/streams/load_balance.cc
    rock/streams/service_discovery.cc
    rock/streams/zlib_stream.cc
    rock/tcp_server.cc
    rock/timer.cc
    rock/thread.cc
    rock/util.cc
    rock/util/crypto_util.cc
    rock/util/json_util.cc
    rock/util/hash_util.cc
    rock/worker.cc
    rock/application.cc
    rock/zk_client.cc
    )

ragelmaker(rock/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/rock/http)
ragelmaker(rock/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/rock/http)
ragelmaker(rock/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/rock)

protobufmaker(rock/ns/ns_protobuf.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})
#PROTOBUF_GENERATE_CPP(PB_SRCS PB_HDRS rock/ns/ns_protobuf.proto)
#message("****${PB_SRCS}***${PB_HDRS}****")
#list(APPEND LIB_SRC ${PB_SRCS})
#
#message(STATUS ${LIB_SRC})

add_library(rock SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(rock)
#add_library(rock_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (rock_static PROPERTIES OUTPUT_NAME "rock")

#find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} rock)
#set(LIBS ${LIBS} dl)
#set(LIBS ${LIBS} ${YAMLCPP})
#set(LIBS ${LIBS} ${PTHREAD})

set(LIBS
        rock
        dl
        pthread
        yaml-cpp
        jsoncpp
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        event
        hiredis_vip
        mysqlclient_r
        zookeeper_mt
        sqlite3
        tinyxml2
        jemalloc
        )
rock_add_executable(test_util "tests/test_util.cc" rock "${LIBS}")
rock_add_executable(test_hashmultimap "tests/test_hashmultimap.cc" rock "${LIBS}")
rock_add_executable(test_hashmap "tests/test_hashmap.cc" rock "${LIBS}")
rock_add_executable(test_dict "tests/test_dict.cc" rock "${LIBS}")
rock_add_executable(test_array "tests/test_array.cc" rock "${LIBS}")
# if(BUILD_TEST)
rock_add_executable(test1 "tests/test.cc" rock "${LIBS}")
rock_add_executable(test_config "tests/test_config.cc" rock "${LIBS}")
rock_add_executable(test_thread "tests/test_thread.cc" rock "${LIBS}")
rock_add_executable(test_fiber "tests/test_fiber.cc" rock "${LIBS}")
rock_add_executable(test_scheduler "tests/test_scheduler.cc" rock "${LIBS}")
rock_add_executable(test_iomanager "tests/test_iomanager.cc" rock "${LIBS}")
rock_add_executable(test_hook "tests/test_hook.cc" rock "${LIBS}")
rock_add_executable(test_address "tests/test_address.cc" rock "${LIBS}")
rock_add_executable(test_socket "tests/test_socket.cc" rock "${LIBS}")
rock_add_executable(test_bytearray "tests/test_bytearray.cc" rock "${LIBS}")
rock_add_executable(test_http "tests/test_http.cc" rock "${LIBS}")
rock_add_executable(test_http_parser "tests/test_http_parser.cc" rock "${LIBS}")
rock_add_executable(test_tcp_server "tests/test_tcp_server.cc" rock "${LIBS}")
rock_add_executable(echo_server "examples/echo_server.cc" rock "${LIBS}")
rock_add_executable(test_http_server "tests/test_http_server.cc" rock "${LIBS}")
rock_add_executable(test_uri "tests/test_uri.cc" rock "${LIBS}")
rock_add_executable(my_http_server "samples/my_http_server.cc" rock "${LIBS}")

rock_add_executable(echo_server_udp "examples/echo_server_udp.cc" rock "${LIBS}")
rock_add_executable(echo_udp_client "examples/echo_udp_client.cc" rock "${LIBS}")

rock_add_executable(test_daemon "tests/test_daemon.cc" rock "${LIBS}")
rock_add_executable(test_env "tests/test_env.cc" rock "${LIBS}")
rock_add_executable(test_ws_server "tests/test_ws_server.cc" rock "${LIBS}")
rock_add_executable(test_ws_client "tests/test_ws_client.cc" rock "${LIBS}")
rock_add_executable(test_application "tests/test_application.cc" rock "${LIBS}")

rock_add_executable(test_http_connection "tests/test_http_connection.cc" rock "${LIBS}")
rock_add_executable(test_lru "tests/test_lru.cc" rock "${LIBS}")
rock_add_executable(test_timed_cache "tests/test_timed_cache.cc" rock "${LIBS}")
rock_add_executable(test_timed_lru_cache "tests/test_timed_lru_cache.cc" rock "${LIBS}")
rock_add_executable(test_zlib_stream "tests/test_zlib_stream.cc" rock "${LIBS}")

#endif()
rock_add_executable(test_crypto "tests/test_crypto.cc" rock "${LIBS}")
rock_add_executable(test_sqlite3 "tests/test_sqlite3.cc" rock "${LIBS}")
rock_add_executable(test_rock "tests/test_rock.cc" rock "${LIBS}")
rock_add_executable(test_email  "tests/test_email.cc" rock "${LIBS}")
rock_add_executable(test_mysql "tests/test_mysql.cc" rock "${LIBS}")
rock_add_executable(test_nameserver "tests/test_nameserver.cc" rock "${LIBS}")
rock_add_executable(test_bitmap "tests/test_bitmap.cc" rock "${LIBS}")
rock_add_executable(test_zkclient "tests/test_zookeeper.cc" rock "${LIBS}")
rock_add_executable(test_service_discovery "tests/test_service_discovery.cc" rock "${LIBS}")

set(ORM_SRCS
    rock/orm/table.cc
    rock/orm/column.cc
    rock/orm/index.cc
    rock/orm/orm.cc
    rock/orm/util.cc
    )
rock_add_executable(orm "${ORM_SRCS}" rock "${LIBS}")

add_library(test_module SHARED tests/test_module.cc)

rock_add_executable(bin_rock "rock/main.cc" rock "${LIBS}")
set_target_properties(bin_rock PROPERTIES OUTPUT_NAME "rock")

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)
#set(OLIBS ${LIBS} orm_data)
#rock_add_executable(test_orm "tests/test_orm.cc" orm_data "${OLIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
