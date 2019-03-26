//============================================================================
// Name        : Assign_7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<iomanip>
#include<queue>
#include<string.h>
using namespace std;

struct list{
	int visit;			//used for traversal
	char v;
	list *down;
	struct edge *side;		//will store friend list
};

struct edge{									//will represent its friends i.e edges between two vertices
	int weight;				//will store weight of particular edge
	int visited;			//weather edge is visited or not
	int not_to_visit;
	int added;
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
	int make_friend(int ,list *);
	list * makelist();
	void display();
	void unvisited();			//will mark all list nodes as unvisited
	void kruskal();				//kruskal's algorithm to find mst
	int findmin();				//finding minimum weighted edge
	void mark_visited(int );
	int bfs(char ,char);
	void unvisited_2();
};

facebook :: facebook(){
	count = 0;
	top = NULL;
}

void facebook :: unvisited_2(){			//for unvisited vertices
	struct list *temp = top;
	while(temp!=NULL){
		temp->visit = 0;
		temp = temp->down;
	}
}

void facebook :: getdata(){
	int ch2=0,x=1;
	list *l;
	l = makelist();
	if(l == NULL){
		cout << "This vertex already exists";
		return;
	}
		//will pass the data to list
		if(count!=0&&x!=0){
			cout << "EDGE EXISTS BETWEEN :\n";
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
					x = make_friend(ch2,l);
					if(x==1){
						cout << "Edge formed" << endl;
					}
					else if(x==0){
						cout << "Edge already exists" << endl;
					}
				}
			}
			while(1);
		}
		count ++;
}

list * facebook :: makelist(){
	struct list  *temp = top;
	char ch;
	cout << "Enter name of vertex : ";
	cin >> ch;
	if(top!=NULL){
	while(temp->down != NULL){
		if(temp->v == ch){
			return NULL;			//if character already exists
		}
			temp = temp->down;
	}
	}
	struct list *p = new(struct list);
	p->v = ch;
	p->down = NULL;
	p->side = NULL;
	if(top == NULL){
		top = p;
	}
	else{

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
		cout << i  << ". "<< temp->v << endl ;
		temp = temp->down;
		i++;
	}
}

int facebook :: make_friend(int x,list *a){
	struct list *temp = top ;
	struct edge *p = new(struct edge) ;
	struct edge *p1 = new(struct edge) , *p3 ;
	cout << "ENTER WEIGHT OF EDGE : ";
	p->visited = 0;
	p->friend_user = a;
	p->next = NULL;
	if(a->side == NULL){
		a->side = p1;
	}
	else{
	p3 = a->side;
		while(p3->next != NULL){
			p3 = p3->next;
		}
		p3->next = p1;
	}
	p1->visited = 0;
	p1->added = 1;
	p1->friend_user = NULL;
	p1->next = NULL;
	while((x-1)!=0){
		x--;
		temp = temp->down;
	}
	cout << temp->v << a->v << " : ";
	cin >> p->weight;
	p1->weight = p->weight;
	if(temp ->side == NULL){
		temp -> side = p;
		p1->friend_user = temp;
		return 1;
	}

	struct edge * q = temp->side,*r;
	while(q!= NULL){
		if(q->friend_user->v == a->v){
			delete p;
			return 0;
		}
		r = q;
		q = q->next;
	}
	r->next = p;
	p1->friend_user = temp;
	return 1;
}

void facebook :: display(){
	struct list *temp = top;
	struct edge *temp2;
	while(temp!=NULL){
		temp2 = temp->side;
		cout << temp->v  ;						//display user name
		while(temp2 != NULL){
			cout << " -> (" << temp2->weight << ")" ;
			cout << setw(5) << setiosflags(ios::left)<< temp2->friend_user->v ;	//display friends
			temp2 = temp2->next;
		}
		temp = temp->down;
		cout << endl;
	}
}

