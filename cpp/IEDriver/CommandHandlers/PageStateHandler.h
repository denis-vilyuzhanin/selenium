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

#ifndef WEBDRIVER_IE_PAGESTATEHANDLER_H_
#define WEBDRIVER_IE_PAGESTATEHANDLER_H_

#include "../Browser.h"
#include "../IECommandHandler.h"
#include "../IECommandExecutor.h"
#include "logging.h"

namespace webdriver {

class PageStateHandler : public IECommandHandler {
 public:
  PageStateHandler(void) {
  }

  virtual ~PageStateHandler(void) {
  }

 protected:
  void ExecuteInternal(const IECommandExecutor& executor,
                       const LocatorMap& locator_parameters,
                       const ParametersMap& command_parameters,
                       Response* response) {
    BrowserHandle browser_wrapper;
    int status_code = executor.GetCurrentBrowser(&browser_wrapper);
    if (status_code != SUCCESS) {
      response->SetErrorResponse(status_code, "Unable to get browser");
      return;
    }

	CComPtr<IHTMLDocument2> doc;
	browser_wrapper->GetDocument(&doc);

	CComBSTR pageURL;
	HRESULT hr = doc->get_URL(&pageURL);
	if (FAILED(hr)) {
      LOGHR(WARN, hr) << "Unable to get document URL";
	  response->SetErrorResponse(status_code, "Unable to get document URL");
      return;
    }
	std::string url_string = CW2A(pageURL, CP_UTF8);

	Json::Value response_value;
	response_value["url"] = url_string;
    //std::string page_source = browser_wrapper->GetPageSource();
    response->SetSuccessResponse(response_value);
  }
};

} // namespace webdriver

#endif // WEBDRIVER_IE_PAGESTATEHANDLER_H_
