#pragma once

#include "CoreMinimal.h"
#include "HandyHttpActionRequest.h"

class HANDYHTTP_API FHandyHttpActionMultpleRequest : public FHandyHttpActionRequest
{
public:
	FHandyHttpActionMultpleRequest();

	virtual bool GetObject(const FString& URL, const FString& SavePaths);
	virtual bool PutObject(const FString& URL, const FString& LocalPaths);
protected:
	void HttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
	void HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);
private:
	int32 RequestNumber = 0;
};