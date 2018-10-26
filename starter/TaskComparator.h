#ifndef TASKCOMPARATOR_H
#define TASKCOMPARATOR_H

#include "Task.h"

class TaskComparator {
public:
	bool operator()(const Task* task1, const Task* task2) const{//do I need a const version?
		if (task1->getDeadline() < task2->getDeadline()) {
			return true;
		}
		return false;
	}
};




#endif