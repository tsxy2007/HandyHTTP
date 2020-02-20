// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHttpManage.h"
#include "HTTP/HandyHttpActionRequest.h"

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

FString FHandyHttpManage::RegistedHttpObject(FHandyHttpRequestCompleteDelegate HandyHttpRequestCompleteDelegate, FHandyHttpRequestProgressDelegate HandyHttpRequestProgressDelegate, FHandyHttpRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate)
{

	FScopeLock Lock(&Instance->Mutex);
	FHandyHttpActionRequest* HttpObject = new FHandyHttpActionRequest();
	{
		HttpObject->HandyHttpRequestCompleteDelegate = HandyHttpRequestCompleteDelegate;
		HttpObject->HandyHttpRequestHeaderReceivedDelegate = HandyHttpRequestHeaderReceivedDelegate;
		HttpObject->HandyHttpRequestProgressDelegate = HandyHttpRequestProgressDelegate;
	}
	FString Key = FGuid::NewGuid().ToString();
	HTTPMap.Add(Key, HttpObject);
	return Key;
}

FHandyHttpActionRequest* FHandyHttpManage::Find(FString& handle)
{

	FScopeLock Lock(&Instance->Mutex);
	if (HTTPMap.Contains(handle))
	{
		return HTTPMap[handle];
	}
	return nullptr;
}
