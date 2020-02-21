// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandyHttpType.generated.h"

UENUM(BlueprintType)
enum class FHandyHttpState : uint8
{
	NotStarted,
	Processing,
	Failed,
	Failed_ConnectionError,
	Successed,
};

USTRUCT(BlueprintType)
struct FHandyHttpBase
{
	GENERATED_BODY()

	FHandyHttpBase() {}
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=HandyHttpBase)
	FString URL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpBase)
	TArray<FString> AllHeaders;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpBase)
	FString ContentType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpBase)
	int32 ContentLength;

};


USTRUCT(BlueprintType)
struct FHandyHttpRequest : public FHandyHttpBase
{
	GENERATED_USTRUCT_BODY()


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpRequest)
	FString Verb;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpRequest)
	float ElapsedTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpRequest)
	FHandyHttpState Status;
};


USTRUCT(BlueprintType)
struct  FHandyHttpResponse : public FHandyHttpBase
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpResponse)
	int32 ResponseCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HandyHttpResponse)
	FString ResponseMessage;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHandyHttpRequestCompleteDelegate, const FHandyHttpRequest&, Request, const FHandyHttpResponse&, Response, bool, bConnectedSuccessfully);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHandyHttpRequestProgressDelegate, const FHandyHttpRequest&, Request, int32, BytesSent, int32, BytesReceived);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHandyHttpRequestHeaderReceivedDelegate, const FHandyHttpRequest&, Request, const FString&, HeaderName, const FString&, NewHeaderValue);


