#include "Client/HTTPClient.h"

HandyHTTP::HTTP::FHTTPClient::FHTTPClient()
{

}

bool HandyHTTP::HTTP::FHTTPClient::GetObject(FGetObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

bool HandyHTTP::HTTP::FHTTPClient::DeleteObject(FDeleteObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

bool HandyHTTP::HTTP::FHTTPClient::PutObject(FPutObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

void HandyHTTP::HTTP::FHTTPClient::AbortRequest(IHTTPClientRequest& Request)
{
	Request.CancelRequest();
}
