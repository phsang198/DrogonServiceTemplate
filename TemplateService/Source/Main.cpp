// Example usage of RootService
#include "TemplateService.h"
#include "ServiceInstaller/ServiceInstaller.h"  // Your existing ServiceInstaller
#include <iostream>
#include <tchar.h>
int _tmain(int argc, _TCHAR* argv[])
{
    std::wstring szCurDir(argv[0]), szModuleName(argv[0]);
    int nIndex = static_cast<int>(szCurDir.find_last_of(L"\\"));
    szCurDir = szCurDir.substr(0, nIndex + 1);
    szModuleName = szModuleName.substr(nIndex + 1, szModuleName.find_last_of(L".exe") - nIndex - 4);

    TemplateService service(szModuleName.c_str(), argc, const_cast<LPCWSTR*>(argv));

#ifdef _DEBUG
    CServiceBase::RunDebug(service);
#else
    std::string szFileLic, szProductName = LICENSE_NAME;
    //std::shared_ptr<CLicenseManager> pLicMngr = service.GetLicenseManager();
    //pLicMngr->SetProductName(szProductName);
    //pLicMngr->SetLicenseFile(szFileLic);

    if ((argc > 1) && ((*argv[1] == '-') || (*argv[1] == '/')))
    {
        if (lstrcmpi(TEXT("install"), argv[1] + 1) == 0)
        {
            /*Install the service when the command is
            "-install\"or "/install".*/
            InstallService(
                service.GetName(),          // Name of service
                SERVICE_DISPLAY_NAME,       // Name to display
                SERVICE_START_TYPE,         // Service start type
                SERVICE_DEPENDENCIES,       // Dependencies
                SERVICE_ACCOUNT,            // Service running account
                SERVICE_PASSWORD            // Password of the account
            );
        }
        else if (lstrcmpi(TEXT("remove"), argv[1] + 1) == 0)
        {
            /*Uninstall the service when the command is
            "-remove\"or "/remove".*/
            UninstallService(service.GetName());
        }
        else if (lstrcmpi(TEXT("debug"), argv[1] + 1) == 0)
        {

            CServiceBase::RunDebug(service);
        }
    }
    else
    {
        if (!CServiceBase::Run(service))
        {
            if (ERROR_FAILED_SERVICE_CONTROLLER_CONNECT == GetLastError())
                printf("Service failed to run err %d\n", GetLastError());
			LOG_ERROR << "Failed to run service: " << service.GetName() << " Error: " << GetLastError();
        }
    }
#endif

    return 0;
}

/*
Usage:
- myservice.exe install     -> Install service
- myservice.exe uninstall   -> Uninstall service
- myservice.exe start       -> Start service
- myservice.exe stop        -> Stop service
- myservice.exe console     -> Run in console mode for debugging
- myservice.exe             -> Run as service (called by SCM)
*/