/*
 * PriorityQueue.h
 *
 *  Created on: 21-Jan-2019
 *      Author: mohak
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

template<typename t>

class PriorityQueue {
protected:
	struct Node{
		int priority;
		t data;
		struct Node *next;
	};
	struct Node *front,*rear;
public:
	PriorityQueue();
	virtual ~PriorityQueue();
	void enqueue(t,int);
	t dequeue();
	int isEmpty();
	t getNode(int);
};
#include"PriorityQueue.tpp"
#endif /* PRIORITYQUEUE_H_ */
