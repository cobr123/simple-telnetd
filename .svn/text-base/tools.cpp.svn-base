#include "tools.h"

std::string croprn(std::string s)
{
	size_t l = s.length();
	
	char n = s[s.length()-1];
	char r = s[s.length()-2];
	
	if (s.length() > 1) {
		if (s[s.length()-1] == '\n' && s[s.length()-2] == '\r') {
			std::string t = s.substr(0, s.length()-2);
			return t;
		}
	}
	return s;
}

std::string extract_cmd(std::string s)
{
	return s.substr(0, s.find(' ', 0));
}


void handler_sigalrm(int sig)
{
	exit(-1);
}


FILE* rpopen_tlim(const char *cmd, int lim)
{
	FILE* fpr;
	int p[2];
	if ( pipe(p) < 0)
	{
		perror("pipe");
	}
	fcntl(p[0], F_SETFD, FD_CLOEXEC); //read
	fcntl(p[1], F_SETFD, FD_CLOEXEC); //write
	
	
	int pid = fork();
	if (pid == 0)
	{
		if (lim > 0)
			alarm(lim);
		//signal(SIGALRM, handler_sigalrm);
		dup2(p[1], 1);
		dup2(p[1], 2);
		close(p[0]);
		execl("/bin/sh", "sh", "-c", cmd, 0);
		perror("execl");
		_exit(1);
	}
	
	fpr = fdopen (p[0], "r");
	close(p[1]);
	return fpr;
}

int rpclose(FILE *f)
{
	fclose(f);
	int status;
	waitpid(-1, &status, 0);

	return 0;
}		




