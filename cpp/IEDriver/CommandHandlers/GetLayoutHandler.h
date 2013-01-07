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

#ifndef WEBDRIVER_IE_GETLAYOUTHANDLER_H_
#define WEBDRIVER_IE_GETLAYOUTHANDLER_H_

#include "../Browser.h"
#include "../IECommandHandler.h"
#include "../IECommandExecutor.h"
#include "logging.h"

namespace webdriver {

class GetLayoutHandler : public IECommandHandler {
 public:
  GetLayoutHandler(void) {
  }

  virtual ~GetLayoutHandler(void) {
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

	Json::Value jsonLayout(Json::objectValue);
	try {
	  fetchLayout(browser_wrapper, jsonLayout);
	  response->SetSuccessResponse(jsonLayout);
	} catch(int code){
	  response->SetErrorResponse(code, "System Error. IE communication issue."); 
	}
	
  }

  void fetchLayout(BrowserHandle& browser_wrapper, Json::Value& jsonLayout) {
	CComPtr<IHTMLDocument2> doc2;
	browser_wrapper->GetDocument(&doc2);
	assertReference(doc2, 1000, "GetLayoutHandler::fetchLayout can't obtain IHTMLDocument3");

	CComPtr<IHTMLDocument3> doc3;
	HRESULT hr = doc2->QueryInterface(&doc3);
	assertReference(hr, doc3, 1001, "GetLayoutHandler::fetchLayout can't obtain IHTMLDocument3");
	
	CComPtr<IHTMLElement> documentElement;
	hr = doc3->get_documentElement(&documentElement);
	assertReference(hr, documentElement, 1002, "GetLayoutHandler::fetchLayout can't obtain IHTMLElement of document");

	fetchChildren(documentElement, jsonLayout);
  }

  void fetchChildren(CComPtr<IHTMLElement>& element, Json::Value& jsonElement) {
	CComPtr<IDispatch> childrenDispatcher;
	HRESULT hr = element->get_children(&childrenDispatcher);
	assertReference(hr, childrenDispatcher, 1003, "GetLayoutHandler::fetchChildren can't obtain IDispatch of children");

	CComPtr<IHTMLElementCollection> childrenCollection;
	hr = childrenDispatcher->QueryInterface(&childrenCollection);
	assertReference(hr, childrenCollection, 1004, "GetLayoutHandler::fetchChildren can't obtain IHTMLElementCollection");

	long childrenCount;
	hr = childrenCollection->get_length(&childrenCount);
	assertHRESULT(hr, 1005, "GetLayoutHandler::fetchChildren can't obtain children count");

	CComBSTR tagName;
	hr = element->get_tagName(&tagName);
	assertHRESULT(hr, 1006, "GetLayoutHandler::fetchChildren can't obtain tag name");
	std::string tagNameString = CW2A(tagName, CP_UTF8);

	jsonElement["tagName"] = tagNameString;
	jsonElement["childrenCount"] = childrenCount;
	
	Json::Value jsonChildren(Json::arrayValue);
	for(long i = 0; i < childrenCount; i++) {
		VARIANT index;
		index.vt = VT_I4;
		index.lVal = i;
		CComPtr<IDispatch> itemDispatcher;
		hr = childrenCollection->item(index, index, &itemDispatcher);
		assertReference(hr, itemDispatcher, 1007, "GetLayoutHandler::fetchChildren can't obtain next item");

		CComPtr<IHTMLElement> childElement;
		hr = itemDispatcher->QueryInterface(&childElement);
		assertReference(hr, itemDispatcher, 1008, "GetLayoutHandler::fetchChildren can't obtain IHTMLElement of child");

		Json::Value jsonChild(Json::objectValue);
		fetchChildren(childElement, jsonChild);

		jsonChildren.append(jsonChild);
	}
	jsonElement["children"] = jsonChildren; 
  }

  void assertHRESULT(HRESULT hr, int code, const char* message) {
    if (FAILED(hr)) {
		LOGHR(WARN, hr) << message;
		throw code;
	}
  }
  
  template<class T>
  void assertReference(HRESULT hr, T& p, int code, const char* message) {
    if (FAILED(hr) || p == NULL) {
		LOGHR(WARN, hr) << message;
		throw code;
	}
  }

  template<class T>
  void assertReference(T& p, int code, const char* message) {
    if (p == NULL) {
		LOG(WARN) << message;
		throw code;
	}
  }
};

} // namespace webdriver


#endif // WEBDRIVER_IE_GETLAYOUTHANDLER_H_