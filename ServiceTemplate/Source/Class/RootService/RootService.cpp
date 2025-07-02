#pragma once
#include "RootService.h"
#include <windows.h>
#include "ThreadPool/ThreadPool.h"

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

    initDrogon();
}

RootService::~RootService()
{
    StopDrogon();
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
        RunDrogon(); 
        //CThreadPool::QueueUserWorkItem(&RootService::RunDrogon, this);

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
std::string RootService::getConfig()
{
    return APP.getCustomConfig().toStyledString();
}
void RootService::RunDrogon()
{
    try
    {
        drogon::app().getLoop()->runAfter(1, [] {
            LOG_INFO << "Start success!";
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
    WriteEventLogEntry(L"Service initing...", EVENTLOG_INFORMATION_TYPE);


    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

    APP.loadConfigFile("./Config/config.json");


    WriteEventLogEntry(L"Service inited !", EVENTLOG_INFORMATION_TYPE);

}
void RootService::StopDrogon()
{
    APP.quit();
}
