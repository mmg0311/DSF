/*
 * BST.h
 *
 *  Created on: 19-Feb-2019
 *      Author: mohak
 */

#ifndef BST_H_
#define BST_H_
	struct Tree {
		int data;
		Tree * left,* right;
	};



	class BST {
	private:
		Tree  *root;
	public:
		BST();
		Tree * ret_root();
		virtual ~BST();
		void display(int *);
		int insert(int );
		Tree * getnode(int );
		int search(int );
		int height(Tree *);
		Tree * delete_node(Tree *,int );
		Tree * findMin(Tree *);
		void mirror(Tree *);
	};

#endif /* BST_H_ */
