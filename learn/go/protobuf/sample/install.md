1. 去`https://github.com/google/protobuf`下载代码
2. 按`https://github.com/google/protobuf/tree/master/src`的方法编译安装
3. `go get github.com/golang/protobuf` 
4. 进入protobuf/protoc-gen-go `go build`
5. `protoc --go_out=. sample.proto` 
