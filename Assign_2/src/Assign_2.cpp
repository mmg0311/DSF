//============================================================================
// Name        : Assign_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include"PriorityQueue.h"
#include<iomanip>
using namespace std;

typedef struct info{
	int id;
	char name[30];
	int age;
	int disease;
}info;

class patient{
private:
	PriorityQueue<info> q1;
	int n;
public:
	patient(){
		n = 0;
	}
	int Empty();
	info gettop();
	void enterData();
	void display(info);
	void displayall();
};

int patient :: Empty(){
	if(q1.isEmpty()){
		return 1;
	}
	return 0;
}

void patient::enterData(){
	n++;
	struct info temp;
	cout << "NAME OF PATIENT : " << endl;
	cin.ignore();
	cin.getline(temp.name,30);
	cout << "ENTER ADHAR NUMBER : " << endl;
	cin >> temp.id;
	label :
	cout << "ENTER DISEASE FROM BELOW MENTIONED LIST \n1.FEVER\n2.YELLOW FEVER\n3.DENGUE\n4.MALARIA\n5.TB\n6.HEART ATTACK\n";

	cin >> temp.disease;
	if(temp.disease <0 || temp.disease >6){
		cout << "PLEASE RE-ENTER DISEASE" << endl;
		goto label;
	}

	q1.enqueue(temp,temp.disease);
}

void  patient:: display(info temp){
	cout << setw(20)<< setiosflags(ios::left) << temp.name << setw(20) << setiosflags(ios::left) << temp.id ;
	switch(temp.disease){
	case 1:
		cout <<  setw(20)<< setiosflags(ios::left) << "FEVER" << endl;
		break;
	case 2:
		cout <<  setw(20)<< setiosflags(ios::left) << " YELLOW FEVER" << endl;
				break;
	case 3:
		cout <<  setw(20)<< setiosflags(ios::left) << "DENGUE" << endl;
				break;
	case 4:
		cout <<  setw(20)<< setiosflags(ios::left) << "MALARIA" << endl;
				break;
	case 5:
		cout <<  setw(20)<< setiosflags(ios::left) << "TB" << endl;
		break;
	case 6:
		cout <<  setw(20)<< setiosflags(ios::left) << "HEART ATTACK" << endl;
				break;

	}

}

void patient::displayall(){
	//struct info * arr;
	//arr = new struct info [n];
	//q1.getNode(arr,n);
		for(int i = 1;i<=n;i++){
			display(q1.getNode(i));
		}
		//delete(arr);
}

info patient :: gettop(){
	n--;
	info temp = q1.dequeue();
	return temp;
}

int main() {
	int ch;
	info t;
	patient a;
	do{
		cout << "ENTER CHOICE: \n1.ADD PATIENT\n2.DISPLAY PATIENT TOBE TREATED FIRST\n3.DISPLAY FULL LIST\n4.EXIT" << endl;
		cin >> ch;
		switch(ch){
			case 1:
					a.enterData();
					break;
			case 2:
				if(!a.Empty()){
					t = a.gettop();
				cout << "PATIENT OF HIGHEST PRIORITY IS: " << endl;
				cout << "======================================================================" << endl;
				cout << "NAME " << setw(20) << "ADHAR NUMBER " << setw(20) << "DISEASE" << endl;
				cout << "======================================================================" << endl;
				a.display(t);
				cout << "======================================================================" << endl;
				}
				else{
					cout << "LIST IS EMPTY" << endl;
				}
				break;
			case 3:
				if(!a.Empty()){
				cout << "======================================================================" << endl;
				cout << "NAME " << setw(20) << "ADHAR NUMBER " << setw(20) << "DISEASE" << endl;
				cout << "======================================================================" << endl;
				a.displayall();
				cout << "======================================================================" << endl;

				}
				else{
					cout << "LIST IS EMPTY" << endl;
				}
				break;
			case 4:
				break;
			default:
				cout << "ENTER VALID CHOICE " << endl;
		}
	}
	while(ch!=4);
	return 0;
}
