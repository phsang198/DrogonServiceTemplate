#pragma once

class Config
{
public:
	Config();
	~Config();

public:
	static std::string getConfig();
	static bool setConfig(const std::string& uConfig);
public:
	static bool loadDBConfig(std::string& dbName, std::string& dbHost, int& dbPort, std::string& dbUser, std::string& dbPassword);

	static bool loadTokenConfig(std::string& host);
	static bool loadSMeshConfig(std::string& host, std::string& config);

	static bool loadErrorConfig();
private:
	static bool parse();
private:
	static std::string _config;

};


