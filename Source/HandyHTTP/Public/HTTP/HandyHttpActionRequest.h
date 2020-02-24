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
	// ¼æÈÝÀ¶Í¼
	virtual void GetObjects(const TArray<FString>& URL, const FString& SavePaths);
	virtual void DeleteObjects(const TArray<FString>& URL);

	//Õý³£
	virtual bool GetObject(const FString& URL, const FString& SavePaths);
	virtual bool PutObject(const FString& URL, TArray<uint8>& Data);
	virtual bool PutObject(const FString& URL, const FString& LocalPaths);
	virtual bool PutObject(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
	virtual bool DeleteObject(const FString& URL);

	FORCEINLINE FString GetPaths() { return TmpSavePaths; }
	FORCEINLINE void SetPaths(const FString& InPaths) { TmpSavePaths = InPaths; }
protected:
	void HttpRequestCompleted(FHttpRequestPtr Request,FHttpResponsePtr Response,bool bConnectedSuccessfully);
	void HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent,int32 BytesReceived);
	void HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);

	void Print(const FString& Msg, float Time = 10.f, FColor Color = FColor::Red);

public:
	// BP
	FHandyHttpSingleRequestCompleteDelegate HandyHttpRequestCompleteDelegate;
	FHandyHttpSingleRequestProgressDelegate HandyHttpRequestProgressDelegate;
	FHandyHttpSingleRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate;
	FHandyAllRequestCompleteDelegate HandyAllRequestCompleteDelegate;
	// C++
	FHandySingleRequestCompleteDelegate HandyCompleteDelegate;
	FHandySingleRequestProgressDelegate HandySingleRequestProgressDelegate;
	FHandySingleRequestHeaderReceivedDelegate HandySingleRequestHeaderReceivedDelegate;
	FSimpleDelegate  AllTasksCompletedDelegate;
private:
	//static FHandyHttpActionRequest* Instance;

	FCriticalSection Mutex;
	FString TmpSavePaths;
};
