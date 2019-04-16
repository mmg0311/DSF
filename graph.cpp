#include<bits/stdc++.h>
#define inf 1000
using namespace std;
typedef pair<int ,struct vertex *> ipair;
struct vertex{
	int corres;
	char v;				//name of vertex
	int visited;		//whether vertex is visited or not
	struct vertex *down;
	struct edge *side;
};

struct edge{
	struct vertex *a;		//to store info of friend
	int w;		//weight
	int visit;	//whether edge is visited or not
	int not_to_visit;
	int added;
	struct edge *next;		
};

class graph{
	struct vertex *top;
	int count;
	
public:
	graph(){
		top = NULL;
		count = 0;
	}
	void getdata();
	void display();
	void dfs();
	void bfs();
	void display_adjacency();
	int makefriend(int ,struct vertex *);
	void unvisited();
	int findmin();
	void kruskals();
	void mark_visited(int );
	int bfs1(char ,char );
	void dijkastras();
	void prims();
};

void graph :: unvisited(){
	struct vertex *t= top;
	while(t!=NULL){
		t->visited = 0;
		t = t->down;
	}
}

void graph:: display(){
	struct vertex *t =top;
	struct edge *e ;
	while(t != NULL){
		cout << t->v ;
		e = t->side;
		while(e!= NULL){
			cout << " -> " <<e->a->v << "(" << e->w << ")";
			e = e->next;
		}
		t = t->down;
		cout << endl;
	}
}

void graph :: display_adjacency(){
	struct vertex *t;
	int i=1;
	t = top;
	while(t->down != NULL){
		cout << i << " . " << t->v << endl;
		i++;
		t = t->down;
	}
}

int graph :: makefriend(int x,struct vertex *v){
	struct vertex *t = top;
	struct edge *e,*s,*e2;
	while(x != 1){
		t = t->down;
		x--;
	}
	if(t == NULL){
		cout << "cannot be friends\n" ;
		return -1;
	}
	e = new (struct edge);
	cout << "Enter weight of edge :" << t->v << v->v << " : " ;
	cin >> e->w;
	e->a = v;
	e->visit = 0;
	e->added = 0;
	e->next = NULL;
	s = t->side;
	if(s!= NULL){
		while(s->next != NULL){
			if(s->a->v == v->v){
				delete e;
				return 1;
			}
			s = s->next;
		}
		if(s->a->v == v->v){
			delete e;
			return 1;
		}
		s->next = e;
	}
	else{
		t->side = e;
	}
	s = v->side;
	e2 = new (struct edge);
	e2->a = t;
	e2->visit = 0;
	e->added = 1;
	e2->w = e->w;
	e2->next = NULL;
	if(s == NULL){
		v->side = e2;
	}
	else{
		while(s->next != NULL){
			s = s->next;
		}
		s->next = e2;
	}
	return 0;
}

void graph::getdata(){
	count++;
	int ch,c;
	struct vertex *p,*t;
	p = new (struct vertex);
	t = top;
	cout << "enter name of vertex : ";
	cin >> p->v;
	p->corres = count;
	p->visited = 0;
	p->side = NULL;
	p->down = NULL;
	if(t == NULL){
		top = p;
		return;
	}
	while(t->down!=NULL){
		t = t->down;
	}
	t->down = p;

	if(count != 1){

		display_adjacency();
		cout << "-1 to exit\n";
		while(1){
			cout << "enter ur choice : ";
			cin >> ch;
			if(ch == -1){
				break;
			}
			else if(ch >= count){
				cout << "enter valid choice\n";
			}
			else{
				c = makefriend(ch,p);
				if(c==0){
					cout << "Friend request sent\n";
				}
				else{
					cout << "both are already friends\n";
				}
			}
		}
	}

}

void graph :: dfs(){
	stack<struct vertex *>s;
	struct vertex *temp = top;
	struct edge * e;
	s.push(temp);
	unvisited();
	while(!s.empty()){
		temp = s.top();
		e = temp->side;
		s.pop();
		if(temp->visited == 0){
			temp->visited =1;
			cout << temp->v << " ";
		}	
		
		while(e!= NULL){
			if(e->a->visited==0){
				s.push(e->a);
			}
			e = e->next;
		}
	}
}

void graph :: bfs(){
	queue<struct vertex *> q;
	struct vertex *t =top;
	struct edge *e;
	unvisited();
	q.push(t);
	while(!q.empty()){
		t = q.front();
		q.pop();
		e = t->side;
		if(t->visited == 0){
			t->visited =1;
			cout << t->v << " ";
		}
		while(e!= NULL){
			if(e->a->visited == 0){
				q.push(e->a);
			}
			e = e->next;
		}
	}
}

int graph :: findmin(){
	struct vertex *p =top;
	int min = 1000;
	struct edge *e,*ans;
	while(p!= NULL){
		e = p->side;
		while(e != NULL){
			if(min == e->w){
				if(e->visit == 1 || e->not_to_visit==1){
					if(e->next != NULL){
						min = e->next->w;
					}
					else{
						if(p->down != NULL){
							min = p->down->side->w;
						}
					}
				}
			}
			
			if(e->w < min){
				if(e->visit !=1){
					min = e->w;
				}
			}
			

			e= e->next;
		}
		p = p->down;
	}
	return min;
}

