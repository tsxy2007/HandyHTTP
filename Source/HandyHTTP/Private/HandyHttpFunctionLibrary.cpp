// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHttpFunctionLibrary.h"
#include "HandyHttpManage.h"
#include "HTTP/HandyHttpActionRequest.h"

FString UHandyHttpFunctionLibrary::RegistedHttpObject(FHandyHttpRequestCompleteDelegate HandyHttpRequestCompleteDelegate /*= FHandyHttpRequestCompleteDelegate()*/, FHandyHttpRequestProgressDelegate HandyHttpRequestProgressDelegate /*= FHandyHttpRequestProgressDelegate()*/, FHandyHttpRequestHeaderReceivedDelegate FHandyHttpRequestHeaderReceivedDelegate /*= FHandyHttpRequestHeaderReceivedDelegate()*/)
{
	return FHandyHttpManage::Get()->RegistedHttpObject(HandyHttpRequestCompleteDelegate, HandyHttpRequestProgressDelegate, FHandyHttpRequestHeaderReceivedDelegate);
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
