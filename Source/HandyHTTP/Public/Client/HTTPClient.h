#pragma once

#include "CoreMinimal.h"
#include "Request/HTTPClientRequest.h"

namespace HandyHTTP
{
	namespace HTTP
	{
		struct HANDYHTTP_API FHTTPClient
		{
			FHTTPClient();

			bool GetObject(FGetObjectRequest& Request) const;
			bool DeleteObject(FDeleteObjectRequest& Request) const;
			bool PutObject(FPutObjectRequest& Request) const;

			void AbortRequest(IHTTPClientRequest& Request);
		};
	}
}