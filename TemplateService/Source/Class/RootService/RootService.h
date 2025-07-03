#pragma once

#include "ServiceBase/ServiceBase.h"  // Your existing CServiceBase
#include <drogon/drogon.h>
#include <string>

#define APP drogon::app()

class RootService : public CServiceBase
{
private:
    DWORD		         m_dwArgc;
    LPCWSTR* m_pszArgv;
    static RootService* m_instance;
protected:
    std::string config; 
public:
    RootService(LPCWSTR pszServiceName,
        DWORD dwArgc,
        LPCWSTR* pszArgv,
        BOOL fCanStop = TRUE,
        BOOL fCanShutdown = TRUE,
        BOOL fCanPauseContinue = FALSE);

    ~RootService() override;
public:
    LPCWSTR GetName() { return m_name; }
public:
    // Override CServiceBase methods
    void OnStart(DWORD dwArgc, PSTR* pszArgv) override;
    void OnStartDebug(DWORD dwArgc, PSTR* pszArgv) override;
    void OnStop() override;
    void OnPause() override;

private:
    static BOOL __stdcall ConsoleCtrlHandler(DWORD ctrlType);

protected:
    std::string getConfig();
    virtual void RunDrogon();
private:
    void loadConfig();
    virtual void initDrogon() final;
    virtual void StopDrogon() final;
};
