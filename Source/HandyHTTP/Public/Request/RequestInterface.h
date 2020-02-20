#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

class IHttpRequest;
namespace HandyHTTP
{
	namespace HTTP
	{
		struct HANDYHTTP_API IHTTPClientRequest
		{
			friend struct FHTTPClient;
			IHTTPClientRequest();

			IHTTPClientRequest& operator<<(const FHttpRequestCompleteDelegate& HttpRequestCompleteDelegate)
			{
				HttpRequest->OnProcessRequestComplete() = HttpRequestCompleteDelegate;
				return *this;
			}

			IHTTPClientRequest& operator<<(const FHttpRequestHeaderReceivedDelegate HttpRequestHeaderReceivedDelegate)
			{
				HttpRequest->OnHeaderReceived() = HttpRequestHeaderReceivedDelegate;
				return *this;
			}

			IHTTPClientRequest& operator<<(const FHttpRequestProgressDelegate HttpRequestProgressDelegate)
			{
				HttpRequest->OnRequestProgress() = HttpRequestProgressDelegate;
				return *this;
			}

		protected:
			bool ProcessRequest();
			void CancelRequest();


		protected:
			TSharedPtr<IHttpRequest> HttpRequest;
		};
	}
}