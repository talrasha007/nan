/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>
#include <string.h>  // memset()

static v8::Persistent<v8::String> persistentTest1;

NAN_METHOD(Save1) {
  NanScope();

  NanAssignPersistent(persistentTest1, args[0].As<v8::String>());

  NanReturnUndefined();
}

NAN_METHOD(Get1) {
  NanScope();

  NanReturnValue(NanNew(persistentTest1));
}

NAN_METHOD(Dispose1) {
  NanScope();

  NanDisposePersistent(persistentTest1);

  NanReturnUndefined();
}

NAN_METHOD(ToPersistentAndBackAgain) {
  NanScope();

  v8::Persistent<v8::Object> persistent;
  NanAssignPersistent(persistent, args[0].As<v8::Object>());
  v8::Local<v8::Object> object = NanNew(persistent);
  NanDisposePersistent(persistent);
  memset(&persistent, -1, sizeof(persistent));  // Clobber it good.

  NanReturnValue(object);
}

NAN_METHOD(PersistentToPersistent) {
  NanScope();

  v8::Persistent<v8::String> persistent;
  NanAssignPersistent(persistent, args[0].As<v8::String>());
  NanAssignPersistent(persistentTest1, persistent);
  NanDisposePersistent(persistent);
  NanDisposePersistent(persistentTest1);

  NanReturnUndefined();
}

void Init (v8::Handle<v8::Object> target) {
  target->Set(
      NanNew<v8::String>("save1")
    , NanNew<v8::FunctionTemplate>(Save1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("get1")
    , NanNew<v8::FunctionTemplate>(Get1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("dispose1")
    , NanNew<v8::FunctionTemplate>(Dispose1)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("toPersistentAndBackAgain")
    , NanNew<v8::FunctionTemplate>(ToPersistentAndBackAgain)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("persistentToPersistent")
    , NanNew<v8::FunctionTemplate>(PersistentToPersistent)->GetFunction()
  );
}

NODE_MODULE(persistent, Init)
