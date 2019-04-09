// Copyright (c) 2019 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_API_ATOM_API_PROTOCOL_NS_H_
#define ATOM_BROWSER_API_ATOM_API_PROTOCOL_NS_H_

#include "atom/browser/api/trackable_object.h"
#include "content/public/browser/content_browser_client.h"
#include "native_mate/dictionary.h"
#include "native_mate/handle.h"

namespace atom {

class AtomBrowserContext;

namespace api {

// Possible errors.
enum ProtocolError {
  PROTOCOL_OK,  // no error
  PROTOCOL_REGISTERED,
  PROTOCOL_NOT_REGISTERED,
  PROTOCOL_INTERCEPTED,
  PROTOCOL_NOT_INTERCEPTED,
};

// Protocol implementation based on network services.
class ProtocolNS : public mate::TrackableObject<ProtocolNS> {
 public:
  static mate::Handle<ProtocolNS> Create(v8::Isolate* isolate,
                                         AtomBrowserContext* browser_context);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  // Used by AtomBrowserClient for creating URLLoaderFactory.
  void RegisterURLLoaderFactories(
      content::ContentBrowserClient::NonNetworkURLLoaderFactoryMap* factories);

 private:
  ProtocolNS(v8::Isolate* isolate, AtomBrowserContext* browser_context);
  ~ProtocolNS() override;

  // Callback types.
  using Handler =
      base::Callback<void(const base::DictionaryValue&, v8::Local<v8::Value>)>;
  using CompletionCallback = base::Callback<void(v8::Local<v8::Value>)>;

  // JS APIs.
  int RegisterProtocol(const std::string& scheme,
                       const Handler& handler,
                       mate::Arguments* args);

  // scheme => handler.
  std::map<std::string, Handler> handlers_;
};

}  // namespace api

}  // namespace atom

#endif  // ATOM_BROWSER_API_ATOM_API_PROTOCOL_NS_H_
