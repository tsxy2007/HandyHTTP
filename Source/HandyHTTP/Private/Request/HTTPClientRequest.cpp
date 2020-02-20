
#include "Request/HTTPClientRequest.h"
#include "Core/HandyHttpMacro.h"

HandyHTTP::HTTP::FPutObjectRequest::FPutObjectRequest(const FString& URL, const FString& ContentString)
{
	DEFINITION_HTTP_TYPE("PUT", "application/x-www-form-urlencoded");
	HttpRequest->SetContentAsString(ContentString);
}

HandyHTTP::HTTP::FPutObjectRequest::FPutObjectRequest(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream)
{
	DEFINITION_HTTP_TYPE("PUT", "application/x-www-form-urlencoded");
	HttpRequest->SetContentFromStream(Stream);
}

HandyHTTP::HTTP::FPutObjectRequest::FPutObjectRequest(const FString& URL, TArray<uint8>& ContentPayLoad)
{
	DEFINITION_HTTP_TYPE("PUT", "application/x-www-form-urlencoded");
	HttpRequest->SetContent(ContentPayLoad);
}

HandyHTTP::HTTP::FGetObjectRequest::FGetObjectRequest(const FString& URL)
{
	DEFINITION_HTTP_TYPE("GET", "application/x-www-form-urlencoded");
}

HandyHTTP::HTTP::FDeleteObjectRequest::FDeleteObjectRequest(const FString& URL)
{
	DEFINITION_HTTP_TYPE("DELETE", "application/x-www-form-urlencoded");
}
