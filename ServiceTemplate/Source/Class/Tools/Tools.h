#pragma once
#include <windows.h>
#include <string>

class Tools
{
public:
    static std::string LPCWSTRToString(LPCWSTR pwsz)
    {
        if (!pwsz) return "";
        int len = WideCharToMultiByte(CP_UTF8, 0, pwsz, -1, nullptr, 0, nullptr, nullptr);
        if (len == 0) return "";
        std::string result(len - 1, 0); // -1 bỏ null terminator
        WideCharToMultiByte(CP_UTF8, 0, pwsz, -1, &result[0], len, nullptr, nullptr);
        return result;
    }
};
