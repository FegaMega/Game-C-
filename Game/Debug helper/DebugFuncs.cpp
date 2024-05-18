#include "DebugFuncs.h"

const char* getStringAddress(std::string str) {
	char buff[20];
	sprintf_s(buff, "%x", (int)&str[0]);
	return buff;
}

const char* getStringAddress(const char* str){
	char buff[20];
	sprintf_s(buff, "%x", (int)&str[0]);
	return buff;
}