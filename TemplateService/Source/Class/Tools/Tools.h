#pragma once
#include <windows.h>
#include <string>
#include <fstream>

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
    static std::wstring s2ws(const std::string& str)
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }
    static LPCWSTR S2LPCWSTR(const std::string& str)
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo.c_str();
    }

    static std::string getExePath()
    {
        char curPath[FILENAME_MAX];
        GetModuleFileNameA(NULL, curPath, sizeof(curPath));
        std::string szCurDir(curPath);

        size_t found = szCurDir.find_last_of("\\/"); 
        if (found != std::string::npos)
        {
            szCurDir = szCurDir.substr(0, found); 
        }
        else
        {
            szCurDir.clear(); 
        }
        return szCurDir;
    }

    static std::string readFile(std::string filepath)
    {
        std::ifstream fi(filepath, std::ios::binary);
        if (!fi) return "";

        // Di chuyển con trỏ đến cuối file để lấy kích thước
        fi.seekg(0, std::ios::end);
        size_t size = fi.tellg();
        fi.seekg(0, std::ios::beg);

        // Đọc toàn bộ file vào string
        std::string buffer(size, '\0');
        fi.read(&buffer[0], size);

        return buffer;
    }
};