int facebook :: findmin(){
	struct list *temp=top;
	struct edge *e;
	int min = temp->side->weight;
	while(temp!=NULL){					//traversing list
		e = temp->side;
		while(e!=NULL){					//traversing edges
			if(e->weight == min){
			if(e->visited == 1 || e->not_to_visit == 1){		//if the minimum is visited

				if(e->next != NULL){
					min = e->next->weight;
				}
				else{
					if(temp->down != NULL){
					min = temp->down->side->weight;
					}
				}
			}
			}
			if(e->weight < min && e->visited==0){		//finding minimun weight
				min = e->weight;

			}
			e = e->next;
		}
		temp = temp->down;
	}
	return min;
}

void facebook :: mark_visited(int m){
	struct list *temp=top,*temp2;
	struct edge *e,*e2;
	int check;
	while(temp!=NULL){					//traversing list
		e = temp->side;
		while(e!=NULL){					//traversing edges
			if(e->weight == m && e->visited==0){		//finding minimun weight
				check = bfs(temp->v ,e->friend_user->v);
				//here we will check weather vertex is already in spanning tree or not
				if(check==1){
				e->visited =1;
				temp2 = e->friend_user;
				e2 = temp2->side;
					while(e2->friend_user->v != temp->v){
						e2 = e2->next;
					}
				e2->visited = 1;
				}
				else{
					e->not_to_visit = 1;
				}
				e->visited =1;
			}
			e = e->next;
		}
		temp = temp->down;
	}
}

void facebook :: kruskal(){
	int m,sum=0;
	struct list *temp = top;
	struct edge *temp2;
	struct list *p=top;
	while(p!=NULL){					//find minimum and mark it as visited
		m = findmin();				//every time the loop runs
		mark_visited(m);
		p = p->down;
	}
	while(temp!=NULL){
			temp2 = temp->side;
			cout << temp->v  ;						//display vertex name
			while(temp2 != NULL){
				if(temp2->visited==1){
					if(temp2->not_to_visit == 0){
						if(temp2->added!=1){
							sum += temp2->weight;
						}
						cout << " -> (" << temp2->weight << ")" ;
						cout << setw(5) << setiosflags(ios::left)<< temp2->friend_user->v ;	//display friends
					}
				}
				temp2 = temp2->next;
			}
			temp = temp->down;
			cout << endl;
		}
	cout << "\nMinimun weight of given graph using kruskal's algo is : " << sum;
}

int facebook :: bfs(char a,char b){		//bfs traversal
	int c=0;
	unvisited_2();
	queue<list *> q;
	list * p = top;
	edge *e;

	while(p->v != a){
		p = p->down;		//search for first character
	}
	q.push(p);
	while(!q.empty()){
		p = q.front();
		q.pop();
		e = p->side;
		if(p->visit==0){
			p->visit = 1;
		}
		while(e != NULL){
			if(e->friend_user->visit == 0){
			if(e->visited == 1){
			 if(e->friend_user->v == b){
					c++;
					break;
				}
				q.push(e->friend_user);
			}
			}
			e = e->next;
		}
	}
	if(c==0){
		return 1;		//if it is  not already present
	}
	return 0;			//if  present
}

int main() {
	int ch,c=0;
	facebook f;
		do{
			cout << "\nENTER CHOICE :\n 1.Enter Vertex\n 2.Display\n 3.Kruskal's MST";
			cout << "\n 4.Exit\n";
			cin >> ch;
			switch(ch){
			case 1:
				f.getdata();
				c++;
				break;
			case 2:
				if(c==0){
					cout << "PLEASE ENTER DATA FIRST";
					break;
				}
				f.display();
				break;
			case 3:
				if(c==0){
					cout << "PLEASE ENTER DATA FIRST";
					break;
				}
				f.kruskal();
				break;
			case 4:
				break;
			default :
				cout << "PLEASE ENTER VALID CHOICE " << endl;
				break;
			}
		}
		while(ch!=8);
}
