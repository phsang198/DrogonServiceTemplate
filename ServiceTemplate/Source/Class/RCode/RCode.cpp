#pragma once
#include "pch.h"

std::map<int, std::string> response::error;

//void response::add_header(crow::response& res)
//{
//	res.set_header("Access-Control-Allow-Headers", "Content-Type");
//	res.set_header("Access-Control-Allow-Headers", "token");
//	res.set_header("Access-Control-Request-Headers", "token");
//	res.set_header("Access-Control-Allow-Methods", "OPTIONS, GET, POST, PUT, PATCH, DELETE");
//	res.set_header("Accept-Encoding", "gzip");
//	res.set_header("Access-Control-Allow-Origin", "*");
//}
//crow::response response::add_response(int code , const nlohmann::json& data, const nlohmann::json& key)
//{
//	if (code == INT_MIN)
//	{
//		crow::response res; 
//		add_header(res); 
//		return res; 
//	}
//	nlohmann::json tmp;
//
//	if (!key.empty())
//	{
//		tmp = std::move(key);
//	}
//	tmp["code"] = code;
//	tmp["message"] = RCode[code];
//	if (!data.empty())
//	{
//		tmp["data"] = std::move(data);
//	}
//	try
//	{
//		std::ostringstream oss;
//		oss << tmp;
//		crow::response res(oss.str());
//		add_header(res);
//		res.set_header("content-type", "application/json");
//		return res; 
//	}
//	catch (std::exception& e)
//	{
//		nlohmann::json tmp2; 
//		tmp2["code"] = 201;
//		tmp2["message"] = RCode[201];
//		tmp2["detail"] = "invalid UTF-8 data";
//
//		std::ostringstream oss;
//		oss << tmp2;
//		crow::response res(oss.str());
//		add_header(res);
//		res.set_header("content-type", "application/json");
//		return res;
//	}
//
//	return response::add_response(201); 
//}
//
//crow::response response::add_response_binary(int code, const nlohmann::json& data, const nlohmann::json& key)
//{
//	if (code == INT_MIN)
//	{
//		crow::response res;
//		add_header(res);
//		return res;
//	}
//	nlohmann::json tmp;
//
//	if (!key.empty())
//	{
//		tmp = std::move(key);
//	}
//	tmp["code"] = code;
//	tmp["message"] = RCode[code];
//	if (!data.empty())
//	{
//		tmp["data"] = std::move(data);
//	}
//
//	//std::string jsonString = tmp.dump();
//	std::ostringstream oss;
//	oss << tmp; 
//
//	std::istringstream iss(oss.str()); 
//
//	std::ostringstream binaryStream;
//	Poco::Base64Encoder  encoder(binaryStream);
//	Poco::StreamCopier::copyStream(iss, encoder);
//
//	std::string binaryString = binaryStream.str();
//	/*Poco::JSON::Parser parser;
//	Poco::Dynamic::Var result = parser.parse(jsonString);
//	Poco::JSON::Object::Ptr jsonObject = result.extract<Poco::JSON::Object::Ptr>();
//
//	Poco::JSON::Stringifier stringifier;
//	std::ostringstream oss;
//	stringifier.condense(*jsonObject, oss);
//	std::string binaryString = oss.str();*/
//
//
//	crow::response response = crow::response(binaryString);
//	response.set_header("Content-Type", "application/octet-stream");
//	response::add_header(response);
//
//	return response;
//}
