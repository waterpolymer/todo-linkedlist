#ifndef TASK_H
#define TASK_H

#include "Date.h"
#include <vector>
#include <string>

class Task {
private:
	std::string description;
	Date deadline;

public:
	Task(std::string inDescription, Date inDeadline) : description(inDescription), deadline(inDeadline) {};
	virtual ~Task();
	virtual std::string getDescription() { return description; };
	virtual Date getDeadline() const { return deadline; };
	virtual char getAbbreviation() { return 'G'; };
	virtual std::string getDetailedDescription() { return ""; };
};

class ShoppingTask:public Task{
private:

	std::vector<std::string> items;

public:
	ShoppingTask(std::string inDescription, Date inDeadline, std::vector<std::string> inItems) : 
					Task(inDescription, inDeadline), items(inItems) {};
	virtual ~ShoppingTask();
	
	virtual char getAbbreviation() { return 'S'; };
	virtual std::string getDetailedDescription(){
		std::string tmp;
		for (unsigned int i = 0; i < items.size(); ++i ){
			if(i == items.size() - 1){
				tmp = tmp + items[i];
			}else{
				tmp = tmp + items[i] + "|";
			}
		}
		return tmp;
	}
};

class EventTask:public Task{
private:
	std::string location;
	std::string time;

public:
	EventTask(std::string inDescription, Date inDeadline, std::string inLocation, std::string inTime) : 	
					Task(inDescription, inDeadline), location(inLocation), time(inTime) {};
	virtual ~EventTask();
	
	char getAbbreviation(){return 'E';};
	virtual std::string getDetailedDescription(){
		std::string tmp;
		tmp = location + "|" + time;
		return tmp;
	}
};

class HomeworkTask:public Task{
private:
	std::string classSubject;	//add set ClassSub;

public:
	HomeworkTask(std::string inDescription, Date inDeadline, std::string inClassSubject) : 
					Task(inDescription, inDeadline), classSubject(inClassSubject) {};
	virtual ~HomeworkTask();

	virtual char getAbbreviation() { return 'H'; };
	virtual std::string getDetailedDescription(){return classSubject;};
};

#endif
