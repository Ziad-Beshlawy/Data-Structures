#include"inord_list.h"
#include <iostream>
using namespace std;

inord_list::inord_list(){
	Head = NULL;
	Tail = NULL;
	Current = NULL;
}

inord_list::~inord_list(){
	Current = Head;
	while(Current != NULL){
		Current = Head->Next;
		Head->smallCurrent = Head->smallHead;
		while(Head->smallCurrent != NULL){
			Head->smallCurrent = Head->smallHead->smallNext;
			delete Head->smallHead;
			Head->smallHead = Head->smallCurrent;
		}
		delete Head;
		Head = Current;
	}
}

bool inord_list::insert(const ListElemType &e, int LineNumber){
	Link addedNode;
	smallLink addedSmallNode;
	addedNode = new Node;
	addedSmallNode = new smallNode;
	if(addedNode == NULL || addedSmallNode == NULL) return false;
	addedSmallNode->ln_num = LineNumber;
	addedSmallNode->smallNext = NULL;
	if(Head == NULL){
		Head = addedNode;
		Tail = addedNode;
		Head->elem = e;
		Head->occ = 1;
		Head->smallHead = addedSmallNode;
		Head->smallCurrent = Head->smallHead;
		Head->smallTail = addedSmallNode;
		Head->Next = NULL;
		return true;
	}
	else if(e < Head->elem){
		addedNode->Next = Head;
		Head = addedNode;
		Head->elem = e;
		Head->occ = 1;
		Head->smallHead = addedSmallNode;
		Head->smallCurrent = Head->smallHead;
		Head->smallTail = addedSmallNode;
		return true;
	}
	else if(e == Head->elem){
		Head->occ++;
		if(LineNumber > Head->smallTail->ln_num){
			Head->smallTail->smallNext = addedSmallNode;
			Head->smallTail = addedSmallNode;
		}
		delete addedNode;
		return true;
	}
	else if(e > Tail->elem){
		addedNode->Next = NULL;
		Tail->Next = addedNode;
		Tail = addedNode;
		Tail->elem = e;
		Tail->occ = 1;
		Tail->smallHead = addedSmallNode;
		Tail->smallCurrent = Tail->smallHead;
		Tail->smallTail = addedSmallNode;
		Tail->Next = NULL;
		return true;
	}
	else if(e == Tail->elem){
		Tail->occ++;
		if(LineNumber > Tail->smallTail->ln_num){
			Tail->smallTail->smallNext = addedSmallNode;
			Tail->smallTail = addedSmallNode;
		}
		delete addedNode;
		return true;
	}
	else{
		Link previous;
		previous = Head;
		while(e > previous->Next->elem){
			previous = previous->Next;
		}
		if(e == previous->Next->elem){
			previous->Next->occ++;
			if(LineNumber > previous->Next->smallTail->ln_num){
				previous->Next->smallTail->smallNext = addedSmallNode;
				previous->Next->smallTail = addedSmallNode;
			}
			delete addedNode;
		}
		else{
			addedNode->Next = previous->Next;
			previous->Next = addedNode;
			addedNode->elem = e;
			addedNode->occ = 1;
			addedNode->smallHead = addedSmallNode;
			addedNode->smallCurrent = addedSmallNode;
			addedNode->smallTail = addedSmallNode;
		}
		return true;
	}
}

bool inord_list::first(ListElemType &e){
	if(Head == NULL) return false;
	Current = Head;
	e = Current->elem;
	return true;
}

bool inord_list::next(ListElemType &e){
	if(Current == NULL) return false;
	Current = Current->Next;
	if(Current == NULL) return false;
	e = Current->elem;
	return true;
}


bool inord_list::getLineNumber(int &LineNumber){
	if(Current == NULL) return false;
	if(Current->smallCurrent == NULL){
		Current->smallCurrent = Current->smallHead;
		return false;
	}
	LineNumber = Current->smallCurrent->ln_num;
	Current->smallCurrent = Current->smallCurrent->smallNext;
	return true;
}

int inord_list::getOcc(){
	if(Current == NULL) return -1;
	else return Current->occ;
}
