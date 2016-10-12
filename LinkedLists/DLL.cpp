/*
 * DLL.cpp
 *
 *  Created on: Sep 28, 2016
 *      Author: Debra
 */

#include "DLL.hpp"
#include "DNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL() {
	first = NULL;
	last = NULL;
	size = 0;
}
DLL::~DLL() {
	DNode *tmp = first;
	while (first != NULL) {
		tmp = first->next;
		delete first;
		first = tmp;
		size--;
	}
	first = NULL;
	last = NULL;
}
void DLL::printDLL() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->data << "->";
		tmp = tmp->next;
	}
	cout << endl;
}
void DLL::printRevDLL() {
	DNode *tmp = last;
	while (tmp != NULL) {
		cout << tmp->data << "->";
		tmp = tmp->prev;
	}
	cout << endl;
}

void DLL::addFirst(int x) { //2 pts
//add very first element to list
	DNode *node = new DNode(x);
	first = node;
	last = node;
	size++;
}
void DLL::addAtFront(int x) { //2 pts
//	add a new node to the beginning of the list
	DNode *node = new DNode(x);
	node->next = first;
	first = node;
	size++;

}

void DLL::push(int x) { //2 pts
// add a new node to the end of the list
	DNode *node = new DNode(x);
	last->next = node;
	node->prev = last;
	last = node;
	size++;
}

void DLL::addAtK(int x, int k) { //4 pts
//add at position k a new node with x as the data
	DNode *tmp = first;
	if (k == 0) {
		addAtFront(x);
	} else if (k < size && k >= 0) {
		for (int i = 0; i < k - 1; i++) {
			tmp = tmp->next;
		}
		DNode *tmp2 = tmp->next;
		tmp->next = new DNode(x);
		tmp->next->next = tmp2;
		size++;
	}
}
void DLL::join(DLL *list2) { //2 pts
// join list 2 to the end of the list, modifying the size of the list
	last->next = list2->first;
	last = list2->last;
	size = size + list2->size;
}

int DLL::pop() { //5 pts
//popping the last node off the end of the list and returning that data
	DNode *tmp = last;
	int nodeData = last->data;
	tmp = tmp->prev;
	delete last;

	//DEINCREMENT
	size --;
	last = tmp;
	last->next = NULL;
	return nodeData;

}
DNode *DLL::findKth(int k) {
//find the element at the kth position and returning a pointer to that node
	DNode *tmp = first;
	for (int i = 0; i < k - 1; i++) {
		tmp = tmp->next;
	}
	return tmp;
}

int DLL::findK(int k) {
	DNode *tmp = first;
	int ind = 0;
	while (tmp != NULL && tmp->data != k) {
		tmp = tmp->next;
		ind++;
	}
	if (ind < size) {
		return ind;
	} else {
		return -1;
	}
}

int DLL::remFirst() { //2 pts
//remove the first node from the list, returning its data
	DNode *tmp = first;
	int nodeData = first->data;
	tmp = tmp->next;
	delete first;
	size --;
	first = tmp;
	first->prev = NULL;
	return nodeData;
}

int DLL::remKth(int k) { //4 pts
//remove the kth element of the list, returning its data
	if (k == 0) {
		return remFirst();
	} else if (k < size && k > 0) {
		DNode *tmp = first;
		for (int i = 0; i < k - 1; i++) {
			tmp = tmp->next;
		}
		int x = tmp->next->data;
		DNode *tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		tmp2->next = NULL;
		tmp2->prev = NULL;
		delete tmp2;
		size --;
		return x;
	} else {
		return -1;
	}
}
void DLL::RecursiveReverse(DLL *l2) { //6 pts
// RECURSIVELY reverses the list
	if (l2->first->prev == NULL) {
		l2->last = l2->first;
	}
	DNode *tmp = l2->first->prev;
	l2->first->prev = l2->first->next;
	l2->first->next = tmp;
	if (l2->first->prev == NULL) {
		return;
	}
	l2->first = l2->first->prev;
	RecursiveReverse(l2);
	return;

}
void DLL::sortDLL() { //10 pts
//sort the list from smallest to largest
	if (size == 0) {
		return;
	}
	bool swap = true;
	while (swap) {
		swap = false;
		DNode *tmp = first;
		for (int i = 0; i < size - 1; i++) {
			tmp = tmp->next;
			if (tmp->data < tmp->prev->data) {
				int tmpNum = tmp->data;
				tmp->data = tmp->prev->data;
				tmp->prev->data = tmpNum;
				swap = true;
			}
		}
	}
	return;
}

void DLL::Merge2(DLL *l2) { //10 pts
//Merge two sorted lists into one longer sorted list, and setting
//the current list to the longer sorted list
// Note that I sorted both lists before I called this.
//also note that joining the two lists and then sorting is NOT what I want
//here - I want this function to start at the beginning of each list,
//and pull the smallest of the 2 values into the new list, then move up
//one in that particular list.
// e.g.,
// l1 = 3,7,12,15,22,23,24,29    l2=4,8,12,13,27
// n=3
// l1 = 7,12,15,22,23,24,29    l2=4,8,12,13,27
// n=3,4
// l1 = 7,12,15,22,23,24,29    l2=8,12,13,27
// n=3,4,7
// l1 = 12,15,22,23,24,29    l2=8,12,13,27
// n=3,4,7,8
// l1 = 12,15,22,23,24,29    l2=12,13,27
// n=3,4,7,8,12
// l1 = 15,22,23,24,29    l2=12,13,27
// n=3,4,7,8,12,12
// l1 = 15,22,23,24,29    l2=13,27
// n=3,4,7,8,12,12,13
// l1 = 15,22,23,24,29    l2=27
// n=3,4,7,8,12,12,13
// l1 = 15,22,23,24,29    l2=27
// n=3,4,7,8,12,12,13,15
// l1 = 22,23,24,29    l2=27
// n=3,4,7,8,12,12,13,15,22
// l1 = 23,24,29    l2=27
// n=3,4,7,8,12,12,13,15,22,23
// l1 = 24,29    l2=27
// n=3,4,7,8,12,12,13,15,22,23,24
// l1 = 29    l2=27
// n=3,4,7,8,12,12,13,15,22,23,24,27
// l1 = 29    l2
// n=3,4,7,8,12,12,13,15,22,23,24,27,29


}
void DLL::RemoveDuplicates() { //12pts
// assumes the list is unsorted, removes all duplicates from the list
//Note how massively easier this would be if we just sorted the list first...
// Note also that you can use a helper function if you like
	sortDLL();
	if (size == 0) {
		return;
	}
	DNode *tmp = first;
	for (int i = 0; i < size - 1; i++) {
		tmp = tmp->next;
		if (tmp->data == tmp->prev->data) {
			remKth(i);
		}
	}
}

