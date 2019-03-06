//============================================================================
// Name        : graph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include<string.h>
#include<iomanip>
#include"stackll.h"
#include<queue>
using namespace std;

struct user{
	char name[30];
	int d,month,year;		//for date of birth
	int friends;			//number of friends
	int comments;			//number of comments given user has made
};

struct list{
	int visited;			//will be 1 if visited and 0 else
	user *u;				//pointer to structure user
	list *down;
	struct edge *side;		//will store friend list
};

struct edge{									//will represent its friends i.e edges between two vertices
	list * friend_user;
	edge * next;
};

class facebook{
	int count;
	list *top;
public:
	facebook();
	void getdata();
	void display_list();
	list * makelist(user* );
	int make_friend(int ,list *);
	void display();
	void max_friends();
	void get_birth(int );
	void dfs(int );
	void bfs();
	void unvisited();			//will mark all list nodes as unvisited
};

void facebook :: max_friends(){
	struct list *temp = top;
	int max = temp->u->friends;
	while(temp!=NULL){
		if(temp->u->friends > max){
			max = temp->u->friends ;
		}
		temp = temp->down;
	}
	temp = top;
	cout << "{ " ;
	while(temp!=NULL){
		if(temp->u->friends==max){
			cout << temp->u->name << ", ";
		}
		temp = temp->down;
	}
	cout << "} has maximum friends (" << max << ") on facebook" ;
}

void facebook :: display(){
	struct list *temp = top;
	struct edge *temp2;
	while(temp!=NULL){
		temp2 = temp->side;
		cout << temp->u->name  ;						//display user name
		while(temp2 != NULL){
			cout << " -> " ;
			cout << setw(5) << setiosflags(ios::left)<< temp2->friend_user->u->name ;	//display friends
			temp2 = temp2->next;
		}
		temp = temp->down;
		cout << endl;
	}
}

facebook :: facebook(){
	count = 0;
	top = NULL;
}

void facebook :: getdata(){
	int ch2=0,x=0;
	user *u  = new (user);
	list *l;
	cout << "ENTER NAME : ";
	cin.ignore();
	cin.getline(u->name,30);
	cout << "ENTER DATE OF BIRTH : \n";
	cout << "DATE : " ;
	cin  >> u->d;
	cout << "MONTH : ";
	cin  >> u->month;
	cout << "YEAR : ";
	cin  >> u->year;
	u->friends=0;								//initially no friends
	//validation for date
		if(u->d<=0 || u->d>31 || u->month<=0 || u->month >12 || u->year >2018){
					cout << "PLEASE ENTER VALID DATE OF BIRTH\n" ;
					return;
		}
		else{
			if(u->month == 2 && u->d >29){									//will check for feb month
					cout << "PLEASE ENTER VALID DATE OF BIRTH\n";
					return;
			}
			else{
				l = makelist(u);//put it in list
				x++;
			}
		}
		//will pass the data to list
		if(count!=0 && x!=0){
			cout << "RECCOMENDED FRIENDS :\n";
			display_list();
			cout << "Press \"-1\" to skip";
			do{
				cout << "\nEnter choice : " ;
				cin >> ch2;
				if(ch2==-1){
					break;
				}
				if(ch2>count){
					cout << "enter valid choice " << endl;
				}
				else{
					//cout << "call make friend";
					x = make_friend(ch2,l);
					if(x==1){
						cout << "friend request accepted" << endl;
						u->friends++;
					}
					else if(x==0){
						cout << "already friends" << endl;
					}
				}
			}
			while(1);
		}
		count ++;
}

list * facebook :: makelist(user *a){
	struct list *p = new(struct list);
	p->u = a;
	p->down = NULL;
	p->side = NULL;
	if(top == NULL){
		top = p;
	}
	else{
		struct list  *temp = top;
		while(temp->down != NULL){
				temp = temp->down;
		}
		temp->down = p;
	}
	return p;
}

