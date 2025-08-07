#pragma once
#include "pch.h"
#include "ObjectManager/ObjectManager.h"
#include "Object/Object.h"
#include "Model/CModel/CModel.h"

namespace root::v1 //  /root/v1/resource
{
    class resource : public CONTROLLER<resource>
    {
    public:
        ~resource() override {}
    public:
        METHOD_LIST_BEGIN
			METHOD_ADD(resource::get, "", Get);                 // "" is the subresource
            METHOD_ADD(resource::post, "", Post);
            METHOD_ADD(resource::put, "", Put);
            METHOD_ADD(resource::del, "", Delete);
        METHOD_LIST_END

    protected:
        void get(const REQ& req, FUNC&& callback);
        void post(const REQ& req, FUNC&& callback);
        void put(const REQ& req, FUNC&& callback);
        void del(const REQ& req, FUNC&& callback);
    public:
		using ObjectManager = Manager<Object>;   // cache List of objects
		CModel model;                            // Model for actions with db 
    };
}
