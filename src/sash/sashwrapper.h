#include <napi.h>
#include "sash.h"

class SashWrapper : public Napi::ObjectWrap<SashWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  SashWrapper(const Napi::CallbackInfo& info);
  Sash* GetInternalInstance();

 private:
  static Napi::FunctionReference constructor;
  void Update(const Napi::CallbackInfo& info);
  Napi::Value Digest(const Napi::CallbackInfo& info);
  Sash *sash_;
};