void facebook :: display_list(){
	list *temp = top;
	int i=1;
	while(temp->down!= NULL){
		cout << i  << ". "<< temp->u->name << endl ;
		temp = temp->down;
		i++;
	}
}

int facebook :: make_friend(int x,list *a){
	struct list *temp = top ;
	struct edge *p = new(struct edge) ;
	p->friend_user = a;
	p->next = NULL;
	while((x-1)!=0){
		x--;
		temp = temp->down;
	}
	if(temp ->side == NULL){
	//cout << "temp->side == NULL";
		temp -> side = p;
		return 1;
	}
	//cout << "here";
	struct edge * q = temp->side,*r;
	//cout << q;
	while(q!= NULL){
	//cout << q->friend_user->u->name;
		if(strcmp(q->friend_user->u->name,a->u->name)==0){
			delete p;
			return 0;
		}
		r = q;
		q = q->next;
	}
	r->next = p;
	return 1;
}

void facebook :: get_birth(int mon){
	struct list *temp = top;
	int c=1;
	while(temp!=NULL){
		if(temp->u->month == mon){
			cout << c << ". " << temp->u->name << endl;
			c++;
		}
		temp = temp->down;
	}
	if(c==1){
		cout << "No-one in database has birthday in specified month i.e (" << mon << ")\n" ;
	}
}

void facebook :: unvisited(){			//for unvisited vertices
	struct list *temp = top;
	while(temp!=NULL){
		temp->visited = 0;
		temp = temp->down;
	}
}

void facebook :: dfs(int m){		//dfs traversal
	stack_ll<list *> s;
	int check=0;
	list *p=top;
	edge * q;
	unvisited();				//mark all as unvisited
	s.push(top);
	while(s.isEmpty()){
		p = s.pop();
		q = p->side;
		if(p->visited==0){
			p->visited = 1;
			if(m==p->u->month){
			cout<< p->u->name << "\t" ;
			check++;
			}
		}
		while(q!=NULL){
			if(q->friend_user->visited==0){
			s.push(q->friend_user);
			}
			q = q->next;
		}
	}
	if(check==0){
		cout << "No-one in database has birthday in specified month i.e (" << m << ")\n" ;
	}
	else{
		cout << "Has birthday in month " << m << endl;
	}
}

void facebook :: bfs(){		//bfs traversal
	unvisited();
	queue<list *> q;
	list * p = top;
	int max = p->u->friends;
	edge *e;
	q.push(p);
	while(!q.empty()){
		p = q.front();
		q.pop();
		e = p->side;
		if(p->visited==0){
			p->visited = 1;
			if(max<p->u->friends){
				max = p->u->friends;
			}
		}
		while(e!=NULL){
			if(e->friend_user->visited==0){
			q.push(e->friend_user);
			}
			e = e->next;
		}
	}
	p = top;
	cout << "{ " ;
	while(p!=NULL){
		if(p->u->friends==max){
			cout << p->u->name << ", ";
		}
		p = p->down;
	}
	cout << "} has maximum friends (" << max << ") on facebook" ;
}

int main() {
	int ch,month;
	facebook f;
		do{
			cout << "\nENTER CHOICE :\n 1.Enter a user\n 2.Display\n 3.Display who has max friends\n 4.Find who has post maximum and minimum comments";
			cout << "\n 5.Find users having birthday in given month\n 6.DFS traversal (birthday in given month)\n 7.BFS traversal(max friends)\n 8.Exit\n";
			cin >> ch;
			switch(ch){
			case 1:
				f.getdata();
				break;
			case 2:
				f.display();
				break;
			case 3:
				f.max_friends();
				break;
			case 4:
				break;
			case 5:
				cout << "Enter the month : ";
				cin >> month;
				f.get_birth(month);
				break;
			case 6:
				//dfs
				cout << "Enter the month : ";
				cin >> month;
				f.dfs(month);
				break;
			case 7:
				//bfs
				f.bfs();
				break;
			case 8:
				break;
			default :
				cout << "PLEASE ENTER VALID CHOICE " << endl;
				break;
			}
		}
		while(ch!=8);
}
