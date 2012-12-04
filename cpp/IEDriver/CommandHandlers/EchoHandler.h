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

#ifndef WEBDRIVER_IE_ECHOHANDLER_H_
#define WEBDRIVER_IE_ECHOHANDLER_H_

#include "../Browser.h"
#include "../IECommandHandler.h"
#include "../IECommandExecutor.h"

namespace webdriver {

class EchoHandler : public IECommandHandler {
 public:
  EchoHandler(void) {
  }

  virtual ~EchoHandler(void) {
  }

 protected:
  void ExecuteInternal(const IECommandExecutor& executor,
                       const LocatorMap& locator_parameters,
                       const ParametersMap& command_parameters,
                       Response* response) {
	ParametersMap::const_iterator message_parameter_iterator = command_parameters.find("message");
	if (message_parameter_iterator == command_parameters.end()) {
		response->SetErrorResponse(400, "Missing parameter: message");
		return;
    } else {
		std::string message = message_parameter_iterator->second.asString();
		response->SetSuccessResponse(message);
	}
  }
};

} // namespace webdriver

#endif // WEBDRIVER_IE_ECHOHANDLER_H_
