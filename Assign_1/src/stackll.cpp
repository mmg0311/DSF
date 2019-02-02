/*
 * stackll.cpp
 *
 *  Created on: 23-Dec-2018
 *      Author: mohak
 */

#include "stackll.h"
#include <iostream>
using namespace std;
stack_ll::stack_ll() {
	// TODO Auto-generated constructor stub
	top = NULL;
}

stack_ll::~stack_ll() {
	// TODO Auto-generated destructor stub
	struct Node *p;
	p = top;
	while(p != NULL){
		top = top->next;
		delete(p);
		p = top;
	}
}

void stack_ll :: push(char x){
	struct Node *p;
	p = new(struct Node );
	p->data = x;
	p->next = NULL ;
	p->next = top ;
	top = p;
}

char stack_ll :: pop(){
	if(isEmpty()==1){
	struct Node *temp = top;
	top = top->next;
	char x = temp->data;
	delete(temp);
	return x;
	}
	return -1;
}

int stack_ll :: isEmpty(){
	if(top == NULL){
		return 0;
	}
	return 1;
}

char stack_ll :: gettop(){
	if(isEmpty()==1){
		struct Node *temp = top;
		//top = top->next;
		char x = temp->data;
		//delete(temp);
		return x;
		}
		cout << "IT IS EMPTY" << endl;
		return -1;
}


