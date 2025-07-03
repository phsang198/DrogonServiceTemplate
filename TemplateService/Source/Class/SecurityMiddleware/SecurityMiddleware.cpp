#include "SecurityMiddleware.h"

void SecurityMiddleware::invoke(const REQ& req,
    MiddlewareNextCallback&& nextCb,
    MiddlewareCallback&& mcb) 
{
    const std::string& origin = req->getHeader("origin");
    if (origin.find("www.some-evil-place.com") != std::string::npos)
    {
        // intercept directly
        mcb(HttpResponse::newNotFoundResponse(req));
        return;
    }
    // Do something before calling the next middleware
    nextCb([mcb = std::move(mcb)](const HttpResponsePtr& resp) {
        // Do something after the next middleware returns
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Credentials", "true");
        mcb(resp);
        });
}
