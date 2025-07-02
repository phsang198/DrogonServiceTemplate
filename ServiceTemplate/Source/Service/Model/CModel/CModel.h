#pragma once
#include <string>
// token manager
class Object; 


class CModel
{
public: 
	CModel(); 
	~CModel(); 
public:
	std::string msg;
public: 
	bool Connect(std::string dbName, std::string dbHost, int dbPort, std::string dbUser, std::string dbPassword);  
	bool initSchema(std::string content);
	//----------------------------------------------------------------------------------------------------------------------
	void Destroy();
	
public: 
	//int m_CacheSize; //Cache Size
};

