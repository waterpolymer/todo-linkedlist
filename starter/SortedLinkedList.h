#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

template <class T, class Comparator>
class SortedLinkedList {
private:
	struct Node
	{
		T data;
		Node* next;
	};
	Node* d_head;
	int d_size;

public:
	SortedLinkedList();
	~SortedLinkedList();

	bool insert(const T& data);
	T at(const int& pos);
	bool removePos(const int& pos);
	bool isEmpty() { return (d_size == 0); };
	int size() { return d_size; std::cout << "galp\n"; };
};


template <class T, class Comparator>
SortedLinkedList<T, Comparator>::SortedLinkedList() :
	d_head(nullptr), d_size(0) {};

template <class T, class Comparator>
SortedLinkedList<T, Comparator>::~SortedLinkedList() {
	Node* deleteMe = d_head;
	while (d_head != nullptr) {
		d_head = d_head->next;
		delete deleteMe;
		deleteMe = d_head;
	}
}

template <class T, class Comparator>
T SortedLinkedList<T, Comparator>::at(const int& pos) {
	if (d_size < pos || d_size == 0) {
		throw std::out_of_range("Out of range exception");
	}

	Node* nodeTraverser = d_head;
	int posCounter = 1;							//numbering of most things starts at one
	while (nodeTraverser != nullptr) {
		if (posCounter == pos) {
			return nodeTraverser->data;
		}
		nodeTraverser = nodeTraverser->next;
		++posCounter;
	}
}

template <class T, class Comparator>
bool SortedLinkedList<T, Comparator>::insert(const T& data) {
	Node* newData = new Node{ data, nullptr };
	
	Comparator comparator;
	
	if (d_head == nullptr) { //need to compare first element
		d_head = newData;
		++d_size;
		return true;
	}

	if (comparator(data, d_head->data)){
		newData->next = d_head;
		d_head = newData;
		++d_size;
		return true;
	}

	if (d_head->next == nullptr) {
		d_head->next = newData;
		++d_size;
		return true;
	}

	Node* listTraverser = d_head->next;
	Node* listTraverserTrail = d_head;

	if (listTraverser->next == nullptr) {		//if list traverser->next starts as null, it won't go through the while loop
		if (comparator(data, listTraverser->data)) {
			newData->next = listTraverser;
			listTraverserTrail->next = newData;
			++d_size;
			return true;
		}
	}

	while (listTraverser->next != nullptr) {
		if (comparator(data, listTraverser->data)){
			newData->next = listTraverser;			//Edit: No need it'll insert no matter what into either the last or next slot
			listTraverserTrail->next = newData;
			++d_size;	
			return true;
		}
		listTraverserTrail = listTraverserTrail->next;
		listTraverser = listTraverser->next;
	}

	listTraverser->next = newData;
	++d_size;
	return true;
}

template <class T, class Comparator>
bool SortedLinkedList<T, Comparator>::removePos(const int& pos) {
	if (d_size < pos || d_size == 0) {
		return false;
	}

	Node* deleteMe;
	if (pos == 1) {
		deleteMe = d_head;
		d_head = d_head->next;
		delete deleteMe;
		--d_size;
		return true;
	}

	int posCounter = 2;
	Node* listTraverser = d_head->next;
	Node* listTraverserTrail = d_head;
	while (listTraverser != nullptr) {
		if (posCounter == pos) {
			deleteMe = listTraverser;
			listTraverserTrail->next = listTraverser->next;
			delete deleteMe;
			--d_size;
			return true;
		}
		++posCounter;
		listTraverserTrail = listTraverser;
		listTraverser = listTraverser->next;
	}
	return true; //default to stop warnings
}

#endif // SORTEDLINKEDLIST_H_

