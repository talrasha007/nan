/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>
#include <string>

static int magic = 1337;

NAN_METHOD(NewNumber) {
  NanScope();
  NanReturnValue(NanNew<v8::Number>(0.5));
}

NAN_METHOD(NewNegativeInteger) {
  NanScope();
  NanReturnValue(NanNew<v8::Integer>(-1));
}

NAN_METHOD(NewPositiveInteger) {
  NanScope();
  NanReturnValue(NanNew<v8::Integer>(1));
}

NAN_METHOD(NewUnsignedInteger) {
  NanScope();
  NanReturnValue(NanNew<v8::Integer>(0xFFFFFFFFu));
}

NAN_METHOD(NewInt32FromPositive) {
  NanScope();
  NanReturnValue(NanNew<v8::Int32>(0xFFFFFFFF));
}

NAN_METHOD(NewInt32FromNegative) {
  NanScope();
  NanReturnValue(NanNew<v8::Int32>(-1));
}

NAN_METHOD(NewUint32FromPositive) {
  NanScope();
  NanReturnValue(NanNew<v8::Uint32>(0xFFFFFFFF));
}

NAN_METHOD(NewUint32FromNegative) {
  NanScope();
  NanReturnValue(NanNew<v8::Uint32>(-1));
}

NAN_METHOD(NewUtf8String) {
  NanScope();
  const char s[] = "strïng";
  NanReturnValue(NanNew<v8::String>(s));
}

NAN_METHOD(NewLatin1String) {
  NanScope();
  const uint8_t s[] = "str\xefng";
  NanReturnValue(NanNew<v8::String>(s));
}

NAN_METHOD(NewUcs2String) {
  NanScope();
  const uint16_t s[] = {'s', 't', 'r', 0xef, 'n', 'g', '\0'};
  NanReturnValue(NanNew(s));
}

NAN_METHOD(NewStdString) {
  NanScope();
  const std::string s = "strïng";
  NanReturnValue(NanNew<v8::String>(s));
}

NAN_METHOD(NewRegExp) {
  NanScope();
  NanReturnValue(NanNew<v8::RegExp>(NanNew("foo"), v8::RegExp::kNone));
}

NAN_METHOD(NewStringObject) {
  NanScope();
  NanReturnValue(NanNew<v8::StringObject>(NanNew<v8::String>("foo")));
}

NAN_METHOD(NewNumberObject) {
  NanScope();
  NanReturnValue(NanNew<v8::NumberObject>(0.5));
}

NAN_METHOD(NewBooleanObject) {
  NanScope();
  NanReturnValue(NanNew<v8::BooleanObject>(true));
}

NAN_METHOD(NewExternal) {
  NanScope();
  v8::Local<v8::External> ext = NanNew<v8::External>(&magic);
  assert(*static_cast<int *>(ext->Value()) == 1337);
  NanReturnValue(NanNew<v8::String>("passed"));
}

NAN_METHOD(NewSignature) {
  NanScope();
  v8::Local<v8::FunctionTemplate> tmpl =
      NanNew<v8::FunctionTemplate>(NewSignature);
  v8::Local<v8::Signature> sig = NanNew<v8::Signature>(tmpl, 1, &tmpl);
  tmpl = NanNew<v8::FunctionTemplate>(
      NewSignature, v8::Handle<v8::Value>(), sig);
  NanReturnValue(NanNew<v8::String>("string"));
}

NAN_METHOD(NewScript) {
  NanScope();
  v8::Local<NanUnboundScript> script = NanNew<NanUnboundScript>(NanNew("2+4"));
  NanReturnValue(NanRunScript(script)->ToInt32());
}

NAN_METHOD(NewScript2) {
  NanScope();
  v8::ScriptOrigin origin(NanNew<v8::String>("x"));
  v8::Local<NanUnboundScript> script =
      NanNew<NanUnboundScript>(NanNew("2+4"), origin);
  NanReturnValue(NanRunScript(script)->ToInt32());
}

NAN_METHOD(CompileScript) {
  NanScope();
  v8::Local<NanBoundScript> script = NanCompileScript(NanNew("2+4"));
  NanReturnValue(NanRunScript(script)->ToInt32());
}

NAN_METHOD(CompileScript2) {
  NanScope();
  v8::ScriptOrigin origin(NanNew<v8::String>("x"));
  v8::Local<NanBoundScript> script = NanCompileScript(NanNew("2+4"), origin);
  NanReturnValue(NanRunScript(script)->ToInt32());
}

NAN_METHOD(NewDate) {
  NanScope();
  NanReturnValue(NanNew<v8::Date>(1337));
}

NAN_METHOD(NewArray) {
  NanScope();
  NanReturnValue(NanNew<v8::Array>());
}

NAN_METHOD(NewBoolean) {
  NanScope();
  NanReturnValue(NanNew<v8::Boolean>(true));
}

// #212
NAN_METHOD(NewBoolean2) {
  NanScope();
  NanReturnValue(NanNew<v8::Boolean>(1));
}

void Init(v8::Handle<v8::Object> target) {
  target->Set(
      NanNew<v8::String>("newNumber")
    , NanNew<v8::FunctionTemplate>(NewNumber)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newNegativeInteger")
    , NanNew<v8::FunctionTemplate>(NewNegativeInteger)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newPositiveInteger")
    , NanNew<v8::FunctionTemplate>(NewPositiveInteger)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newUnsignedInteger")
    , NanNew<v8::FunctionTemplate>(NewUnsignedInteger)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newInt32FromPositive")
    , NanNew<v8::FunctionTemplate>(NewInt32FromPositive)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newInt32FromNegative")
    , NanNew<v8::FunctionTemplate>(NewInt32FromNegative)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newUint32FromPositive")
    , NanNew<v8::FunctionTemplate>(NewUint32FromPositive)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newUint32FromNegative")
    , NanNew<v8::FunctionTemplate>(NewUint32FromNegative)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newUtf8String")
    , NanNew<v8::FunctionTemplate>(NewUtf8String)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newLatin1String")
    , NanNew<v8::FunctionTemplate>(NewLatin1String)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newUcs2String")
    , NanNew<v8::FunctionTemplate>(NewUcs2String)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newStdString")
    , NanNew<v8::FunctionTemplate>(NewStdString)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newRegExp")
    , NanNew<v8::FunctionTemplate>(NewRegExp)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newStringObject")
    , NanNew<v8::FunctionTemplate>(NewStringObject)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newNumberObject")
    , NanNew<v8::FunctionTemplate>(NewNumberObject)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newBooleanObject")
    , NanNew<v8::FunctionTemplate>(NewBooleanObject)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newExternal")
    , NanNew<v8::FunctionTemplate>(NewExternal)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newSignature")
    , NanNew<v8::FunctionTemplate>(NewSignature)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newScript")
    , NanNew<v8::FunctionTemplate>(NewScript)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newScript2")
    , NanNew<v8::FunctionTemplate>(NewScript2)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("compileScript")
    , NanNew<v8::FunctionTemplate>(CompileScript)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("compileScript2")
    , NanNew<v8::FunctionTemplate>(CompileScript2)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newDate")
    , NanNew<v8::FunctionTemplate>(NewDate)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newArray")
    , NanNew<v8::FunctionTemplate>(NewArray)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newBoolean")
    , NanNew<v8::FunctionTemplate>(NewBoolean)->GetFunction()
  );
  target->Set(
      NanNew<v8::String>("newBoolean2")
    , NanNew<v8::FunctionTemplate>(NewBoolean2)->GetFunction()
  );
}

NODE_MODULE(news, Init)
