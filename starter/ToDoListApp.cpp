#include <algorithm>
#include "ToDoListApp.h"

using namespace std; 

namespace {
	string dateToString(const Date& date) {
		string s;
		s = to_string(date.getMonth()) + '/' + to_string(date.getDay()) + '/' + to_string(date.getYear());
		return s;
	}

	Date stringToDate(const string& inString) {
		Date * date = new Date(stoi(inString.substr(0, 2)), stoi(inString.substr(3, 2)), stoi(inString.substr(6, 4)));
		return *date;
	}
}

void ToDoListApp::run() {

	//NOTE: we are using out/in streams from the class level, not cin/cout
	//      directly. All your functions should do this.
	out << "Welcome to your To-Do List! You may begin to enter commands.";
	out << endl;

	string command;
	do {
		out << "> ";
		getline(in, command);
		//Convert entire command to uppercase for easy compares
		transform(command.begin(), command.end(), command.begin(), ::toupper);

		if (command == "PRINT") {
			executeCommandPrint();
		} else if (command == "DETAILED") {
			executeCommandPrint(false, true);
		} else if (command == "COMPLETED") {
			executeCommandPrint(true);
		} else if (command == "ADD") {
			executeCommandAddTask();
		} else if (command == "REMOVE") {
			executeCommandRemoveTask();
		} else if (command == "COMPLETE") {
			executeCommandCompleteTask();
		} else if (command == "SAVE") {
			executeCommandSave();
		} else if (command == "LOAD") {
			executeCommandLoad();
		} else if (command == "EXIT") {
			out << "Thank you for using To-Do List!\n";
			break;
		} else {
			out << "Unknown Command (" << command << "). Try Again.\n";
		}
		out << "\n";
	} while (true);
}

void ToDoListApp::executeCommandPrint(bool completed, bool detailed) {
	if (completed) {
		if (completedTasks.isEmpty()) {
			out << "You have no completed tasks!" << endl;
		}

		for (int i = 1; i <= completedTasks.size(); ++i) {
			out << i << ". " << dateToString(completedTasks.getData(i)->getDeadline()) << " - ";
			char abbreviation = completedTasks.getData(i)->getAbbreviation();
			if (abbreviation == 'S') {
				out << "[Shopping] ";
			}
			if (abbreviation == 'E') {
				out << "[Event] ";
			}
			if (abbreviation == 'H') {
				out << "[Homework] ";
			}
			out << completedTasks.getData(i)->getDescription() << endl;
		}
		return;
	}

	if (incompleteTasks.isEmpty()) {
		out << "You have no outstanding tasks!" << endl;	//optimization
		return;
	}

	if (detailed) {
		//detailed print
		for (int i = 1; i <= incompleteTasks.size(); ++i) {
			out << i << ". " << dateToString(incompleteTasks.getData(i)->getDeadline()) << " - ";
			char abbreviation = incompleteTasks.getData(i)->getAbbreviation();

			if (abbreviation == 'G') {
				out << incompleteTasks.getData(i)->getDescription() << endl;
			}

			if (abbreviation == 'S') {
				string items = incompleteTasks.getData(i)->getDetailedDescription();

				//out << items << "  TESTING TO SEE HOW SAVED ____--____--" << endl;

				out << "[Shopping] " << incompleteTasks.getData(i)->getDescription() << endl;
				out << "Items: " << endl;

				unsigned int j = 0;
				int subStringStart = 0;
				int subStringLength = 0;
				while (j < items.length()) {

					while (items[j] != '|' && j < items.length()) {
						++j;
						++subStringLength;
					}

					out << items.substr(subStringStart, subStringLength) << endl;
					subStringStart = j + 1;
					subStringLength = 0;
					
					++j;
				}

			}

			if (abbreviation == 'E') {	//abbrEviation, ha!
				int j = 0;
				string event = incompleteTasks.getData(i)->getDetailedDescription();	//makes it easier to understand
				while (event[j] != '|') {
					++j;
				}
				out << "[Event] " << incompleteTasks.getData(i)->getDescription() << endl;
				out << "Location: " << endl;
				out << event.substr(0, j) << endl;		//is it +1?
				out << "Time: " << endl;
				out << event.substr(j + 1, event.length() - j + 1);
			}

			if (abbreviation == 'H') {
				out << "[Homework] " << incompleteTasks.getData(i)->getDescription() << endl;
				out << "Subject: " << endl;
				out << incompleteTasks.getData(i)->getDetailedDescription() << endl;
			}
		}
		return;
	}
	else {
		//aka not detailed
		for (int i = 1; i <= incompleteTasks.size(); ++i) {

			out << i << ". " << dateToString(incompleteTasks.getData(i)->getDeadline()) << " - ";
			char abbreviation = incompleteTasks.getData(i)->getAbbreviation();
			if (abbreviation == 'S') {
				out << "[Shopping] ";
			}
			if (abbreviation == 'E') {
				out << "[Event] ";
			}
			if (abbreviation == 'H') {
				out << "[Homework] ";
			}
			out << incompleteTasks.getData(i)->getDescription() << endl;
		}
		return;
	}

}

