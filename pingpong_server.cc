#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <unistd.h>
#include "pingpong.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ClientContext;
using grpc::ServerWriter;
using pingpong::PingPong;
using pingpong::PingRequest;
using pingpong::PongResponse;

class PingPongServiceImpl final : public PingPong::Service {
public:

    Status Ping(ServerContext* context, const PingRequest* request, PongResponse* response) override {
        response->set_message("Pong.");
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    PingPongServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
