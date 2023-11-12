### Ping-pong RPC.
The application is implemented using Protobuf and gRPC libraries in C++ programming language. To run, you need to install these libraries. It is recommended to build from [source code](https://github.com/grpc/grpc/tree/master/src/cpp), following [these steps](https://grpc.io/docs/languages/cpp/quickstart).

#### Build:
```
mkdir build
cd build/
cmake ..
make
```

#### Run server:
```
./pingpong_server
```

#### Run client:
```
./pingpong_client
```

#### Expected client-side output:
```
Client sends Ping.
Server responds Pong.

Client sends Ping.
Server responds Pong.

...
```