void ToDoListApp::executeCommandCompleteTask() {
	if (incompleteTasks.isEmpty()) {
		out << "There are no outstanding tasks to complete" << endl;
		return;
	}

	int pos;
	out << "Which task would you like to complete?" << endl;
	in >> pos;
	try {
		Task * completedTask;
		completedTask = incompleteTasks.getData(pos);		//default copy constructor?
		incompleteTasks.remove(pos);
		completedTasks.add(completedTask);
		out << "Task marked complete successfully\n";
		return;
	}
	catch (const out_of_range& e) {
		out << "Out of range error, try again" << endl;
		return;	
	}
}

void ToDoListApp::executeCommandRemoveTask() {
	if (incompleteTasks.isEmpty()) {
		out << "There are no outstanding tasks to complete" << endl;
		return;
	}

	int pos;
	out << "Which task would you like to remove?" << endl;
	in >> pos;

	if (incompleteTasks.remove(pos)) {
		out << "Task removed successfully" << endl;
		return;
	}
	else {
		out << "You have entered an invalid task number!" << endl;
		return;
	}
}

void ToDoListApp::executeCommandAddTask() {
	char inChar;
	string inDate;
	string inDescription;
	out << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
	in >> inChar;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (inChar != 'S' && inChar != 'E' && inChar != 'H' && inChar != 'G') {
		out << "Invalid task Type, try again" << endl;
		return;
	}

	out << "When is the deadline for this task (MM/DD/YYYY format)?" << endl;
	getline(in, inDate);
	Date date = stringToDate(inDate);

	out << "How would you describe this task?" << endl;
	getline(in, inDescription);

	Task * inTask;

	if (inChar == 'G') {
		inTask = new Task(inDescription, date);
	}

	if (inChar == 'S') {

		vector<string> itemList;
		string item;
		out << "What items do you need to buy? [Type your item and press ENTER to add another item. Type DONE to complete the list.]" << endl;
		while (true) {
			getline(in, item);
			if (item == "DONE") {
				break;
			}
			itemList.push_back(item);
		}
		inTask = new ShoppingTask(inDescription, date, itemList);
	}

	if (inChar == 'E') {
		string location;
		string time;
		out << "Where is this event taking place?" << endl;
		getline(in, location);
		out << "When is the event taking place?" << endl;
		getline(in, time);
		inTask = new EventTask(inDescription, date, location, time);
	}

	if (inChar == 'H') {
		string classSubject;
		out << "What subject is this homework task for?" << endl;
		getline(in, classSubject);
		inTask = new HomeworkTask(inDescription, date, classSubject);
	}
	
	incompleteTasks.add(inTask);

	out << "Task successfully added" << endl;
	return;
}

