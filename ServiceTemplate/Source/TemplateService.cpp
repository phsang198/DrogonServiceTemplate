#include "pch.h"
#include "TemplateService.h"
#include <Class/Tools/Tools.h>
#include <fmt/base.h>
#include <fmt/format.h>

TemplateService::~TemplateService()
{
}

void TemplateService::RunDrogon()
{
    auto servicename = Tools::LPCWSTRToString(GetName());
    auto conf = getConfig(); 

    LOG_INFO << fmt::format("{} is starting at http://0.0.0.0:8765\n", servicename);

    RootService::RunDrogon();  
}
