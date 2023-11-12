cmake_minimum_required(VERSION 3.5)

project(PingPong C CXX)

option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

set(_GRPC_GRPCPP gRPC::grpc++)

get_filename_component(pingpong_proto "pingpong.proto" ABSOLUTE)
get_filename_component(pingpong_proto_path "${pingpong_proto}" PATH)

set(pingpong_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/pingpong.pb.cc")
set(pingpong_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/pingpong.pb.h")
set(pingpong_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/pingpong.grpc.pb.cc")
set(pingpong_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/pingpong.grpc.pb.h")

add_custom_command(
      OUTPUT "${pingpong_proto_srcs}" "${pingpong_proto_hdrs}" "${pingpong_grpc_srcs}" "${pingpong_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${pingpong_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${pingpong_proto}"
      DEPENDS "${pingpong_proto}")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(pingpong_grpc_proto
  ${pingpong_grpc_srcs}
  ${pingpong_grpc_hdrs}
  ${pingpong_proto_srcs}
  ${pingpong_proto_hdrs})
target_link_libraries(pingpong_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

foreach(_target
  pingpong_client pingpong_server
  )
  add_executable(${_target} "${_target}.cc")
  target_link_libraries(${_target}
    pingpong_grpc_proto
    absl::flags
    absl::flags_parse
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()
