#include "settings.h"

int Settings::getFromFile(char * f) 
{
	FILE *o;
	o = fopen(f, "r");
	if (o == 0)
	{
		return -1;
	}
	char line[1024];
	cmdlist_.clear();
	while ( fgets(line, sizeof(line), o) != 0) 
	{
		if (strlen(line) > 1) {
                        cmdlist_.insert(std::string(line, strlen(line)-1) );
		}
		
	}
	return cmdlist_.size();
}

bool Settings::inCmdList(std::string s)
{
        if (cmdlist_.end() == cmdlist_.find(s))
        {
                return false;
        }
        else
        {
                return true;
        }
}

