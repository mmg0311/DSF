/*
 * PriorityQueue.cpp
 *
 *  Created on: 21-Jan-2019
 *      Author: mohak
 */

#include "PriorityQueue.h"
#include<iostream>
using namespace std;
template<typename t>
PriorityQueue<t>::PriorityQueue() {
	// TODO Auto-generated constructor stub
	front = NULL;
	rear = NULL;

}
template<typename t>
PriorityQueue<t>::~PriorityQueue() {
	// TODO Auto-generated destructor stub
	struct Node *x;
		while(front != NULL)
		{
			x=front;
			front=front->next;
			delete(x);
		}
	rear=NULL;
}
template<typename t>
void PriorityQueue<t>::enqueue(t d,int priority){
	struct Node *temp= new Node;
	temp->priority = priority;
	temp->data = d;
	temp->next = NULL;
	if(isEmpty())
	{
		front=temp;
		rear=temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
}
}

template<typename t>
int PriorityQueue<t>:: isEmpty(){
	if(front == NULL){
		return 1;
	}
	return 0;
}
template<typename t>
t PriorityQueue<t> :: dequeue(){
	struct Node *current = front;
	struct Node *temp1 = front;
	struct Node *temp2;
	while(temp1 != NULL)
	{
		if(temp1->priority > current->priority)
			current = temp1;
		temp1=temp1->next;
	}
	temp1=front;
	if(current != front)
	{
		while(temp1 != NULL)
		{
			if(temp1==current)
				break;
			temp2=temp1;
			temp1=temp1->next;
		}
		temp2->next=current->next;
	}
	else
		front=front->next;
	t d= current->data;
	delete(current);		
return d;
}

template<typename t>
t PriorityQueue<t>::getNode( int n){
t d;
struct Node *temp=front;
for(int i = 1;i<n;i++){

temp = temp->next;
}
d = temp->data;
delete(temp);
return d;
/*int c=0;
	struct Node *current=front;
	while(c!=n && current!=NULL)
	{
		a[c]=current->data;
		current=current->next;
		c++;
} */

}






