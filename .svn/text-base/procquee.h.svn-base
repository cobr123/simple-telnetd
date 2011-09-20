#ifndef __PROCQUEUE_H__
#define __PROCQUEUE_H__

#include <signal.h>
#include <vector>

class ProcQueue {
public:
	ProcQueue () {}
	void insert(int pid);
	bool remove(int pid);
	void broadcastSignal(int sig);
	size_t size();
	void clear();
private:
	std::vector<int> queue_;
	ProcQueue(const ProcQueue&);
};

#endif
