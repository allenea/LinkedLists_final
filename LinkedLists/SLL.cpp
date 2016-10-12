/*
 * SLL.cpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Debra
 */

#include "SLL.hpp"
#include "SNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

SLL::SLL(){
	first = NULL;
	last = NULL;
	size = 0;
}
SLL::~SLL(){
	SNode *tmp = first;
	while (first != NULL) {
		tmp = first->next;
		delete first;
		first = tmp;
		size --;
	}
	first = NULL;
	last = NULL;
}
void SLL::printSLL() {
	SNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->data << "->";
		tmp = tmp->next;
	}
	cout << endl;
}

void SLL::addFirst(int x) { // 3 pts
//make a new list of only one node, data is x
	SNode *node = new SNode(x);
	first = node;
	last = node;
	size = 1;
}
void SLL::addAtFront(int x) {  //3 pts
//add a new node to the front of the list with data being x
	SNode *node = new SNode(x);
	node->next = first;
	first = node;
    size ++;
}

void SLL::push(int x) { //6 pts

//add a new node to the end of the list, with data x
	SNode *node = new SNode(x);
	last->next = node;
	last = node;
	size ++;


}

void SLL::addAtK(int x, int k){

	SNode *tmp = first;
	if (k==0) {
		addAtFront(x);
		return;
	}
	if (k < size  && k >= 0) {
		for (int i = 0; i < k-1; i++) {
			tmp = tmp->next;
		}
		SNode *tmp2 = tmp->next;
		tmp->next = new SNode(x);
		tmp->next->next = tmp2;
		size++;
	}

}
void SLL::join(SLL *list2){ //3 pts
	//cout<<"size"<<size<<endl;
	//cout<<"size2"<<list2->size<<endl;
//join the list with list2, making the current list one longer list
	last->next = list2->first;
	last = list2->last;

	size = size + list2->size;
	//cout<<"Final Size"<<size<<endl;
	list2->printSLL();

}

int SLL::pop() {
	if (size > 0) {
		int x = last->data;
		if (first != last ){
			SNode *tmp = first;
			for (int i = 0; i < size-2;i++) {
				tmp = tmp->next;
			}
			delete last;
			last = tmp;
			last->next = NULL;
		}
		else {
			delete last;
			first = NULL;
			last = NULL;
		}
		size --;
		return x;
	}
	else {
		return -1;
	}
}
SNode *SLL::findKth(int k) { //4 pts
// find the node at the kth location and return it
	SNode *tmp = first;
	for(int i = 0; i < k-1; i++){
		tmp = tmp->next;
	}
	return tmp;
}

int SLL::findK(int k) {
	SNode *tmp = first;
	int ind = 0;
	while (tmp != NULL && tmp->data != k) {
		tmp = tmp->next;
		ind++;
	}
	if (ind < size) {
		return ind;
	}
	else {
		return -1;
	}
}
int SLL::remFirst() { //3 pts
//remove the first node from the list, returning its data
	SNode *tmp = first;
	int Data = tmp->data;
	first = first->next;
	delete tmp;
	size --;
	return Data;

}
int SLL::remKth(int k) {
	if (k < size && k > 0) {
		SNode *tmp = first;
		for (int i = 0; i < k -1; i++) {
			tmp = tmp->next;
		}
		int x = tmp->next->data;
		SNode *tmp2= tmp->next;
		tmp->next = tmp->next->next;
		delete tmp2;
		size --;
		return x;
	}
	return -1;
}

void SLL::reverseList(){ //10 pts
//Reverses the list, after completed, the last should be the first
//in the list and the first should be the last
//Challenge - I did this with one pass across the list
	SNode *curr = first;
	SNode *tmp1 = NULL;
	SNode *tmp2 = first->next;
	cerr << "size: " << size << endl;
	for(int i = 0; i < size-1; i++){
		cerr << "i: " << i << endl;
		curr->next = tmp1;
		tmp1 = curr;
		curr = tmp2;
		tmp2 = tmp2->next;
		//cout << curr->data << " " << curr->next->data << endl;
	}
	SNode *tmp3 = first;
	first = last;
	last = tmp3;
}

