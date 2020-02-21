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
	virtual ~FHandyHttpActionRequest();

	//static FHandyHttpActionRequest* Get();
	//static void Destory();


public:

	virtual bool GetObject(const FString& URL, const FString& SavePaths);
	virtual bool PutObject(const FString& URL, TArray<uint8>& Data);
	virtual bool PutObject(const FString& URL, const FString& LocalPaths);
	virtual bool PutObject(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
	virtual bool DeleteObject(const FString& URL);

	FORCEINLINE FString GetPaths() { return TmpSavePaths; }
protected:
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
