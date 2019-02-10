//============================================================================
// Name        : Assign_4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
#include"stackll.h"

using namespace std;

class Exp{
private:
	struct Tree{
		char data;
		struct Tree *left;
		struct Tree *right;
	};
	char *exp;
	struct Tree *root;
	int l;

public:
	Exp(){
		exp = NULL ;
		l = 0;
		root = NULL;
	}
	void removeTree(struct Tree *);
	~Exp(){
		delete(exp);
	}
	void GET();
	void create();
	void display();
	void r_traversal();
	void nr_traversal();
	int input();
	void r_inorder(struct Tree *);
	void r_pre(struct Tree *);
	void r_post(struct Tree *);
	void nr_inorder();
	void nr_pre();
	void nr_post();
	int isoperator(int);
};

//TO DETERMINE IF IT IS AN OPERATOR

int Exp :: isoperator(int x){
	if(x==(int)'+' ||x== (int)'-' ||x== (int)'/' ||x== (int)'%' ||x== (int)'*'||x==(int)'^'){
		//typecast operator used because ascii value of character will be  passed in x
		return 0;
	}
	else{
		return 1;
	}
}

//get the input expression
void Exp::GET(){
	delete(exp);
	exp = new (char [30]);
	if(exp == NULL){
		cout << "MEMORY ALLOCATION FAILED\n" ;
		return;
	}
	cout << "ENTER AN EXPRESSION" << endl;
	cin >> exp;
	l = strlen(exp);
}

//remove tree

void Exp::removeTree(struct Tree *r){
	removeTree(r->left);
	removeTree(r->right);
	delete(r);
}


//create tree of input expression

void Exp::create(){
	stack_ll<struct Tree*> s;
	for(int i=0;i<l;i++){
		if(isoperator(exp[i])==0){
			struct Tree *t;
			//is operator
			t = new(struct Tree );
			t->data = exp[i];
			t->right = s.pop();
			t->left = s.pop();
			s.push(t);
		}

		else if(isalpha(exp[i])){
			struct Tree *t;
			//is alpha
			t = new(struct Tree );
			t->data = exp[i];
			t->left = NULL;
			t->right = NULL;
			s.push(t);
		}

	}
	root = s.gettop();
	//cout << root->data;
}


//recurssive preorder
void Exp::r_pre(struct Tree *r){
	if(r==NULL) return;
	cout << r->data <<" ";
	r_pre(r->left);

	r_pre(r->right);
}

//recurssive inorder
void Exp::nr_inorder(){
	stack_ll<struct Tree *> s1;
	struct Tree *r= root;
	while(r!=NULL || s1.isEmpty()){
		while(r!=NULL){
			s1.push(r);
			r = r->left;
		}
		r = s1.pop();
		cout << " " << r->data;
		r = r->right;
	}
}

//recurssive postorder
void Exp::r_post(struct Tree *r){
	if(r==NULL) return;
	r_post(r->left);
	r_post(r->right);
	cout << r->data <<" ";
}

//recurssive inorder
void Exp :: r_inorder(struct Tree *r){
	if(r==NULL) return;

	r_inorder(r->left);
	cout << r->data <<" ";
	r_inorder(r->right);
}

//non recurrssive preorder
void Exp :: nr_pre(){
	stack_ll<struct Tree *> s2;
	s2.push(root);
	struct Tree *r;

	while(s2.isEmpty()!=0){
		r = s2.pop();
		cout << " "  << r->data;
		if(r->right!=NULL){
		s2.push(r->right);
		}
		if(r->left!=NULL){
		s2.push(r->left);
		}
	}

}

void Exp::nr_post(){
	stack_ll<struct Tree *> p;
	stack_ll<struct Tree *> q;
	p.push(root);
	struct Tree *node;
    while (p.isEmpty()!=0) {
        // Pop an item from p and push it to q
        node = p.pop();
        q.push(node);

        // Push left and right children of removed item to p
        if (node->left)
            p.push( node->left);
        if (node->right)
            p.push( node->right);
    }

    // Print all elements of second stack
    while (q.isEmpty()!=0) {
        node = q.pop();
        cout << " " << node->data;
    }
}

void Exp::r_traversal(){
	cout << "-------------RECURSSIVE TRAVERSAL-------------------" << endl;
	int choice;
	do{
		cout << "\nENTER CHOICE:\n 1.INORDER TRAVERSAL\n 2.PRE-ORDER TRAVERSAL\n 3.POST-ORDER TRAVERSAL\n 4.EXIT" << endl;
		cin >> choice;
		switch(choice){
		case 1:
			cout << "IN-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			r_inorder(root);
			break;
		case 2:
			cout << "PRE-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			r_pre(root);
			break;
		case 3:
			cout << "POST-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			r_post(root);
			break;
		case 4:
			break;
		}
	}
	while(choice!=4);
}

void Exp::nr_traversal(){
	cout << "-------------NON-RECURSSIVE TRAVERSAL-------------------" << endl;
	int choice;
	do{
		cout << "\nENTER CHOICE:\n 1.INORDER TRAVERSAL\n 2.PRE-ORDER TRAVERSAL\n 3.POST-ORDER TRAVERSAL\n 4.EXIT" << endl;
		cin >> choice;
		switch(choice){
		case 1:
			cout << "IN-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			nr_inorder();
			break;
		case 2:
			cout << "PRE-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			nr_pre();
			break;
		case 3:
			cout << "POST-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
			nr_post();
			break;
		case 4:
			break;
		}
	}
	while(choice!=4);
}
int main() {
	int ch,c=0;
	Exp e;
	do{
		cout << "\nENTER CHOICE \n 1.ENTER EXPRESSION(POSTFIX)\n 2.RECURSSIVE TRAVERSAL\n 3.NON-RECURRSIVE TRAVERSAL\n 4.EXIT";
		cin >> ch;
		switch(ch){
		case 1:
			e.GET();
			e.create();
			c++;
			break;
		case 2:
			if(c==0){
				cout << "PLEASE ENTER EQUATION" << endl;
				break;
			}
			e.r_traversal();
			break;
		case 3:
			if(c==0){
				cout << "PLEASE ENTER EQUATION" << endl;
				break;
			}
			e.nr_traversal();
			break;
		case 4:
			break;
		default:
			cout << "ENTER VALID CHOICE" << endl;
			break;
		}
	}
	while(ch!=4);
	return 0;
}
