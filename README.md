### Ping-pong RPC.
The application is implemented using Protobuf and gRPC libraries in C++ programming language. To run, you need to install these libraries. All the necessary instructions are written in the sh file, it must be run from the superuser.

#### Build necessary libraries and binary files for ping-pong application:
```
sudo ./build.sh
```

#### Run:
```
cd build
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
