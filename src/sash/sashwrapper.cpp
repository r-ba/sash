#include "sashwrapper.h"

Napi::FunctionReference SashWrapper::constructor;

Napi::Object SashWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "create", {
    InstanceMethod("update", &SashWrapper::Update),
    InstanceMethod("digest", &SashWrapper::Digest)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("create", func);
  return exports;
}

SashWrapper::SashWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<SashWrapper>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int length = info.Length();

  if (length == 0) {
    this->sash_ = new Sash("");
  } else if (length == 1) {
    Napi::String value = info[0].As<Napi::String>();
    this->sash_ = new Sash(value.ToString());
  } else {
    Napi::TypeError::New(env, "Only one argument permitted").ThrowAsJavaScriptException();
  }
}

void SashWrapper::Update(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
  }

  Napi::String strChunk = info[0].As<Napi::String>();
  this->sash_->update(strChunk.ToString());
}

Napi::Value SashWrapper::Digest(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 0) {
    Napi::TypeError::New(env, "Takes no arguments").ThrowAsJavaScriptException();
  }

  std::string digestedValue = this->sash_->digest();

  return Napi::String::New(info.Env(), digestedValue);
}

Sash* SashWrapper::GetInternalInstance() {
  return this->sash_;
}
