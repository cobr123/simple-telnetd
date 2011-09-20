#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <set>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>

class Settings {
public:
	Settings()	{}
	
	~Settings() {}
	int getFromFile(char * f);
	bool inCmdList(std::string s);
private:
	Settings(const Settings&);
	const Settings& operator=(const Settings&);
	
        std::set<std::string> cmdlist_;
};

#endif
