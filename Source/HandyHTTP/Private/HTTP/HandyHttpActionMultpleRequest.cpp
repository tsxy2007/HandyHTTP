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

void FHandyHttpActionMultpleRequest::GetObjects(const TArray<FString>& URL, const FString& SavePaths)
{
	SetPaths(SavePaths);
	for (const auto& Tmp : URL)
	{
		FHTTPClient Client;

		FGetObjectRequest Request(Tmp);

		REQUEST_BIND_FUN(FHandyHttpActionMultpleRequest);

		if (Client.GetObject(Request))
		{
			RequestNumber++;
		}
	}
}

bool FHandyHttpActionMultpleRequest::GetObject(const FString& URL, const FString& SavePaths)
{
	bool bResult = FHandyHttpActionRequest::GetObject(URL, SavePaths);
	if (bResult)
	{
		RequestNumber++;
	}
	return bResult;
}

bool FHandyHttpActionMultpleRequest::PutObject(const FString& URL, const FString& LocalPaths)
{
	SetPaths(LocalPaths);
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

void FHandyHttpActionMultpleRequest::DeleteObjects(const TArray<FString>& URL)
{
	//RequestNumber = URL.Num();
	for (auto& Tmp : URL)
	{
		FHTTPClient Client;

		FDeleteObjectRequest Request(Tmp);

		if (Client.DeleteObject(Request))
		{
			RequestNumber++;
		}
	}
}

void FHandyHttpActionMultpleRequest::HttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Request.IsValid() &&
		Response.IsValid() &&
		bConnectedSuccessfully &&
		EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		if (Request->GetVerb() == "GET")
		{
			FString FileName = FPaths::GetCleanFilename(Request->GetURL());
			FFileHelper::SaveArrayToFile(Response->GetContent(), *(GetPaths() / FileName));
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
	if (RequestNumber > 0)
	{
		RequestNumber--;
		if (RequestNumber <= 0)
		{
			HandyAllRequestCompleteDelegate.ExecuteIfBound();
			AllTasksCompletedDelegate.ExecuteIfBound();
			delete this;
		}
	}
	else
	{
		check(0);
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

