
#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string>

Socket::Socket() :
	remotePort_(0), remoteAddress_(0),
	localPort_(0), localAddress_(0)
{
	pfd_ = new s_fd(socket(AF_INET, SOCK_STREAM, 0));
}

Socket::Socket(int newfd, unsigned long newAddress, int newPort) :
	remotePort_(newPort), remoteAddress_(newAddress),
	localPort_(0), localAddress_(0)
{
	pfd_ = new s_fd(newfd);
}

Socket::Socket(const Socket &s) :
	remotePort_(s.remotePort_), remoteAddress_(s.remoteAddress_),
	localPort_(s.localPort_), localAddress_(s.localAddress_)
{
	s.pfd_->n++;
	pfd_ = s.pfd_;
}

Socket::~Socket()
{
	if (--pfd_->n == 0) {
		close();
		delete pfd_;
	}
}

void Socket::close()
{
	::close(pfd_->fd);
	pfd_->fd = -1;
}

bool Socket::bind(int p, int addr) 
{
	localPort_ = p;
	localAddress_ = addr;
	struct sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(localPort_);
	local_addr.sin_addr.s_addr = htonl(localAddress_);
	if (::bind(pfd_->fd, (struct sockaddr *)(&local_addr), sizeof(local_addr)) < 0)
	{
		return false;
	}
	return true;
}

bool Socket::setNonBlocking(bool nonblock)
{
	long flags;
	
	// get flags
	if (!fcntl(pfd_->fd, F_GETFL, &flags))
		return false;
	
	if (nonblock)
		return fcntl(pfd_->fd, F_SETFL, flags | O_NONBLOCK);
	else
		return fcntl(pfd_->fd, F_SETFL, flags & ~O_NONBLOCK);
}

std::string Socket::getPeerName()
{
	struct sockaddr addr;
	socklen_t len = sizeof(addr);
	getpeername(pfd_->fd, &addr, &len);  
	return std::string(addr.sa_data);
}


bool Socket::listen(int backlog)
{
	return ::listen(pfd_->fd, backlog) == 0;
}

Socket Socket::accept()
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int newfd = ::accept(pfd_->fd, (sockaddr *)&addr, &addrlen);
	if (newfd == -1)
		return Socket(-1, 0, 0);
	unsigned long newRemoteAddress = ntohl(addr.sin_addr.s_addr);
	int newRemotePort = ntohs(addr.sin_port);
	return Socket(newfd, newRemoteAddress, newRemotePort);
}

bool Socket::isConnected()
{
	return pfd_->fd != -1;
}


std::string Socket::readLine()
{
	static std::string buf (512, ' ');
	std::string::size_type pos = 0; // pos in buffer
	int nb; // number of bytes read by ::read
	char r; // temp var for storing output of read into
	std::string::size_type length = buf.length ();
	
	do
    {
		nb = ::read(pfd_->fd, &r, 1);
		
		if (nb == 0)
			return std::string("");

		switch (nb) {
			case 0:
				return std::string("");
				break;
			case -1:
				/*
				if (errno != EINTR && errno != EAGAIN)
				{
					return std::string("");
				}
				sleep(1);
				break;
				 */
				return std::string("");
				
			default:
				if (pos == length)
				{
					buf.resize (length + 512 );
					length = buf.length();
				}
				buf[pos++] = r;
				break;
		}
		
    } while (r != '\n');
	
	return buf.substr(0, pos);
}

bool Socket::write(std::string s, bool m)
{
	if (m) {
		s += "\r\n";
	}
	int r = ::write(pfd_->fd, s.c_str(), s.length());
	
	return r == s.length(); 
}

