#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "pingpong.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using pingpong::PingPong;
using pingpong::PingRequest;
using pingpong::PongResponse;

class PingPongClient {
public:
    PingPongClient(std::shared_ptr<Channel> channel)
        : stub_(PingPong::NewStub(channel)) {}

    std::string Ping() {
        PingRequest request;
        PongResponse response;
        ClientContext context;

        Status status = stub_->Ping(&context, request, &response);
        sleep(1);
        if (status.ok()) {
            return response.message();
        } else {
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<PingPong::Stub> stub_;
};

int main() {
    PingPongClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    while (true) {
        sleep(1);
        std::cout << "Client sends Ping." << std::endl;
        std::cout << "Server responds " << client.Ping() << std::endl;
        std::cout << "" << std::endl;
    }

    return 0;
}
