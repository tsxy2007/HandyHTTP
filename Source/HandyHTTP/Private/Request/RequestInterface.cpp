#include "Request/RequestInterface.h"
#include "HttpModule.h"

HandyHTTP::HTTP::IHTTPClientRequest::IHTTPClientRequest()
	:HttpRequest(FHttpModule::Get().CreateRequest())
{

}

bool HandyHTTP::HTTP::IHTTPClientRequest::ProcessRequest()
{
	return HttpRequest->ProcessRequest();
}

void HandyHTTP::HTTP::IHTTPClientRequest::CancelRequest()
{
	HttpRequest->CancelRequest();
}

