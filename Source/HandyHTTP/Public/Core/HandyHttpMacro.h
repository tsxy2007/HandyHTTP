#pragma once
#include "IHttpRequest.h"
#include "IHttpResponse.h"

#define DEFINITION_HTTP_TYPE(VerbString,Content) \
HttpRequest->SetURL(URL); \
HttpRequest->SetVerb(TEXT(##VerbString)); \
HttpRequest->SetHeader(TEXT("Content-Type"), TEXT(##Content));

#define  REQUEST_BIND_FUN(RequestClass)\
Request\
<< FHttpRequestCompleteDelegate::CreateRaw(this, &##RequestClass##::HttpRequestCompleted) \
<< FHttpRequestProgressDelegate::CreateRaw(this, &##RequestClass##::HttpRequestProgress)\
<< FHttpRequestHeaderReceivedDelegate::CreateRaw(this, &##RequestClass##::HttpRequestHeaderReceived);


void HttpRequestPtrToHandyRequest(FHttpRequestPtr Request, FHandyHttpRequest& HandyHttpRequest)
{
	if (Request.IsValid())
	{
		HandyHttpRequest.Verb = Request->GetVerb();
		HandyHttpRequest.URL = Request->GetURL();
		HandyHttpRequest.Status = (FHandyHttpState)Request->GetStatus();
		HandyHttpRequest.ElapsedTime = Request->GetElapsedTime();
		HandyHttpRequest.ContentType = Request->GetContentType();
		HandyHttpRequest.ContentLength = Request->GetContentLength();
		HandyHttpRequest.AllHeaders = Request->GetAllHeaders();
	}
}

void HttpResponsePtrToHandyResponse(FHttpResponsePtr Response, FHandyHttpResponse& HandyHttpResponse)
{
	if (Response.IsValid())
	{
		HandyHttpResponse.ResponseCode = Response->GetResponseCode();
		HandyHttpResponse.URL = Response->GetURL();
		HandyHttpResponse.ResponseMessage = Response->GetContentAsString();
		HandyHttpResponse.ContentType = Response->GetContentType();
		HandyHttpResponse.ContentLength = Response->GetContentLength();
		HandyHttpResponse.AllHeaders = Response->GetAllHeaders();
	}
}