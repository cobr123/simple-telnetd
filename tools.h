#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

std::string last_error_description();

std::string croprn(std::string s);

std::string extract_cmd(std::string s);

void handler_sigalrm(int sig);

FILE* rpopen_tlim(const char *cmd, int lim);

int rpclose(FILE *f);



#endif

