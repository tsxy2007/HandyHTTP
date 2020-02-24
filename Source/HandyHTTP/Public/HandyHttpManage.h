// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandyHttpType.h"
#include "HTTP/HandyHttpActionRequest.h"

UENUM(BlueprintType)
enum class EHTTPRequestType : uint8
{
	SINGLE,
	MULTPLE,
};


class HANDYHTTP_API FHandyHttpManage
{
public:
	FHandyHttpManage();
	~FHandyHttpManage();

	static FHandyHttpManage* Get();
	static void Destory();

	

	FString RegistedHttpRequest(EHTTPRequestType HttpRequestType = EHTTPRequestType::SINGLE,
		FHandyHttpSingleRequestCompleteDelegate			HandyHttpRequestCompleteDelegate = FHandyHttpSingleRequestCompleteDelegate(),
		FHandyHttpSingleRequestProgressDelegate			HandyHttpRequestProgressDelegate = FHandyHttpSingleRequestProgressDelegate(),
		FHandyHttpSingleRequestHeaderReceivedDelegate		HandyHttpRequestHeaderReceivedDelegate = FHandyHttpSingleRequestHeaderReceivedDelegate(),
		FHandyAllRequestCompleteDelegate HandyAllRequestCompleteDelegate = FHandyAllRequestCompleteDelegate()
	);

	FHandyHttpActionRequest* Find(FString& handle);
private:
	static FHandyHttpManage* Instance;
	FCriticalSection Mutex;
	TMap<FString, FHandyHttpActionRequest*> HTTPMap;
};
