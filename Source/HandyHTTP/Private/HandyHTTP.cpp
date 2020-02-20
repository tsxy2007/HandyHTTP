// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HandyHTTP.h"
#include "HTTP/HandyHttpActionRequest.h"
#include "HandyHttpManage.h"

#define LOCTEXT_NAMESPACE "FHandyHTTPModule"

void FHandyHTTPModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHandyHTTPModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FHandyHttpManage::Destory();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHandyHTTPModule, HandyHTTP)