void ToDoListApp::executeCommandSave() {
	if (incompleteTasks.isEmpty()) {
		out << "You have no outstanding tasks!" << endl;
		return;
	}
	string fileName;
	out << "Where would you like to save your outstanding tasks?" << endl;
	getline(in, fileName);

	ofstream outFile;
	outFile.open(fileName, ios::trunc);	//overwrites previous file if open

	if (!outFile.is_open()) {
		out << "An error has occurred while attempting to open the file, try again" << endl;
		return;
	}

	int pos = 1;
	while (pos <= incompleteTasks.size()) {

		if (incompleteTasks.getData(pos)->getAbbreviation() == 'G') {
			outFile << incompleteTasks.getData(pos)->getAbbreviation() << "|"
				<< dateToString(incompleteTasks.getData(pos)->getDeadline()) << "|"
				<< incompleteTasks.getData(pos)->getDescription() << "\n";
			++pos;
		}
		else {
			outFile << incompleteTasks.getData(pos)->getAbbreviation() << "|"
				<< dateToString(incompleteTasks.getData(pos)->getDeadline()) << "|"
				<< incompleteTasks.getData(pos)->getDescription() << "|"
				<< incompleteTasks.getData(pos)->getDetailedDescription() << "\n";
			++pos;
		}
	}

	outFile.close();
	out << "Tasks saved successfully!" << endl;
}

void ToDoListApp::executeCommandLoad() {
	string fileName;

	out << "What file would you like to load oustanding tasks from?" << endl;
	getline(in, fileName);

	ifstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		out << "An error has occurred while attempting to open the file, try again" << endl;
		return;
	}

	string taskText;
	char abbreivation;
	while (getline(inFile, taskText)) {

		abbreivation = taskText[0];

		if (abbreivation == '\0') {
			out << "There is nothing in that file" << endl;
			return;
		}

		//out << taskText << endl; //debug helper

		Date * date = new Date(stoi(taskText.substr(2, 2)), stoi(taskText.substr(5, 2)), stoi(taskText.substr(8, 4)));
		Task * inTask;
		string description;

		int startSubstr = 13;
		unsigned int pos = 13;

		if (abbreivation == 'G') {
			description = taskText.substr(startSubstr, taskText.length() - startSubstr);
			inTask = new Task(description, *date);
		}

		if (abbreivation == 'S') {

			while (taskText[pos] != '|') {
				++pos;
			}
			description = taskText.substr(startSubstr, pos - startSubstr);
			startSubstr = pos + 1;
			++pos;

			vector<string> inItems;
			string item;

			while (pos < taskText.length()) {
				if (taskText[pos] == '|') {
					item = taskText.substr(startSubstr, pos - startSubstr);
					startSubstr = pos + 1;
					inItems.push_back(item);
				}
				++pos;
			}

			item = taskText.substr(startSubstr, pos - startSubstr); //catchs last item
			inItems.push_back(item);

			inTask = new ShoppingTask(description, *date, inItems);
		}

		if (abbreivation == 'E') {

			while (taskText[pos] != '|') {
				++pos;
			}
			description = taskText.substr(startSubstr, pos - (startSubstr + 1));
			startSubstr = pos + 1;

			string location;
			string time;
			while (pos < taskText.length()) {
				if (taskText[pos] == '|') {
					location = taskText.substr(startSubstr, pos - startSubstr);
					startSubstr = pos + 1;
					time = taskText.substr(startSubstr, taskText.length() - startSubstr);
				}
				++pos;
			}
			inTask = new EventTask(description, *date, location, time);
		}

		if (abbreivation == 'H') {

			while (taskText[pos] != '|') {				//maybe make this a function in the annoymous namespace?
				++pos;
			}
			description = taskText.substr(startSubstr, pos - startSubstr);
			startSubstr = pos + 1;

			string classSubject;
			classSubject = taskText.substr(startSubstr, taskText.length() - startSubstr);		//remember to add description for each task type
			inTask = new HomeworkTask(description, *date, classSubject);
		}
		incompleteTasks.add(inTask);
	}
	out << "Tasks loaded successfullly" << endl;
}

 