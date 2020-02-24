// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHttpFunctionLibrary.h"
#include "HandyHttpManage.h"
#include "HTTP/HandyHttpActionRequest.h"

FString UHandyHttpFunctionLibrary::RegistedHttpRequest( FHandyHttpSingleRequestCompleteDelegate HandyHttpRequestCompleteDelegate, FHandyHttpSingleRequestProgressDelegate HandyHttpRequestProgressDelegate, FHandyHttpSingleRequestHeaderReceivedDelegate FHandyHttpSingleRequestHeaderReceivedDelegate , FHandyAllRequestCompleteDelegate HandyAllRequestCompleteDelegate)
{
	return FHandyHttpManage::Get()->RegistedHttpRequest( EHTTPRequestType::SINGLE,HandyHttpRequestCompleteDelegate, HandyHttpRequestProgressDelegate, FHandyHttpSingleRequestHeaderReceivedDelegate, HandyAllRequestCompleteDelegate);
}

FString UHandyHttpFunctionLibrary::RegistedHttpMultpleRequest(FHandyHttpSingleRequestCompleteDelegate HandyHttpRequestCompleteDelegate, FHandyHttpSingleRequestProgressDelegate HandyHttpRequestProgressDelegate, FHandyHttpSingleRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate, FHandyAllRequestCompleteDelegate HandyAllRequestCompleteDelegate)
{
	return FHandyHttpManage::Get()->RegistedHttpRequest(EHTTPRequestType::MULTPLE, HandyHttpRequestCompleteDelegate, HandyHttpRequestProgressDelegate, HandyHttpRequestHeaderReceivedDelegate, HandyAllRequestCompleteDelegate);
}

void UHandyHttpFunctionLibrary::GetObjects(FString Handle, const TArray<FString>& URL, const FString& SavePaths)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		NewAction->GetObjects(URL, SavePaths);
	}
}

bool UHandyHttpFunctionLibrary::GetObject(FString Handle, const FString& URL, const FString& SavePaths)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		return NewAction->GetObject(URL, SavePaths);
	}
	return false;
}

bool UHandyHttpFunctionLibrary::PutObjectByData(FString Handle, const FString& URL, TArray<uint8>& Data)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		return NewAction->PutObject(URL, Data);
	}
	return false;
}

bool UHandyHttpFunctionLibrary::PutObjectByLocalPaths(FString Handle, const FString& URL, const FString& LocalPaths)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		return NewAction->PutObject(URL, LocalPaths);
	}
	return false;
}

bool UHandyHttpFunctionLibrary::DeleteObject(FString Handle, const FString& URL)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		return NewAction->DeleteObject(URL);
	}
	return false;
}

void UHandyHttpFunctionLibrary::DeleteObjects(FString Handle, const TArray<FString>& URL)
{
	FHandyHttpActionRequest* NewAction = FHandyHttpManage::Get()->Find(Handle);
	if (NewAction)
	{
		NewAction->DeleteObjects(URL);
	}
}
