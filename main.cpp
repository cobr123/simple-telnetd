/*
	Реализовано все, кроме локальных сокетов.
	Timeout - первый параметр
 
 */

#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <string>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdarg.h>
#include "socket.h"
#include "settings.h"
#include "procquee.h"

#define MYPORT 3337
#define CONFIG_FILE "/etc/simple-telnetd.conf"


static bool reconf = false;
static ProcQueue proc_queue;
static int tlim = 0;

void base_handler_sigchld(int sig)
{
	if (sig == SIGCHLD)
	{
		fprintf(stderr, "SIGCHLD signal catched in base, pid %d\n", getpid());
		int stat;
		int pid = waitpid(-1, &stat, 0);
		if (pid < 0)
		{
			perror("waitpid");
			return;
		}
		fprintf(stderr, "Child process %d is terminate\n", pid);
		proc_queue.remove(pid);
	}
}

void handler_sighup(int sig)
{
        fprintf(stderr, "SIGHUP signal catched\n");
        reconf = true;
}

void base_handler_sighup(int sig)
{
        fprintf(stderr, "SIGHUP signal catched in base\n");
	proc_queue.broadcastSignal(SIGHUP);
}

void about()
{
	printf("%s", "Simple telnet daemon.\n Using: simple-telnetd [--start|--stop] [--timeout n]\n");
}

int main (int argc, char * const argv[]) 
{

	if (argc > 1 ) {
		tlim = strtol(argv[1],0,10);
		fprintf(stderr, "Timeout %d\n", tlim);
 	}
	
	Socket msocket;
	Settings set;
	if (set.getFromFile(CONFIG_FILE) < 0) {
		perror("getFromFile()");
		exit(1); 
	}		

	signal(SIGHUP, base_handler_sighup);
	signal(SIGCHLD, base_handler_sigchld);
	
	fprintf(stderr, "Starting\n");
	if (!msocket.bind(MYPORT, INADDR_ANY))
	{
		perror("bind()");
		exit(1);
	}

	fprintf(stderr, "Binding success\n");
	
	msocket.listen(); 	
	
	pid_t ac_pid = 0;
	while (1)
	{
		Socket session = msocket.accept();
		
		if (!session.isConnected()) 
		{
			perror("Error accept()");
			continue;
		}

		fprintf(stderr, "Connection accepted\n");
		
		ac_pid = fork();
		if (ac_pid == 0) {
			
			signal(SIGCHLD, SIG_DFL);
			signal(SIGHUP, handler_sighup);
			
			while(1)
                        {
				session.write(">");
				
				std::string line = session.readLine();
				if (line == "") {
					perror("error recv()");
					exit(0);
				}
				std::string cmd = extract_cmd(croprn(line));

                                if (reconf) {
                                        if (set.getFromFile(CONFIG_FILE) < 0) {
                                                perror("getFromFile()");
                                        }
                                        else {
                                                fprintf(stderr, "Reconfiguration\n");
                                        }

                                        reconf = false;
                                }
				if (!set.inCmdList(cmd)) {
					session.write("Command '");
					session.write(croprn(line));
					session.write("' is not permitted\n");
				}
				else
				{
					char out[1024];
					FILE *fp = rpopen_tlim(croprn(line).c_str(), tlim);
					memset(out, 0, sizeof(out));
						
					while (fgets(out, sizeof(out), fp) !=0)
					{
						session.write(out);
						memset(out, 0, sizeof(out));
					}
					rpclose(fp);
				}
		
			} //while interact session
				
		} // create child process
		else
		{
			proc_queue.insert(ac_pid);
		}
		
	} //while accept
	
	return 0;
}
