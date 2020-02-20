// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HANDYHTTP_API FHandyHttpManage
{
public:
	FHandyHttpManage();
	~FHandyHttpManage();

	static FHandyHttpManage* Get();
	static void Destory();

	

	FString RegistedHttpObject(
		FHandyHttpRequestCompleteDelegate			HandyHttpRequestCompleteDelegate = FHandyHttpRequestCompleteDelegate(),
		FHandyHttpRequestProgressDelegate			HandyHttpRequestProgressDelegate = FHandyHttpRequestProgressDelegate(),
		FHandyHttpRequestHeaderReceivedDelegate		HandyHttpRequestHeaderReceivedDelegate = FHandyHttpRequestHeaderReceivedDelegate()
	);

	FHandyHttpActionRequest* Find(FString& handle);
private:
	static FHandyHttpManage* Instance;
	FCriticalSection Mutex;
	TMap<FString, FHandyHttpActionRequest*> HTTPMap;
};
