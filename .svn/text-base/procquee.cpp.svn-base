#include "procquee.h"
#include <vector>
#include <algorithm>
#include <signal.h>

void ProcQueue::insert(int pid)
{
	queue_.push_back(pid);
}

bool ProcQueue::remove(int pid)
{
	std::vector<int>::iterator it = std::find(queue_.begin(), queue_.end(), pid);
	if (it != queue_.end())
	{
		queue_.erase(it);
		return true;
	}
	return false;
}

void ProcQueue::broadcastSignal(int sig)
{
	std::vector<int>::iterator it;
	for (it = queue_.begin(); it != queue_.end(); it++)
	{
		kill(*it, sig);
	}
}

size_t ProcQueue::size()
{
	return queue_.size();
}

void ProcQueue::clear()
{
	queue_.clear();
}
