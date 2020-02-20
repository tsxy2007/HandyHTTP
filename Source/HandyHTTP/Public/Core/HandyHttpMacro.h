#pragma once

#define DEFINITION_HTTP_TYPE(VerbString,Content) \
HttpRequest->SetURL(URL); \
HttpRequest->SetVerb(TEXT(##VerbString)); \
HttpRequest->SetHeader(TEXT("Content-Type"), TEXT(##Content));

#define  REQUEST_BIND_FUN()\
Request\
<< FHttpRequestCompleteDelegate::CreateRaw(this, &FHandyHttpActionRequest::HttpRequestCompleted) \
<< FHttpRequestProgressDelegate::CreateRaw(this, &FHandyHttpActionRequest::HttpRequestProgress)\
<< FHttpRequestHeaderReceivedDelegate::CreateRaw(this, &FHandyHttpActionRequest::HttpRequestHeaderReceived);