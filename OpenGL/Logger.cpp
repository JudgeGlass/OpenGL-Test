#include "Logger.h"

#include <iostream>
#include <string>
#include <fstream>

void Logger::LogInfo(std::string message) {
	InfoStream += "[Info]: " + message + "\n";
	MainLog += "[Info]: " + message + "\n";
}

void Logger::LogWarning(std::string message) {
	WarningStream += "[WARN]: " + message + "\n";
	MainLog += "[WARN]: " + message + "\n";
}

void Logger::LogError(std::string message) {
	ErrorStream += "[ERROR]: " + message + "\n";
	MainLog += "[ERROR]: " + message + "\n";
}

void Logger::ClearMainLog() {
	MainLog = "";
}

void Logger::WriteLog() {
	logFile.open("Latest.log");
	logFile << MainLog;
	logFile.close();
}

bool Logger::fexists(const std::string& filename) {
	std::ifstream ifile(filename.c_str());
	return (bool)ifile;
}

std::string Logger::getInfoStream() {
	return InfoStream;
}

std::string Logger::getWarningStream() {
	return WarningStream;
}

std::string Logger::getErrorStream() {
	return Logger::ErrorStream;
}

std::string Logger::getMainLog() {
	return MainLog;
}