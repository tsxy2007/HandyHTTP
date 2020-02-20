// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyHttpType.h"
#include "HandyHttpFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYHTTP_API UHandyHttpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,BlueprintPure, meta = (DisplayName = "HandyRegistedHttpObject", Keywords = "RHO"), Category = "HandyHttp")
	static FString RegistedHttpObject(FHandyHttpRequestCompleteDelegate HandyHttpRequestCompleteDelegate ,FHandyHttpRequestProgressDelegate HandyHttpRequestProgressDelegate,FHandyHttpRequestHeaderReceivedDelegate HandyHttpRequestHeaderReceivedDelegate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HandyGetObject", Keywords = "GetObject"), Category = "HandyHttp")
	static bool GetObject(FString Handle, const FString& URL, const FString& SavePaths);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HandyPutObjectByData", Keywords = "PutObject1"), Category = "HandyHttp")
	static bool PutObjectByData(FString Handle, const FString& URL, TArray<uint8>& Data );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HandyPutObjectByLocalPaths", Keywords = "PutObject2"), Category = "HandyHttp")
	static bool PutObjectByLocalPaths(FString Handle, const FString& URL, const FString& LocalPaths);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HandyDeleteObject", Keywords = "DeleteObject"), Category = "HandyHttp")
	static bool DeleteObject(FString Handle, const FString& URL);
};
