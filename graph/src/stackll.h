/*
 * stackll.h
 *
 *  Created on: 20-Dec-2018
 *      Author: e11
 */

#ifndef STACKLL_H_
#define STACKLL_H_
template<typename t>
class stack_ll {
private:
	struct Node{
		t data;
		struct Node * next;
	};
	struct Node *top;
public:
	stack_ll();
	virtual ~stack_ll();
	void push(t );
	t pop();
	int isEmpty();
	t gettop();
};
#include"stackll.tpp"
#endif /* STACKLL_H_ */
