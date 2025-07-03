#pragma once
#include "pch.h"

class SecurityMiddleware : public MIDDLEWARE<SecurityMiddleware>
{
public:
    SecurityMiddleware() {};  // do not omit constructor

    void invoke(const REQ& req,
        MiddlewareNextCallback&& nextCb,
        MiddlewareCallback&& mcb) override;
};

class AuthFilter : public FILTER<AuthFilter>
{
private:
    drogon::HttpResponsePtr toResponseError(const std::string& messageError) {
        auto resp = drogon::HttpResponse::newHttpResponse(drogon::k401Unauthorized, drogon::CT_APPLICATION_JSON);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->setBody("");
        return resp;
    }
public:
    void doFilter(const drogon::HttpRequestPtr& req,
        drogon::FilterCallback&& fcb,
        drogon::FilterChainCallback&& fccb) override
    {
        try
        {
            fccb();
        }
        catch (const std::exception& e)
        {
            return fcb(toResponseError(e.what()));
        }
    }

};