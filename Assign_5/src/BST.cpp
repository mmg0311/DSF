
/*
 * BST.cpp
 *
 *  Created on: 11-Feb-2016
 *      Author: e11
 */

#include "BST.h"
#include<iostream>
#include"../../Assign_2/src/PriorityQueue.h"


BST::BST() {
	// TODO Auto-generated constructor stub
	root = NULL;
}


BST::~BST() {
	// TODO Auto-generated destructor stub
}


Tree * BST:: getnode(int d){
	Tree *q;
	q = new(Tree);
	q->data = d;
	q->left = NULL;
	q->right = NULL;
	return q;
}

//non - recurrsive insertion


int  BST :: insert(int d){

	if(root == NULL){
		root = getnode(d);
		return 0;
	}
	Tree * temp = root;
	Tree *temp2 = root;
	while(temp!=NULL && temp2->data !=d){
		temp2 = temp;
		if(d < temp2->data){
			temp = temp2->left;
		}
		else if(d > temp2->data){
			temp = temp2->right;
		}
	}
	if(d == temp2->data){
		return -1;
	}
	else if(d > temp2->data){
		temp2->right  = getnode(d);
	}
	else{
		temp2->left  = getnode(d);
	}
	return 0;
}



void BST :: display(int *arr){
	Tree * p =root;
	int i= 0;
		PriorityQueue<Tree *> q;
		while(p !=NULL){
			arr[i] = p->data;
			i++;
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

//non recurrsive search
int BST :: search(int x){
	if(root->data  == x){
		return 0;
	}
	Tree *p = root;
	while(p !=NULL){
		if(p->data == x){
			return 0;
		}
		if(p->data < x){
			p = p->right;
		}
		if(p->data > x){
			p = p->left ;
		}
	}
	return 1;
}


int BST :: height(Tree * r){
	if(r==NULL){
		return 0;
	}

	int hl = height(r->left);
	int hr = height(r->right);
	if(hl<hr){
		return (hr+1);
	}
	return (hl+1);

}

Tree * BST :: ret_root(){
	return root;
}

Tree * BST :: findMin(Tree *r){
	if(r->left == NULL){
		return r;
	}
	else{
		r = findMin(r->left);
		return r;
	}
}

Tree * BST :: delete_node(Tree *r,int d){
	if(r == NULL){
		return root;
	}
	else if(r->data < d){
		r->right = delete_node(r->right , d);
	}
	else if (r->data > d){
		r->left = delete_node(r->left , d);
	}
	//if data is found
	else{
		//case 1 it has no child
		if(r->left == NULL && r->right == NULL){
			delete(r);
			r = NULL;
		}
		//case 2 if it has single child
		else if(r->left == NULL) 	//only right child
		{
			Tree * temp;
			temp = r;
			r = r->right;
			delete(temp);
		}
		else if(r->right == NULL)	//only left child
		{
			Tree * temp;
			temp = r;
			r = r->left;
			delete(temp);
		}
		//case 3 if it has both left and right child
		//we will replace d with min in right subtree
		else{
			Tree * temp = findMin(r->right);
			r->data = temp->data;
			r->right = delete_node(r->right,temp->data);
		}

	}
	return r;
}

void BST ::  mirror(Tree *r){
	if(r == NULL){
		return;
	}
	mirror(r->left);
	mirror(r->right);
	Tree * temp = r->left;
	r->left = r->right ;
	r->right = temp;
}




