/*
 * stackll.cpp
 *
 *  Created on: 10-Feb-2019
 *      Author: mohak
 */

#include "stackll.h"
#include <iostream>
using namespace std;
template<typename t>
stack_ll<t>::stack_ll() {
	// TOD Auto-generated constructor stub
	top = NULL;
}
template<typename t>
stack_ll<t>::~stack_ll() {
	// TODO Auto-generated destructor stub
	struct Node *p;
	while(top != NULL){
		p = top;
		top = top->next;
		delete(p);
	}
}
template<typename t>
void stack_ll <t>:: push(t x){
	struct Node *p;
	p = new(struct Node );
	p->data = x;
	p->next = NULL ;
	p->next = top ;
	top = p;
}
template<typename t>
t stack_ll <t>:: pop(){
	struct Node *temp = top;
	top = top->next;
	t x = temp->data;
	delete(temp);
	return x;
}
template<typename t>
int stack_ll<t> :: isEmpty(){
	if(top == NULL){
		return 0;
	}
	return 1;
}
template<typename t>
t stack_ll<t> :: gettop(){
	struct Node *temp = top;
		//top = top->next;
		t x = temp->data;
		//delete(temp);
		return x;
}






















