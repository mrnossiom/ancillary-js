#include <napi.h>

extern "C" {
  #include "ancillaire.h"
}

using namespace Napi;

String Version(const CallbackInfo& info) {
  Env env = info.Env();

  String returnValue = String::New(env, ancillaire_version());
  return returnValue;
}

Number SendFd(const CallbackInfo& info) {
  Env env = info.Env();

  int socket_fd = info[0].As<Number>();
  int fd = info[1].As<Number>();

  return Number::New(env, ancillaire_send_fd(socket_fd, fd));
}

class RecvFdWorker : public AsyncWorker {
  public:
    RecvFdWorker(Function& callback, int socket_fd): AsyncWorker(callback), socket_fd(socket_fd) {}
    ~RecvFdWorker() {}

  // This code will be executed on the worker thread
  void Execute() override {
    // Need to simulate cpu heavy task
    resulting_fd = ancillaire_recv_fd(socket_fd);
  }

  void OnOK() override {
    HandleScope scope(Env());
    Callback().Call({Env().Null(), Number::New(Env(), resulting_fd)});
  }

  private:
    int resulting_fd;
    int socket_fd;
};

Value RecvFd(const CallbackInfo& args) {
  // You need to validate the arguments here.
  Function cb = args[1].As<Function>();
  Number in = args[0].As<Number>();

  RecvFdWorker* wk = new RecvFdWorker(cb, in);

  wk->Queue();
  return args.Env().Undefined();
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "version"), Function::New(env, Version));
  exports.Set(String::New(env, "sendFd"), Function::New(env, SendFd));
  exports.Set(String::New(env, "recvFd"), Function::New(env, RecvFd));
  return exports;
}

NODE_API_MODULE(addon, Init);
