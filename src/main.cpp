#include <napi.h>
#include "sash/sashwrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return SashWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
