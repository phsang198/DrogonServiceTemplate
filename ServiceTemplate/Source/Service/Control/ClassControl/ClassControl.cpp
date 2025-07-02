#include "pch.h"
#include "ClassControl.h"

using namespace root::v1;

void resource::get(const REQ& req, FUNC&& callback)
{
    auto resp = RESPNew();
    resp->setBody(
        "Hello, this is a generic hello message from the SayHello "
        "controller");
    callback(resp);
}

void resource::post(const REQ& req, FUNC&& callback)
{
    auto resp = RESPNew();
    resp->setBody(
        "Hi there, this is another hello from the SayHello Controller");
    callback(resp);
}
void resource::put(const REQ& req, FUNC&& callback)
{
    auto resp = RESPNew();
    resp->setBody(
        "Hello, this is a generic hello message from the SayHello "
        "controller");
    callback(resp);
}

void resource::del(const REQ& req, FUNC&& callback)
{
    auto resp = RESPNew();
    resp->setBody(
        "Hi there, this is another hello from the SayHello Controller");
    callback(resp);
}