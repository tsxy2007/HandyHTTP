// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHttpRequest.h"
#include "HandyHttpType.h"

/**
 * 
 */
class HANDYHTTP_API FHandyHttpActionRequest
{
public:
	FHandyHttpActionRequest();
	~FHandyHttpActionRequest();

	//static FHandyHttpActionRequest* Get();
	//static void Destory();


public:

	bool GetObject(const FString& URL, const FString& SavePaths);
	bool PutObject(const FString& URL, TArray<uint8>& Data);
	bool PutObject(const FString& URL, const FString& LocalPaths);
	bool PutObject(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
	bool DeleteObject(const FString& URL);
private:
	void HttpRequestCompleted(FHttpRequestPtr Request,FHttpResponsePtr Response,bool bConnectedSuccessfully);
	void HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent,int32 BytesReceived);
	void HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);

	void Print(const FString& Msg, float Time = 10.f, FColor Color = FColor::Red);

public:
	FHandyHttpRequestCompleteDelegate HandyHttpRequestCompleteDelegate;
	FHandyHttpRequestProgressDelegate HandyHttpRequestProgressDelegate;
	FHandyHttpRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate;
private:
	//static FHandyHttpActionRequest* Instance;

	FCriticalSection Mutex;
	FString TmpSavePaths;
};
