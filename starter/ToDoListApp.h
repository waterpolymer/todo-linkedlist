#ifndef TODOLISTAPP_H
#define TODOLISTAPP_H

#include <iostream>
#include <fstream>
#include "SortedTaskList.h"

//#include "ToDoListDriver.h"

// ToDoList Application Class - This class will handle the commands entered from the
// user. It is initialized with an input/output stream, which is by default cout/cin. 

// Any functions implemented should make use of out/in instead of cout/cin directly.
class ToDoListApp {
public:
	void run();
	ToDoListApp(std::istream& in = std::cin, 
				std::ostream& out = std::cout) : 
				in(in), out(out) {}
protected:
	
	enum TaskType { SHOPPING = 'S', EVENT = 'E', HOMEWORK = 'H', GENERIC = 'G' };

	// You will implement all of the following functions
	void executeCommandPrint(bool completed = false, bool detailed = false);

	void executeCommandAddTask();
	void executeCommandRemoveTask();
	void executeCommandCompleteTask();
	
	void executeCommandSave();
	void executeCommandLoad();
	
	/*
	friend std::ostream& operator<<(std::ostream &output, Date &outDate) {
		out << outDate.getMonth() << '/' << outDate.getDay() << '/' << outDate.getYear() << std::endl;
	}
	*/
	
private:
	// Remember: you may add additional member variables
	std::istream& in = std::cin;
	std::ostream& out = std::cout;
	SortedTaskList incompleteTasks;
	SortedTaskList completedTasks;
};


/*
make a character to specify start of accepting completed tasks --- Saving complete tasks is not required?

for loading in a file, check for end of character lines?
*/

#endif 
