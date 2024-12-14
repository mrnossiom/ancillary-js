#include "../result/include/node/node.h"

extern "C" {
  #include "ancillary.h"
}
 
using namespace v8;

void Version(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
   
  if (args.Length() != 0) {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "version takes no argument").ToLocalChecked()));
    return;
  }

  Local<String> result = String::NewFromUtf8(isolate, ancillary_version()).ToLocalChecked();
  args.GetReturnValue().Set(result);
}

void SendFd(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() != 2) {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "sendfd takes two arguments").ToLocalChecked()));
    return;
  }
 
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  int socket_fd = args[0]->ToNumber(context).ToLocalChecked()->Value();
  int fd = args[1]->ToNumber(context).ToLocalChecked()->Value();

  int result = ancillary_send_fd(socket_fd, fd);
  args.GetReturnValue().Set(result);
}

void RecvFd(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() != 1) {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "recvfd takes one argument").ToLocalChecked()));
    return;
  }
 
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  int socket_fd = args[0]->ToNumber(context).ToLocalChecked()->Value();

  int result = ancillary_recv_fd(socket_fd);
  args.GetReturnValue().Set(result);
}
 
static void InitModule(v8::Local<v8::Object> exports,
                       v8::Local<v8::Value> module,
                       v8::Local<v8::Context> context) {
  NODE_SET_METHOD(exports, "version", Version);
  NODE_SET_METHOD(exports, "sendFd", SendFd);
  NODE_SET_METHOD(exports, "recvFd", RecvFd);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitModule)
