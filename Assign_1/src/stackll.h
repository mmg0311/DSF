/*
 * stackll.h
 *
 *  Created on: 23-Dec-2018
 *      Author: mohak
 */

#ifndef STACKLL_H_
#define STACKLL_H_

class stack_ll {
private:
	struct Node{
		char data;
		struct Node * next;
	};
	struct Node *top;
public:
	stack_ll();
	virtual ~stack_ll();
	void push(char );
	char pop();
	int isEmpty();
	char gettop();
};

#endif /* STACKLL_H_ */
