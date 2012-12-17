// Copyright 2011 Software Freedom Conservancy
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WEBDRIVER_IE_JSON_REQUEST_RESPONSE_HANDLER_H_
#define WEBDRIVER_IE_JSON_REQUEST_RESPONSE_HANDLER_H_

#include "../Browser.h"
#include "../IECommandHandler.h"
#include "../IECommandExecutor.h"

namespace webdriver {

class JsonRequestResponse : public IECommandHandler {
 public:
  JsonRequestResponse(void) {
  }

  virtual ~JsonRequestResponse(void) {
  }

 protected:
  void ExecuteInternal(const IECommandExecutor& executor,
                       const LocatorMap& locator_parameters,
                       const ParametersMap& command_parameters,
                       Response* response) {
	Json::Value response_value;
	response_value["type"] = "response";
	response_value["status"] = "success";

	Json::Value header;
	header["title"] = "Test";
	header["version"] = "1.0";
	response_value["header"] = header;

	Json::Value item0;
	item0["name"] = "item0";
	item0["value"] = "value0";

	Json::Value item1;
	item1["name"] = "item1";
	item1["value"] = "value1";
	
	Json::Value items(Json::arrayValue);
	items[(Json::UInt)0] = item0;
	items[(Json::UInt)1] = item1;

	response_value["items"] = items;

    response->SetSuccessResponse(response_value);
  }
};

} // namespace webdriver

#endif // WEBDRIVER_IE_JSON_REQUEST_RESPONSE_HANDLER_H_
