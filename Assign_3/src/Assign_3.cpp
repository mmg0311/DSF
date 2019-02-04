//============================================================================
// Name        : Assign_3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include"../../Assign_2/src/PriorityQueue.h"
using namespace std;

template<typename t>
class BinaryTree{
private:
	struct Node{
		t data;
		struct Node *left,*right;
	};
	struct Node *root,*r1;
	int count;
public:
	BinaryTree(){//constructor
		root =NULL;
		r1 = NULL;
		count =0;
	}
	void insert(t );
	int empty(){
		if(root==NULL){
			return 1;
		}
		return 0;
	}
	void displayLevel();
	void display();//level wise display
	void mirror(); // display mirror image
	void displayLeaf(struct Node *); // to display leaf nodes
	int height(); // calculate height
	int he(struct Node *);
	void pre(struct Node *);
	void post(struct Node *);
	void inorder(struct Node *);
	void callCopy();
	struct Node * copy(struct Node *r){
		struct Node *temp;
			if(r==NULL)
				return r;				//IF TREE IS EMPTY
			else
			{
				int x=r->data;			//GET DATA OF NODE
				temp  = new(struct Node);
				temp->data = x;
				temp->left = NULL;
				temp->right = NULL;	//ALLOCATE MEMORY
				temp->left=copy(r->left);		//CALL FOR LCHILD
				temp->right=copy(r->right);		//CALL FOR RCHILD
			}
			return temp;
	}
};



template<typename t>
void BinaryTree<t> :: callCopy(){
	cout << "-------------COPY-------------" <<endl;
	r1 = copy(root);
	cout << "PRE-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
	pre(r1);
	cout << endl;
	cout << "IN-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
	inorder(r1);
	cout << endl;
	cout << "POST-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
	post(root);
	cout << endl;
}


template<typename t>
void BinaryTree<t> :: insert(t a){
	struct Node *q;
	q  = new(struct Node);
	q->data = a;
	q->left = NULL;
	q->right = NULL;
	if(root == NULL){
		root = q;
	}
	else{
		int choice;
		struct Node *p;
		p = root;
		do{
			cout << "ON WHICH SIDE OF  " << p->data << " YOU WANT TO INSERT \n1.LEFT \n2.RIGHT" << endl;
			cin >> choice;
			switch(choice){
			case 1:
				if(p->left == NULL){
					p->left = q;
					count ++;
					return ;
				}
				else{
					p = p->left;
				}
				break;
			case 2:
				if(p->right == NULL){
					p->right = q;
					count ++;
					return;
				}
				else{
					p = p->right;
				}
				break;
			default :
				cout << "PLEASE ENTER VALID CHOICE !!" << endl;
				break;
			}
		}
		while(1);
	}
	count ++;
}

template<typename t>
void BinaryTree<t> :: pre(struct Node *r){
	if(r==NULL) return;
	pre(r->left);
	cout << r->data <<" ";
	pre(r->right);
}

template<typename t>
void BinaryTree<t> :: post(struct Node *r){
	if(r==NULL) return;
	post(r->left);
	post(r->right);
	cout << r->data <<" ";
}

template<typename t>
void BinaryTree<t> :: inorder(struct Node *r){
	if(r==NULL) return;
	cout << r->data <<" ";
	pre(r->left);
	pre(r->right);
}

template<typename t>
void BinaryTree<t> :: display(){
int c;
do{
	cout << "\nENTER CHOICE \n1.DISPLAY LEAVES \n2.DISPLAY LEVEL WISE\n3.PRE-ORDER \n4.POST-ORDER\n5.IN-ORDER\n6.EXIT\n";
	cin >> c;
	switch(c){
	case 1:
		cout << "LEAVES OF GIVEN TREE ARE : " << endl;
		displayLeaf(root);
		cout << "\n";
		break;
	case 2:
		cout << "LEVEL WISE DISPLAY OF GIVEN TREE IS : " << endl;
		displayLevel();
	    cout << endl;
		break;
	case 3:
		cout << "PRE-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
		pre(root);
		cout << endl;
		break;
	case 4:
		cout << "POST-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
		post(root);
		cout << endl;
		break;

	case 5:
		cout << "IN-ORDER TRAVERSAL OF GIVEN TREE IS :" << endl;
		inorder(root);
		cout << endl;
		break;
	case 6:
		break;
	default:
		cout << "ENTER VALID CHOICE" << endl;
		break;

	}
}
while(c!=6);

}

template<typename t>
void BinaryTree<t> :: displayLeaf(struct Node * T){
	if(T == NULL){
		return;
	}
	else{
		struct Node * p ;
		p = T;
		if(p->left == NULL && p->right == NULL){
			cout << p->data << " " ;
		}
		else{
			displayLeaf(p->left);
			displayLeaf(p->right);
		}
	}
}

template<typename t>
int BinaryTree<t> :: height(){
	return he(root);
}

template<typename t>
int BinaryTree<t> :: he(struct Node *r){
		if(r==NULL){
			return -1;
		}
		else{
			int max;
			max = he(r->left) > he(r->right) ? he(r->left):he(r->right) ; // ternary operator
			return max+1;
		}
}

template <typename t>
void BinaryTree <t> :: displayLevel(){
	struct Node * p =root;
	PriorityQueue<struct Node*> q;
	while(p !=NULL){
		cout << p->data << "  ";
		if(p->left != NULL){
		q.enqueue(p->left,1);
		}
		if(p->right!= NULL){
		q.enqueue(p->right,1);
		}
			if(q.isEmpty()==1){
				p = NULL;
				break;
			}
			else{
				p = q.dequeue();
			}
	}
}

int main() {
	BinaryTree<int> b;
		int ch,d,h;

		do{
			cout << "ENTER CHOICE :\n1.INSERT\n2.COPY\n3.DISPLAY \n4.HEIGHT OF BINARY TREE\n5.EXIT\n";
			cin >> ch;
			switch(ch){
			case 1:
				cout << "ENTER DATA TO BE INSERTED\n";
				cin>>d;
				b.insert(d);
				//insert

				break;

			case 2:
				//copy
				if(b.empty()){
					cout << "PLEASE GIVE INPUT" << endl;
					break;
				}
				b.callCopy();
				break;

			case 3:
				if(b.empty()){
					cout << "PLEASE GIVE INPUT" << endl;
					break;
				}
				//display
				b.display();
				break;

			case 4:
				if(b.empty()){
					cout << "PLEASE GIVE INPUT" << endl;
					break;
				}
				cout <<"HEIGHT OF BINARY TREE IS : " ;
				h = b.height();
				cout << h << endl;
				//height
				break;
			case 5:
				break;
			default:
				cout << "ENTER VALID CHOICE" <<endl;
				break;
			}
		}
		while(ch!=5);
	return 0;
}

