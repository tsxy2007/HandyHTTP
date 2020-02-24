// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHttpManage.h"
#include "HTTP/HandyHttpActionRequest.h"
#include "HTTP/HandyHttpActionMultpleRequest.h"

FHandyHttpManage* FHandyHttpManage::Instance = nullptr;

FHandyHttpManage::FHandyHttpManage()
{
}

FHandyHttpManage::~FHandyHttpManage()
{
}

FHandyHttpManage* FHandyHttpManage::Get()
{
	if (Instance == nullptr)
	{
		FScopeLock Lock(&Instance->Mutex);
		Instance = new FHandyHttpManage();
	}
	return Instance;
}

void FHandyHttpManage::Destory()
{
	if (Instance)
	{
		delete Instance;
	}
	Instance = nullptr;
}

FString FHandyHttpManage::RegistedHttpRequest(
	EHTTPRequestType HttpRequestType /*= EHTTPRequestType::SINGLE*/, 
	FHandyHttpSingleRequestCompleteDelegate HandyHttpRequestCompleteDelegate /*= FHandyHttpSingleRequestCompleteDelegate()*/,
	FHandyHttpSingleRequestProgressDelegate HandyHttpRequestProgressDelegate /*= FHandyHttpSingleRequestProgressDelegate()*/,
	FHandyHttpSingleRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate /*= FHandyHttpSingleRequestHeaderReceivedDelegate() */,
	FHandyAllRequestCompleteDelegate HandyAllRequestCompleteDelegate /*= FHandyAllRequestCompleteDelegate()*/
)
{
	FScopeLock Lock(&Instance->Mutex);
	FHandyHttpActionRequest* HttpObject = nullptr;
	switch (HttpRequestType)
	{
	case EHTTPRequestType::SINGLE:
	{
		HttpObject = new FHandyHttpActionRequest();
	}
		break;
	case EHTTPRequestType::MULTPLE:
	{
		HttpObject = new FHandyHttpActionMultpleRequest();
	}
		break;
	default:
		break;
	}
	{
		HttpObject->HandyHttpRequestCompleteDelegate = HandyHttpRequestCompleteDelegate;
		HttpObject->HandyHttpRequestHeaderReceivedDelegate = HandyHttpRequestHeaderReceivedDelegate;
		HttpObject->HandyHttpRequestProgressDelegate = HandyHttpRequestProgressDelegate;
		HttpObject->HandyAllRequestCompleteDelegate = HandyAllRequestCompleteDelegate;
	}
	
	FString Key = FGuid::NewGuid().ToString();
	HTTPMap.Add(Key, HttpObject);
	return Key;
}

FHandyHttpActionRequest* FHandyHttpManage::Find(FString& handle)
{

	FScopeLock Lock(&Instance->Mutex);

	FHandyHttpActionRequest* Object = nullptr;
	if (HTTPMap.Contains(handle))
	{
		Object = Instance->HTTPMap[handle];
		Instance->HTTPMap.Remove(handle);
	}
	return Object;
}
