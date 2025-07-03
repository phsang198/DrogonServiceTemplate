#pragma once
#include "RootService/RootService.h"

#define LICENSE_NAME             "TemplateService"

#define SERVICE_NAME             L"TemplateService"
// Displayed name of the service
#define SERVICE_DISPLAY_NAME     TEXT("TemplateService(C++)")
// Service start options.
#define SERVICE_START_TYPE       SERVICE_AUTO_START//SERVICE_DEMAND_START
// List of service dependencies - "dep1\0dep2\0\0"
#define SERVICE_DEPENDENCIES     TEXT("")
// The name of the account under which the service should run
#define SERVICE_ACCOUNT          TEXT("NT AUTHORITY\\LocalService")
// The password to the service account name
#define SERVICE_PASSWORD         NULL

class TemplateService : public RootService
{
public:
    TemplateService(LPCWSTR pszServiceName,
        DWORD dwArgc,
        LPCWSTR* pszArgv,
        BOOL fCanStop = TRUE,
        BOOL fCanShutdown = TRUE,
        BOOL fCanPauseContinue = FALSE)
        : RootService(pszServiceName, dwArgc, pszArgv, fCanStop, fCanShutdown, fCanPauseContinue) {}
    ~TemplateService();
public: 
    void RunDrogon() override;
};
