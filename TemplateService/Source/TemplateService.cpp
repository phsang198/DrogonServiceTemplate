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
    
    auto conf = getConfig();

    if (1) // test with all configs 
    {
        RootService::RunDrogon();
    }
}