void graph :: mark_visited(int min){
 struct vertex *temp= top,*temp2;
 struct edge *e;
 int check;
 while(temp != NULL){
 	e = temp->side;
 	while(e!= NULL){
 		 if(e->w==min && e->visit == 0){
 			check = bfs1(temp->v,e->a->v);
 			if(check == 1){
 				e->visit = 1;
 				temp2 = e->a;
 				e = temp2->side;
 				while(e->a->v != temp->v){
 						e = e->next;
 				}
 			e->visit =1;
 		}
 		else{
 			e->not_to_visit =1;
 		}
 		e->visit =1;
 	}
 	e = e->next;
 	}

 	temp= temp->down;
 }


}

int graph::bfs1(char a,char b){
	struct vertex *temp;
	struct edge *e;
	int c=0;
	temp = top;
	while(temp != NULL){
		if(temp->v == a){
			break;
		}
		temp = temp->down;
	}
	stack<struct vertex *> s;
	s.push(temp);
	unvisited();
	while(!s.empty()){
		temp = s.top();
		s.pop();
		if(temp->visited == 0){
			temp->visited =1;
		}
		e = temp->side;
		while(e != NULL){
			if(e->a->visited == 0){
				if(e->visit == 1){
					if(e->a->v == b){
						c++;
						break;
					}
					s.push(e->a);
				}
			}
			e = e->next;
		}
	}
	if(c==0){
		return 1;
	}
	return 0;
}

void graph :: kruskals(){
	struct vertex *p =top;
	struct edge *q;
	int min,sum=0;
	while(p!=NULL){
		min = findmin();		//find minimum weight edge
		mark_visited(min);	//mark that edge as visited
		p = p->down;
	}
	cout << endl;
	p = top;
	while(p!= NULL){
		cout << p->v;
		q = p->side;
		while(q != NULL){
			if(q->visit == 1){
				if(q->not_to_visit != 1){
						if(q->added == 0){
							sum = sum + q->w;
						}
					
					cout << " -> " << q->a->v << "(" << q->w << ")";
				}
			}
			q = q->next;
		}
		cout << endl;
		p = p->down;
	}
	cout << sum ;
}

void graph:: dijkastras(){
	priority_queue<ipair,vector<ipair>,greater<ipair>> pq;	
	//will make a min heap
	struct vertex *t;
	int i,j;
	struct edge *e;
	vector<int> dist(count,inf);
	pq.push(make_pair(0,top));
	dist[0] = 0;
	while(!pq.empty()){
		t = pq.top().second;
		pq.pop();
		j = t->corres;
		j = j-1;
		e = t->side;
		while(e!=NULL){
				i = e->a->corres;
				i--;
				if(dist[i] > dist[j] + e->w){
					dist[i] = dist[j] + e->w;
					pq.push(make_pair(dist[i],e->a));

				}
				e = e->next;
		}
	}
	t = top;
	i =0;
	while(t != NULL){
		cout << t->v << "\t" << dist[i] << endl;
		i++;
		t = t->down;
	}
}

void graph :: prims(){
		priority_queue<ipair,vector<ipair>,greater<ipair>> pq;	
	//will make a min heap
	struct vertex *t;
	int i,j;
	struct edge *e;
	unvisited();
	vector<char> parent(count,'z');
	vector<int> dist(count,inf);
	pq.push(make_pair(0,top));
	dist[0] = 0;
	while(!pq.empty()){
		t = pq.top().second;
		pq.pop();
		t->visited = 1;
		e = t->side;
		while(e!=NULL){
				i = e->a->corres;
				i--;
				if(e->a->visited==0 && dist[i] > e->w){
					dist[i] = e->w;
					pq.push(make_pair(dist[i],e->a));
					parent[i] = t->v;
				}
				e = e->next;
		}
	}
	t = top;
	while(t!=NULL){
		cout << t->v ;
		e = t->side;
		while(e != NULL){
			if(parent[e->a->corres-1] == t->v){
				cout << " -> " << e->a->v << "(" << e->w << ")" ;
			}
			e = e->next;
		}
		cout << endl;
		t = t->down;
	}
	
}

int main(){
	int choice;
	graph g;
	do{
		cout << "\nEnter choice\n\t1.Enter data\n\t2.display graph\n\t3.kruskals\n\t4.prims\n\t5.dijkastras\n\t";
		cout << "6.exit\n\t";
		cin >> choice;
		switch(choice){
			case 1:
				g.getdata();
				break;
			case 2:
				g.display();
				break;
			case 3:
				g.kruskals();
				break;
			case 4:
				g.prims();
				break;
			case 5:
				g.dijkastras();
				break;
			case 6:
				break;
		}
	}
	while(choice!=6);
}