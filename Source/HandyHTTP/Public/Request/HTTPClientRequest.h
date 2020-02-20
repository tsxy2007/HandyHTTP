#pragma once

#include "CoreMinimal.h"
#include "Request/RequestInterface.h"

class IHttpRequest;
namespace HandyHTTP
{
	namespace HTTP
	{
		struct HANDYHTTP_API FPutObjectRequest : public IHTTPClientRequest
		{
			FPutObjectRequest(const FString& URL, const FString& ContentString);
			FPutObjectRequest(const FString& URL, TArray<uint8>& ContentPayLoad);
			FPutObjectRequest(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
		};

		struct HANDYHTTP_API FGetObjectRequest : public IHTTPClientRequest
		{
			FGetObjectRequest(const FString& URL);
		};


		struct HANDYHTTP_API FDeleteObjectRequest : public IHTTPClientRequest
		{
			FDeleteObjectRequest(const FString& URL);
		};
	}
}