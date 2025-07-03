#pragma once
#include "RootService.h"
#include <SecurityMiddleware/SecurityMiddleware.h>
#include <windows.h>
#include <Tools/Tools.h>
#include <ThreadPool/ThreadPool.h>
#include <fmt/format.h>
RootService* RootService::m_instance = nullptr;
// Implementation
RootService::RootService(LPCWSTR pszServiceName,
    DWORD dwArgc,
    LPCWSTR* pszArgv,
    BOOL fCanStop,
    BOOL fCanShutdown,
    BOOL fCanPauseContinue)
    : CServiceBase(pszServiceName, fCanStop, fCanShutdown, fCanPauseContinue)
{
    m_dwArgc = dwArgc;
    m_pszArgv = pszArgv;
    m_instance = this;

    loadConfig(); 
}

RootService::~RootService()
{
    //StopDrogon();
}
void RootService::OnStartDebug(DWORD dwArgc, PSTR* pszArgv)
{
    RunDrogon();
}

void RootService::OnStart(DWORD dwArgc, PSTR* pszArgv)
{
    // Write to event log
    WriteEventLogEntry(L"Service starting...", EVENTLOG_INFORMATION_TYPE);

    try
    {
        CThreadPool::QueueUserWorkItem(&RootService::RunDrogon, this);
        Sleep(1000); 
        WriteEventLogEntry(L"Service started successfully", EVENTLOG_INFORMATION_TYPE);
    }
    catch (const std::exception& e)
    {
        std::wstring errorMsg = L"Failed to start Service: ";
        std::string errorStr = e.what();
        errorMsg += std::wstring(errorStr.begin(), errorStr.end());
        WriteEventLogEntry(errorMsg.c_str(), EVENTLOG_ERROR_TYPE);
        throw;
    }
}

void RootService::OnStop()
{
    WriteEventLogEntry(L"Service stopping...", EVENTLOG_INFORMATION_TYPE);

    StopDrogon();

    WriteEventLogEntry(L"Service stopped", EVENTLOG_INFORMATION_TYPE);
}

void RootService::OnPause()
{
    WriteEventLogEntry(L"Service paused", EVENTLOG_INFORMATION_TYPE);
    // Note: Drogon doesn't have built-in pause/resume, 
    // you might need to implement custom logic here
}

BOOL RootService::ConsoleCtrlHandler(DWORD ctrlType)
{
    switch (ctrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_BREAK_EVENT:
        s_service->Stop();
        return TRUE;
    default:
        return FALSE;
    }
}

void RootService::loadConfig()
{
    config = Tools::readFile(Tools::getExePath() + "/Config/config.json");
}

std::string RootService::getConfig()
{
    return config; 
}
void RootService::RunDrogon()
{
    try
    {
        initDrogon(); 

        WriteEventLogEntry(L"Drogon inited !", EVENTLOG_INFORMATION_TYPE);

        APP.getLoop()->runAfter(1, [&]() {

            auto servicename = Tools::LPCWSTRToString(GetName());
            LOG_INFO << fmt::format("{} is running at http://{}\n", servicename, APP.getListeners().at(0).toIpPort());
        });

        APP.run(); 

      
    }
    catch (const std::exception& e)
    {
        std::wstring errorMsg = L"Drogon runtime error: ";
        std::string errorStr = e.what();
        errorMsg += std::wstring(errorStr.begin(), errorStr.end());
        WriteEventLogEntry(errorMsg.c_str(), EVENTLOG_ERROR_TYPE);
    }

}

void RootService::initDrogon()
{
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

    std::string exePath = Tools::getExePath(); 

    APP.loadConfigFile(exePath + "/Config/config.json");

#ifdef _DEBUG
    APP.setLogPath("");
#elif NDEBUG
    APP.setLogPath(exePath + "/Log/", "logs", 100000000, 10);

#endif
}
void RootService::StopDrogon()
{
    WriteEventLogEntry(L"Drogon quiting...", EVENTLOG_INFORMATION_TYPE);

    APP.quit();

    WriteEventLogEntry(L"Drogon quited !", EVENTLOG_INFORMATION_TYPE);
}
