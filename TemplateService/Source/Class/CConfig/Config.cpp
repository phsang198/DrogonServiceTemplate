#pragma once 
#include "pch.h"
#include "Config.h"

std::string Config::_config;
rapidjson::Document document;

bool Config::parse()
{
	if (document.Parse(_config.c_str()).HasParseError())
	{
		//LOG_ERROR("Can't parse Config file");
		return FALSE;
	}
	assert(document.IsObject());
	return TRUE;
}

Config::Config()
{
	auto t = getConfig();
}

Config::~Config()
{
}

std::string Config::getConfig()
{
	return _config;
}

bool Config::setConfig(const std::string& uConfig)
{
	std::string save = _config;
	_config = uConfig;

	if (!parse())
	{
		_config = save;
		return FALSE;
	}
	return TRUE;
}


bool Config::loadDBConfig(std::string& dbName, std::string& dbHost, int& dbPort, std::string& dbUser, std::string& dbPassword)
{
	const rapidjson::Value& components = document["components"];

	for (const auto& component : components.GetArray())
	{
		if (std::string(component["name"].GetString()) == "PostgreSQL")
		{
			auto para = component["parameters"].GetObj();
			dbName = para["database_name"].GetString();
			dbHost = para["host"].GetString();
			dbPort = para["port"].GetInt();
			dbUser = para["user"].GetString();
			dbPassword = para["password"].GetString();
			return TRUE;
		}
	}
	return FALSE;
}

bool Config::loadTokenConfig(std::string& host)
{
	const rapidjson::Value& components = document["components"];

	for (const auto& component : components.GetArray())
	{
		if (std::string(component["name"].GetString()) == "Token")
		{
			std::string _host = component["parameters"]["host"].GetString();
			std::string port = std::to_string(component["parameters"]["port"].GetInt());
			host = "http://" + _host + ":" + port;
			return TRUE;
		}
	}
	return FALSE;
}

bool Config::loadSMeshConfig(std::string& host, std::string& config)
{
	rapidjson::Value& components = document["components"];
	auto& allocator = document.GetAllocator();
	for (auto& component : components.GetArray())
	{
		if (std::string(component["name"].GetString()) == "Mesh")
		{
			std::string _host = component["parameters"]["host"].GetString();
			std::string port = std::to_string(component["parameters"]["port"].GetInt());
			host = "http://" + _host + ":" + port;

			rapidjson::Document copy_doc2;
			auto& allocator1 = copy_doc2.GetAllocator();

			copy_doc2.CopyFrom(document, allocator1);

			copy_doc2["service"].RemoveMember("name");
			copy_doc2["service"].RemoveMember("port");
			copy_doc2["service"].RemoveMember("app_token");
			copy_doc2["service"].RemoveMember("description");
			copy_doc2["service"].RemoveMember("service_guid");
			copy_doc2["service"].RemoveMember("service_type");

			rapidjson::Document copy_doc;
			auto& allocator2 = copy_doc.GetAllocator();

			copy_doc.CopyFrom(document["service"], allocator2);
			copy_doc.RemoveMember("crow");
			copy_doc.RemoveMember("features");

			copy_doc.AddMember("config", copy_doc2, allocator1);
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			copy_doc.Accept(writer);
			config = buffer.GetString();

			return TRUE;
		}
	}
	return FALSE;
}

bool Config::loadErrorConfig()
{
	const rapidjson::Value& components = document["components"];

	for (const auto& component : components.GetArray())
	{
		if (std::string(component["type"].GetString()) == "Error code")
		{
			const rapidjson::Value& error = component["parameters"]["error"];

			for (const auto& object : error.GetArray())
			{
				int code = object["code"].GetInt();
				std::string name = object["name"].GetString();

				RCode[code] = name;
			}
			return TRUE;
		}
	}
	return FALSE;
}