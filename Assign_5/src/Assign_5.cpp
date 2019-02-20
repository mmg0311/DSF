//============================================================================
// Name        : Assign_5.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include"BST.h"
#define COUNT 10
using namespace std;

void print(Tree *r1, int space)
{
     if (r1 == NULL)
        return;
    space += COUNT;

    print(r1->right, space);

    cout << endl;
    for (int i = COUNT; i < space; i++) {
        cout << " " ;
    }
    cout << r1->data << endl;

    print(r1->left, space);
}

int main() {
	BST b;
	int ch,count = 0,n,d;
	int *arr;
	Tree * r;
	do{
		cout << "ENTER CHOICE\n 1.INSERT\n 2.Display\n 3.DISPLAY LEVELWISE\n 4.DELETE\n 5.MIRROR IMAGE\n 6.SEARCH\n 7.HEIGHT\n 8.EXIT" << endl;
		cin >> ch;
		switch(ch){
		case 1:
			cout << "ENTER DATA TO BE INSERTED : " << endl;
			cin >> n;
			if(b.insert(n)==-1){
				cout << "NUMBER IS REPEATED " ;
				break;
			}
			count ++;
			r = b.ret_root();
			break;
		case 2:
				if(count == 0){
					cout << "PLEASE PROVIDE TREE FIRST" << endl;
					break;
				}
					print(r,0);
					cout << endl;
					break;
		case 3:
			if(count == 0){
				cout << "PLEASE PROVIDE TREE FIRST" << endl;
				break;
			}
			cout << "LEVEL WISE DISPLAY OF GIVEN BST IS : " << endl;
			arr  = new(int[count]);
			b.display(arr);
			for(int i = 0;i<count;i++){
				cout << " " <<arr[i] ;
			}
			cout << "\n" ;
			break;
		case 4:
			if(count == 0){
				cout << "PLEASE PROVIDE TREE FIRST" << endl;
				break;
			}
			cout << "ENTER NODE TO BE DELETED" << endl;
			cin >> d;
			n = b.search(d);
			if(n==1){
				cout << "NOT PRESENT " << endl;
				break;
			}
			cout << "BEFORE DELETING THE REQUESTED NODE THE BST IS" << endl;
			print(r,0);
			cout << endl;
			r = b.delete_node(r,d);
			cout << "AFTER DELETING THE REQUESTED NODE THE BST IS" << endl;
			print(r,0);
			cout << endl;
			count -- ;
			break;
		case 5:
			if(count == 0){
				cout << "PLEASE PROVIDE TREE FIRST" << endl;
				break;
			}
			b.mirror(r);
			print(r,0);
			break;
		case 6:
			if(count == 0){
				cout << "PLEASE PROVIDE TREE FIRST" << endl;
				break;
			}
			cout << "ENTER NUMBER TO BE SEARCHED : " ;
			cin >> n;
			n = b.search(n);
			if(n==0){
				cout << "NUMBER IS PRESENT IN TREE" << endl;
			}
			else{
				cout << "NOT PRESENT " << endl;
			}
			break;
		case 7:
			if(count == 0){
				cout << "PLEASE PROVIDE TREE FIRST" << endl;
				break;
			}
			n = b.height(r);
			cout << "HEIGHT OF BST IS : " << n-1 << endl;
			break;
		case 8:
			break;
		default:
			cout << "PLEASE ENTER VALID CHOICE " << endl;
			break;
		}
	}
	while(ch!=8);
	return 0;
}
