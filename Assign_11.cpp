//============================================================================
// Name        : Assign_11.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class Student{
	char name[20];
	int roll;
public:
	Student();
	Student getdata();
	void create();
	void add();
	int search(int );
	void display();
	void delete_rec();
};

Student :: Student(){
	name[0] = '\0';
	roll = 0;
}

Student Student :: getdata(){
	Student s;
	cin.ignore();
	cout << "Enter Name : ";
	cin.getline(s.name,20);
	cout << "Enter Roll Number : ";
	cin >> s.roll;
	return s;
}

void Student :: create(){
	int n;
	Student t;
	fstream f;
	f.open("file",ios::binary | ios::out);		//open in out mode to write
	cout << "How many students data you want to enter ?\n";
	cin >> n;
	for(int i=0;i<n;i++){
		t = getdata();
		f.write((char *)&t,sizeof(t));
	}
	f.close();
}

void Student :: add(){
	fstream f;
	f.open("file",ios::app | ios::binary);
	Student s;
	s = getdata();
	f.write((char *)&s,sizeof(s));
	f.close();
}

void Student :: display(){
	fstream f;
	Student s;
	f.open("file",ios::in | ios::binary);
	cout << "Roll Number\t\tName\n";
	f.read((char *)&s,sizeof(s));
	while(f){
		cout  <<s.roll << "\t" << s.name << endl;
		f.read((char *)&s,sizeof(s));
	}
	f.close();
}

int Student :: search(int r){
	fstream f;
	Student s;

	f.open("file",ios::in | ios::binary);
	f.read((char *)&s,sizeof(s));
	while(f){
		if(s.roll == r){
			cout << "Name : ";
			cout << s.name << endl;
			f.close();
			return 0;
		}
		f.read((char *)&s,sizeof(s));
	}
	cout << "There is no student with given roll number\n";
	f.close();
		return 1;

}

void Student :: delete_rec(){
	int r,c;
	cout << "Enter the Students roll number whose data is to be deleted\n ";
	cin >> r;
	cout << "Record to be deleted\n";
	c = search(r);
	if(c==1){
		return;
	}
	fstream f,f2;
	f.open("file", ios::in | ios::binary);
	f2.open("temp",ios::out | ios::binary);
	Student s;
	f.read((char *)&s,sizeof(s));
	while(f){
		if(s.roll != r){
			f2.write((char *)&s,sizeof(s));
		}
		f.read((char *)&s,sizeof(s));
	}
	f.close();
	f2.close();
	remove("file");
	rename("temp","file");
	cout << "Successfully deleted !!\n";
}

int main() {
	Student s;
	int choice,r;
	do{
		cout << "*************MENU*****************\n";
		cout << "1.Create Database\n2.Add Student\n3.Display\n4.Search\n5.Delete\n6.Exit\n";
		cin >> choice;
		switch(choice){
		case 1:
			s.create();
			break;
		case 2:
			s.add();
			break;
		case 3:
			s.display();
			break;
		case 4:
			cout << "Enter roll number to be searched\n";
			cin >> r;
			r =  s.search(r);
			break;
		case 5:
			s.delete_rec();
			break;
		case 6:
			break;
		default:
			cout << "Enter valid choice\n";
		}
	}
	while(choice!=6);

}
