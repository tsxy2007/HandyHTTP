#include "HTTP/HandyHttpActionMultpleRequest.h"
#include "Client/HTTPClient.h"
#include "Request/HTTPClientRequest.h"
#include "Core/HandyHttpMacro.h"
#include "FileManager.h"
#include "FileHelper.h"
#include "Paths.h"

using namespace HandyHTTP::HTTP;
FHandyHttpActionMultpleRequest::FHandyHttpActionMultpleRequest()
	:RequestNumber(0)
{

}

bool FHandyHttpActionMultpleRequest::GetObject(const FString& URL, const FString& SavePaths)
{
	return false;
}

bool FHandyHttpActionMultpleRequest::PutObject(const FString& URL, const FString& LocalPaths)
{
	TArray<FString> AllPaths;
	IFileManager::Get().FindFilesRecursive(AllPaths, *LocalPaths, TEXT("*"), true, true);
	for (const auto& Tmp : AllPaths)
	{
		TArray<uint8> ByteData;
		FFileHelper::LoadFileToArray(ByteData, *Tmp);

		FString ObjectName = FPaths::GetCleanFilename(Tmp);

		FHTTPClient Client;

		FPutObjectRequest Request(URL / ObjectName, ByteData);

		REQUEST_BIND_FUN(FHandyHttpActionMultpleRequest);

		if (Client.PutObject(Request))
		{
			RequestNumber++;
		}
	}
	return false;
}

void FHandyHttpActionMultpleRequest::HttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Request.IsValid() &&
		Response.IsValid() &&
		bConnectedSuccessfully &&
		EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{

		FHandyHttpRequest HandyHttpRequest;
		FHandyHttpResponse HandyHttpResponse;
		{
			HttpRequestPtrToHandyRequest(Request, HandyHttpRequest);
			HttpResponsePtrToHandyResponse(Response, HandyHttpResponse);
		}
		HandyHttpRequestCompleteDelegate.ExecuteIfBound(HandyHttpRequest, HandyHttpResponse, bConnectedSuccessfully);
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
	}
	if (RequestNumber > 0)
	{
		RequestNumber--;
	}
	else
	{
		delete this;
	}
}

void FHandyHttpActionMultpleRequest::HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	FHandyHttpActionRequest::HttpRequestProgress(Request, BytesSent, BytesReceived);
}

void FHandyHttpActionMultpleRequest::HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue)
{
	FHandyHttpActionRequest::HttpRequestHeaderReceived(Request, HeaderName, NewHeaderValue);
}

