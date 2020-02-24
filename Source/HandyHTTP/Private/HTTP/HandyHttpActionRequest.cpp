// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/HandyHttpActionRequest.h"
#include "Client/HTTPClient.h"
#include "Request/HTTPClientRequest.h"
#include "Core/HandyHttpMacro.h"
#include "Engine.h"
#include "IHttpResponse.h"
#include "IHttpRequest.h"
#include "HandyHttpType.h"

using namespace HandyHTTP::HTTP;

//FHandyHttpActionRequest* FHandyHttpActionRequest::Instance = nullptr;

FHandyHttpActionRequest::FHandyHttpActionRequest()
{
}

FHandyHttpActionRequest::~FHandyHttpActionRequest()
{
}

void FHandyHttpActionRequest::GetObjects(const TArray<FString>& URL, const FString& SavePaths)
{

}

void FHandyHttpActionRequest::DeleteObjects(const TArray<FString>& URL)
{

}

//
//FHandyHttpActionRequest* FHandyHttpActionRequest::Get()
//{
//	if (Instance == nullptr)
//	{
//		Instance = new FHandyHttpActionRequest;
//	}
//	return Instance;
//}
//
//void FHandyHttpActionRequest::Destory()
//{
//	if (Instance)
//	{
//		delete Instance;
//	}
//	Instance = nullptr;
//}

bool FHandyHttpActionRequest::GetObject(const FString& URL, const FString& SavePaths)
{
	TmpSavePaths = SavePaths;
	FHTTPClient Client;

	FGetObjectRequest Request(URL);

	REQUEST_BIND_FUN(FHandyHttpActionRequest);

	return Client.GetObject(Request);
}

bool FHandyHttpActionRequest::PutObject(const FString& URL, const FString& LocalPaths)
{
	FHTTPClient Client;

	FPutObjectRequest Request(URL, LocalPaths);

	REQUEST_BIND_FUN(FHandyHttpActionRequest);

	return Client.PutObject(Request);
}

bool FHandyHttpActionRequest::PutObject(const FString& URL, TArray<uint8>& Data)
{
	FHTTPClient Client;

	FPutObjectRequest Request(URL, Data);

	REQUEST_BIND_FUN(FHandyHttpActionRequest);

	return Client.PutObject(Request);
}

bool FHandyHttpActionRequest::PutObject(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream)
{
	FHTTPClient Client;

	FPutObjectRequest Request(URL, Stream);

	REQUEST_BIND_FUN(FHandyHttpActionRequest);

	return Client.PutObject(Request);
}

bool FHandyHttpActionRequest::DeleteObject(const FString& URL)
{
	FHTTPClient Client;

	FDeleteObjectRequest Request(URL);

	return Client.DeleteObject(Request);
}

void FHandyHttpActionRequest::HttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Request.IsValid()&& 
		Response.IsValid()&& 
		bConnectedSuccessfully && 
		EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		const FString& VerbStr = Request->GetVerb();
		if (VerbStr== "GET")
		{
			FString FileName = FPaths::GetCleanFilename(Request->GetURL());
			FFileHelper::SaveArrayToFile(Response->GetContent(), *(TmpSavePaths / FileName));
		}
		else if (VerbStr == "PUT")
		{
		}
		else if (VerbStr == "DELETE")
		{
		}

		FHandyHttpRequest HandyHttpRequest;
		FHandyHttpResponse HandyHttpResponse;
		{
			HttpRequestPtrToHandyRequest(Request, HandyHttpRequest);
			HttpResponsePtrToHandyResponse(Response, HandyHttpResponse);
		}
		HandyHttpRequestCompleteDelegate.ExecuteIfBound(HandyHttpRequest, HandyHttpResponse, bConnectedSuccessfully);
		HandyCompleteDelegate.ExecuteIfBound(HandyHttpRequest, HandyHttpResponse, bConnectedSuccessfully);
	}
	else
	{
		FHandyHttpRequest HandyHttpRequest;
		FHandyHttpResponse HandyHttpResponse;
		{
			HttpRequestPtrToHandyRequest(Request, HandyHttpRequest);
			HttpResponsePtrToHandyResponse(Response, HandyHttpResponse);
		}
		HandyHttpRequestCompleteDelegate.ExecuteIfBound(HandyHttpRequest, HandyHttpResponse, bConnectedSuccessfully);
		HandyCompleteDelegate.ExecuteIfBound(HandyHttpRequest, HandyHttpResponse, bConnectedSuccessfully);
	}

	HandyAllRequestCompleteDelegate.ExecuteIfBound();
	AllTasksCompletedDelegate.ExecuteIfBound();
	delete this;
}

void FHandyHttpActionRequest::HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	FHandyHttpRequest HandyHttpRequest;
	HttpRequestPtrToHandyRequest(Request, HandyHttpRequest);
	HandyHttpRequestProgressDelegate.ExecuteIfBound(HandyHttpRequest, BytesSent, BytesReceived);
	HandySingleRequestProgressDelegate.ExecuteIfBound(HandyHttpRequest, BytesSent, BytesReceived);
}

void FHandyHttpActionRequest::HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue)
{
	FHandyHttpRequest HandyHttpRequest;
	HttpRequestPtrToHandyRequest(Request, HandyHttpRequest);
	HandyHttpRequestHeaderReceivedDelegate.ExecuteIfBound(HandyHttpRequest, HeaderName, NewHeaderValue);
	HandySingleRequestHeaderReceivedDelegate.ExecuteIfBound(HandyHttpRequest, HeaderName, NewHeaderValue);
}

void FHandyHttpActionRequest::Print(const FString& Msg, float Time /*= 10.f*/, FColor Color /*= FColor::Red*/)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, Msg);
	}
}
