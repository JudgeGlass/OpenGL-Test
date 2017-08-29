#ifndef Logger_H
#define Logger_H

#include <iostream>
#include <string>
#include <fstream>

class Logger {
public:
	void LogInfo(std::string message);
	void LogWarning(std::string message);
	void LogError(std::string message);
	void ClearMainLog();
	void WriteLog();
	std::string getInfoStream();
	std::string getWarningStream();
	std::string getErrorStream();
	std::string getMainLog();
	bool fexists(const std::string& filename);
private:
	std::string MainLog;
	std::string InfoStream;
	std::string WarningStream;
	std::string ErrorStream;

	std::ofstream logFile;

};

#endif