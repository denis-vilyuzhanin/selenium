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
	try {
		response_value["bodyHtml"] = fetchBodyOuterHtml(doc);
		
		fetchRootNodeName(doc);
		Json::Value dom;
		dom["nodeName"] = fetchRootNodeName(doc);


		response_value["dom"] = dom;
		
	} catch (const char* m) {
		response->SetErrorResponse(-1, m);
		return;
	}

    response->SetSuccessResponse(response_value);
  }

  std::string fetchBodyOuterHtml(CComPtr<IHTMLDocument2>& doc) {
	CComPtr<IHTMLElement> body;
	HRESULT hr = doc->get_body(&body);
	assertSuccess(hr, "Unable to get document body");
	
	CComBSTR outerHTML;
	hr = body->get_outerHTML(&outerHTML);
	assertSuccess(hr, "Unable to get document body html");
	std::string bodyHTMLString = CW2A(outerHTML, CP_UTF8);
	return bodyHTMLString;
  }

  std::string fetchRootNodeName(CComPtr<IHTMLDocument2>& doc) {
	  CComPtr<IHTMLDocument3> doc3;
	  HRESULT hr = doc->QueryInterface(&doc3);
	  assertSuccess(hr, "Unable to get document3");

	  CComPtr<IHTMLElement> documentElement;
	  hr = doc3->get_documentElement(&documentElement);
	  assertSuccess(hr, "Unable to get document element");

	  CComPtr<IHTMLDOMNode> rootNode;
	  hr = documentElement->QueryInterface(&rootNode);
	  assertSuccess(hr, "Unable to get root node");
	  
	  CComBSTR rootNodeName;
	  hr = rootNode->get_nodeName(&rootNodeName);
	  assertSuccess(hr, "Unable to get root node name");

	  std::string rootNodeNameString = CW2A(rootNodeName, CP_UTF8);
	  return rootNodeNameString;
	  /*CComPtr<IHTMLHtmlElement> htmlElement;
	  hr = documentElement->QueryInterface(&htmlElement);
	  assertSuccess(hr, "Unable to get html element");*/


  }

  void assertSuccess(HRESULT hr, const char* message) {
	if (FAILED(hr)) {
		LOGHR(WARN, hr) << message;
		throw message;
    }
  }
};


} // namespace webdriver

#endif // WEBDRIVER_IE_PAGESTATEHANDLER_H_
