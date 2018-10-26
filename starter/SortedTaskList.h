#ifndef SORTED_TASK_LIST_H
#define SORTED_TASK_LIST_H

#include <iostream>
#include <stdexcept>
#include "SortedLinkedList.h"
#include "TaskComparator.h"

class SortedTaskList{
private:
	SortedLinkedList<Task*, TaskComparator> tasks;


public:
	SortedTaskList() {};
	~SortedTaskList() {};

	Task* getData(const int& pos) { return tasks.at(pos); };		//can be improved, does not have to loop n! times, will come back to this later
    bool add(Task* inTask){return tasks.insert(inTask);};           //stores tasks
    bool remove(const int& pos){return tasks.removePos(pos);};
	bool isEmpty() { return tasks.isEmpty(); };
	int size() { return tasks.size(); };

};

#endif //SORTED_TASK_LIST_H