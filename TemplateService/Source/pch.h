#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
#define CONTROLLER HttpController
#define REQ HttpRequestPtr
#define RESPNew HttpResponse::newHttpResponse
#define FUNC std::function<void(const HttpResponsePtr&)>


//// uuid 
//#include "User/User.h"
////ORTHER
//#include <fstream>
//#include <stdlib.h>
//
//#include <time.h>
////STREAM
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <algorithm>
//#include <queue>
//#include <tchar.h>
//#include <ctype.h>
////GDAL
////#include "ogr_geometry.h"
////#include "ogrsf_frmts.h"
//
//#include "Define/IDNStruct.h"
//#include "Define/ApiDefine.h"
//// Poco.
//#include "Poco/JWT/Token.h"
//#include "Poco/JWT/Signer.h"
//#include "Poco/JWT/Serializer.h"
//#include "Poco/JWT/JWTException.h"
//#include "Poco/DateTime.h"
//#include "Poco/DateTimeFormatter.h"
//#include "Poco/DateTimeFormat.h"
//#include "Poco/LogFile.h"
//#include "Poco/Path.h"
//#include "Poco/File.h"
//#include "Poco/Delegate.h"
//
//#include "Poco/File.h"
//#include "Poco/FileStream.h"
//
//#include "Poco/DateTimeParser.h"
//#include "Poco/Clock.h"
//
//#include <Poco/Timespan.h>
//#include <Poco/LocalDateTime.h>
//#include <Poco/Base64Decoder.h>
//#include <Poco/Base64Encoder.h>
//RAPIDJSON
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
// Response Code 
#include "RCode/RCode.h"
////MUTEX LOCK
//#include <mutex>
////TOOLS
//#include "Tools/StringProcess.h"
//#include "Tools/SupportFunc.h"
//// NLOHMANN json
//#include <nlohmann/json.hpp>
//// date
//#include "date/date.h"

//// CASBIN
//
//// RBAC 
//
////CPR
//cpr 
#include <cpr/cpr.h>
#include <cpr/multipart.h>
//
//using json = nlohmann::json;
//using namespace rapidjson;
//
//#define RESP response::add_response
#define RCode response::error
//
//#define MOVE std::move
//// Định nghĩa macro
//#define LOG_INFO(msg) Poco::Logger::root().information(msg)
//#define LOG_ERROR(msg) Poco::Logger::root().error(msg)
//#define LOG_WARNING(msg) Poco::Logger::root().warning(msg)
//#define LOG_DEBUG(msg) Poco::Logger::root().debug(msg)
//enum : int
//{
//    CONTINUE = 100,                                  // options method
//    SWITCHING_PROTOCOLS = 101,                       // doi protocol
//    PROCESSING = 102,                                // dang xu li
//    OK = 200,                                        
//    CREATED = 201,                                                  
//    ACCEPTED = 202,
//    NON_AUTHORITATIVE_INFORMATION = 203,             
//    NO_CONTENT = 204,                                // ko co noi dung
//    RESET_CONTENT = 205,                                    
//    PARTIAL_CONTENT = 206,
//    MULTI_STATUS = 207,
//    ALREADY_REPORTED = 208,
//    IM_USED = 226,
//    MULTIPLE_CHOICES = 300,
//    MOVED_PERMANENTLY = 301,
//    FOUND = 302,
//    SEE_OTHER = 303,
//    NOT_MODIFIED = 304,
//    USE_PROXY = 305,
//    RESERVED = 306,
//    TEMPORARY_REDIRECT = 307,
//    PERMANENT_REDIRECT = 308,
//    BAD_REQUEST = 400,
//    UNAUTHORIZED = 401,
//    PAYMENT_REQUIRED = 402,
//    FORBIDDEN = 403,
//    NOT_FOUND = 404,
//    METHOD_NOT_ALLOWED = 405,
//    NOT_ACCEPTABLE = 406,
//    PROXY_AUTHENTICATION_REQUIRED = 407,
//    REQUEST_TIMEOUT = 408,
//    CONFLICT = 409,
//    GONE = 410,
//    LENGTH_REQUIRED = 411,
//    PRECONDITION_FAILED = 412,
//    REQUEST_ENTITY_TOO_LARGE = 413,
//    REQUEST_URI_TOO_LONG = 414,
//    UNSUPPORTED_MEDIA_TYPE = 415,
//    REQUESTED_RANGE_NOT_SATISFIABLE = 416,
//    EXPECTATION_FAILED = 417,
//    UNPROCESSABLE_ENTITY = 422,
//    LOCKED = 423,
//    FAILED_DEPENDENCY = 424,
//    UPGRADE_REQUIRED = 426,
//    PRECONDITION_REQUIRED = 428,
//    TOO_MANY_REQUESTS = 429,
//    REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
//    INTERNAL_SERVER_ERROR = 500,
//    NOT_IMPLEMENTED = 501,
//    BAD_GATEWAY = 502,
//    SERVICE_UNAVAILABLE = 503,
//    GATEWAY_TIMEOUT = 504,
//    HTTP_VERSION_NOT_SUPPORTED = 505,
//    VARIANT_ALSO_NEGOTIATES = 506,
//    INSUFFICIENT_STORAGE = 507,
//    LOOP_DETECTED = 508,
//    NOT_EXTENDED = 510,
//    NETWORK_AUTHENTICATION_REQUIRED = 511
//};
