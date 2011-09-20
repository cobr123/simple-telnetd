
#ifndef SOCKET_H
#define SOCKET_H
#include <string>

class Socket {
	struct s_fd {
		int fd; 
		int n; // ref counter
		s_fd() : fd(0), n(1) {}
		explicit s_fd(int s) : fd(s), n(1) {}
	};
	s_fd *pfd_;
	int remotePort_;
	unsigned long remoteAddress_;
	
	int localPort_;
	unsigned long localAddress_;
	
public:
	Socket();
	
	//file, address, port
	explicit Socket(int, unsigned long, int);
	~Socket();
	Socket(const Socket &);
	
	void close();
	bool setLocalPort(int);
	bool setNonBlocking(bool = true);
	bool listen(int = 5);
	bool bind(int p, int addr);
	Socket accept();
	bool isConnected();
	std::string getPeerName();
	
	bool write(std::string, bool = false);
	std::string readLine();


/*	
	int getRemotePort() const;
	int getLocalPort() const;
	int getFileDescriptor() const;
	
	bool isConnected();
	
	bool setRemoteHostname(String);
	bool setRemoteIP(unsigned long);
	bool setRemotePort(int);
	
	bool setLocalHostname(String);
	bool setLocalIP(unsigned long);
	bool setLocalPort(int);
	
	
	bool connect();
	Socket accept();
	
	bool write(String, bool = false);
	String readLine();
	String readChar();
	bool hasData();
 */
private:
	const Socket & operator=(const Socket&);
};

std::string last_error_description();
std::string croprn(std::string s);
std::string extract_cmd(std::string s);

FILE* rpopen_tlim(const char *cmd, int lim);
int rpclose(FILE *f);




#endif