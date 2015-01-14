/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

NAN_METHOD(ReturnNull) {
  NanScope();
  NanReturnNull();
}

void Init (v8::Handle<v8::Object> target) {
  target->Set(
      NanNew<v8::String>("r")
    , NanNew<v8::FunctionTemplate>(ReturnNull)->GetFunction()
  );
}

NODE_MODULE(returnnull, Init)

