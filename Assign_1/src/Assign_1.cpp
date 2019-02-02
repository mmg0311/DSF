//============================================================================
// Name        : Assign_1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include"stackll.h"
#include<stdlib.h>
#include<string.h>
#include<iomanip>
using namespace std;

class Expression{
private:
	char prefix[30],postfix[30];
public:
	Expression(){

		prefix[0]='\0';
		postfix[0] = '\0';
	}
	void infix_to_prefix(char []);
	void infix_to_postfix(char []);
	void infix_to_postfix2(char []);
	int precedence(char );
	int associativity(char );
	float eval(char ,int ,int);
	float eval_postfix();
	float eval_prefix();
	int isoperator(int);
	int power(int ,int);
};

//TO DETERMINE IF IT IS AN OPERATOR

int Expression :: isoperator(int x){
	if(x==(int)'+' ||x== (int)'-' ||x== (int)'/' ||x== (int)'%' ||x== (int)'*'||x==(int)'^'){
		//typecast operator used because ascii value of character will be  passed in x
		return 0;
	}
	else{
		return 1;
	}
}

//TO DETERMIN PRECEDENCE

int Expression :: precedence(char x){
	if(x=='^')
		return 3;
	else if(x=='*' || x=='/')
		return 2;
	else if(x=='-' || x=='+')
		return 1;
	else if(x=='(')
		return 0;
	else
		return -1;
}

//TO DETERMINE ASSOCIATIVITY

int Expression :: associativity(char x){
	if(x=='^' || x=='=')				//right associativity
		return 1;
	else
		return 0;						//left associativity
}

//INFIX TO POSTFIX CONVERSION

void Expression :: infix_to_postfix(char equation[30]){
	stack_ll S;									//object of stack will be used in this function
	cout << "INFIX FORM :  " << equation << endl;
	int i,j=0,l= strlen(equation),k=0;
	char token,x,op[l];

	cout << "======================================================================" << endl;
	cout << "TOKEN" << setw(20) <<"STACK" << setw(20) << "OUTPUT" << endl;
	cout << "======================================================================" << endl;
	for(i=0;i<l;i++){
		token = equation[i];
		cout <<setw(20)<< setiosflags(ios::left)<< token ;
		if(i==0){
			cout <<setw(20)<< setiosflags(ios::left) <<"empty";
		}

		if(token=='('){
			S.push(token);
			op[k++] = token;
		}

		else if(token == ')'){
		    while((x=S.gettop())!='('){
						x = S.pop();
					    postfix[j] = x;
					    j++;
					    k--;
		    }
		  S.pop();
		  k--;
		}
		else if(isoperator(token)==0){
			while(S.isEmpty()==1&&precedence(token)<=precedence(x= S.gettop())){
				if(associativity(token)==1 && associativity(x)==1){
					break;
				  }
				else{
				x = S.pop();
				k--;
				postfix[j++] = x;
				}
			}
			S.push(token);
			op[k++] = token;
		}
		else {
			postfix[j] = token;
			j++;
		}
		postfix[j]='\0';
		cout << setw(20)<< setiosflags(ios::left);
		for(int a=0;a<k;a++){
			cout << op[a];
		}
		cout  << setw(20) << setiosflags(ios::left)<<  postfix << endl;
	}
	while(S.isEmpty()!=0){
		postfix[j++] = S.pop();
	}

	postfix[j] = '\0' ;
	cout << "======================================================================" << endl;
	cout  << "POSTFIX OF GIVEN EXPRESSION IS : " <<  postfix << endl;
	cout << "======================================================================" << endl;
}

//function similar to postfix function because of less than condition

void Expression :: infix_to_postfix2(char equation[]){
	stack_ll S;									//object of stack will be used in this function
	cout << "INFIX FORM :  " << equation << endl;
	int i,j=0,l= strlen(equation),k=0;
	char token,x,op[l];

	cout << "======================================================================" << endl;
	cout << "TOKEN" << setw(20) <<"STACK" << setw(20) << "OUTPUT" << endl;
	cout << "======================================================================" << endl;
	for(i=0;i<l;i++){
		token = equation[i];
		cout <<setw(20)<< setiosflags(ios::left)<< token ;
		if(i==0){
			cout <<setw(20)<< setiosflags(ios::left) <<"empty";
		}

		if(token=='('){
			S.push(token);
			op[k++] = token;
		}

		else if(token == ')'){
		    while((x=S.gettop())!='('){
						x = S.pop();
					    postfix[j] = x;
					    j++;
					    k--;
		    }
		  S.pop();
		  k--;
		}
		else if(isoperator(token)==0){
			while(S.isEmpty()==1&&precedence(token)<=precedence(x= S.gettop())){
				if(associativity(token)==1 && associativity(x)==1){
					break;
				  }
				else{
				x = S.pop();
				k--;
				postfix[j++] = x;
				}
			}
			S.push(token);
			op[k++] = token;
		}
		else {
			postfix[j] = token;
			j++;
		}
		postfix[j]='\0';
		cout << setw(20)<< setiosflags(ios::left);
		for(int a=0;a<k;a++){
			cout << op[a];
		}
		cout  << setw(20) << setiosflags(ios::left)<<  postfix << endl;
	}
	while(S.isEmpty()!=0){
		postfix[j++] = S.pop();
	}

	postfix[j] = '\0' ;
	cout << "======================================================================" << endl;
	cout  << "POSTFIX OF GIVEN EXPRESSION IS : "<<postfix << endl;
}

//INFIX TO PREFIX CONVERSION

void Expression :: infix_to_prefix(char equation[30]){
	int l = strlen(equation),i,j=0;
	char temp[30];
	stack_ll S;
    cout << "EXPRESSION IS : " << equation << endl;
	for(i=l-1;i>=0;i--){
		temp[j] = equation[i];
		j++;
	}
	temp[j]='\0';
	cout << "AFTER INVERSION :  " << temp << endl;
	//now replacing the opening and closing brackets with each other
	for(i=0;i<l;i++){
		if(temp[i]=='('){
			temp[i]=')';
		}
		else if(temp[i]==')'){
			temp[i]='(';
		}
		else{

		}
	}
	cout << "AFTER REPLACING BRACKETS WE GET :  " << temp << endl;
	infix_to_postfix2(temp);
	j=0;
	for(i=strlen(postfix)-1;i>=0;i--){
		prefix[j] = postfix[i];
		j++;
	}
	prefix[j] = '\0';
	cout << "======================================================================" << endl;
	cout << "PREFIX OF GIVEN EXPRESSION IS :  " << prefix << endl;
	cout << "======================================================================" << endl;

}

//power function

int Expression :: power(int a,int b){
	int c=1;
	for(int i=0;i<b;i++){
		c *= a;
	}
	return c;
}

//EVALUATION FUNCTION USED FOR EVERY OPERATOR APPEARED

float Expression :: eval(char x,int op1,int op2){
	float result=0;
	switch(x){
	case '+':
		result = op1+op2;
		break;
	case '-':
		result  = op1 -op2;
		break;
	case '*':
		result = op1*op2;
		break;
	case '/':
		result = op1/op2;
		break;
	case '%':
		result = op1%op2;
		break;
	case '^':
		result = power(op1,op2);
		break;

	}
	return result;
}

//EVALUATION OF POSTFIX FUNCTION

float Expression :: eval_postfix(){
	stack_ll s;
	float ans=0;
	int i,op1,op2;
	char x;

	for(i=0;postfix[i]!='\0';i++){
		x = postfix[i];
		//if character is variable ask for value to put
		if(isalpha(x)){
			cout << "ENTER VALUE OF " << x << endl;
			cin >> x;
			s.push(x);
		}

		else if(isoperator(x)==0){
			op2 = s.pop() - 48;
			op1 = s.pop() - 48;
			ans = eval(x,op1,op2);
			s.push(ans+48);
		}
		else{//is a numeric value
			s.push(x);
		}

	}
	ans = s.pop() - 48;
	return ans;
}

//EVALUATION OF PREFIX EQUATION

float Expression :: eval_prefix(){
	stack_ll s;
	float ans=0;
	int i,op1,op2;
	char x;
	//start from the end of string because its prefix
	for(i=strlen(prefix)-1;i>=0;i--){
		x = prefix[i];
		if(isalpha(x)){
			cout << "ENTER VALUE OF " << x << endl;
			cin >> x;
			s.push(x);
		}
		else if(isoperator(x)==0){
			op1 = s.pop() - 48;//-48 because my stack is of characters
			op2 = s.pop() - 48;
			ans = eval(x,op1,op2);
			//pushing result on stack
			s.push(ans+48);
		}
		else{//is a numeric value
			s.push(x);
		}

	}
	ans = s.pop() - 48;//character stack
	return ans;
}

int input(char temp[])//for taking infix expression input
{
	char x;
	int i=0,count1=0,count2=0,count3=0;
	while(temp[i]!='\0')
	{
		x=temp[i];
		if(x=='(')
		{
			count1++;
		}
		else if(x==')')
		{
			count1--;
		}
		else if(isalpha(x))
		{
			count2++;
		}
		else
		{
			count3++;
		}
		if(i!=0)
		{
			if(isalpha(x) && isalpha(temp[i-1]))	//NO CONSECUTIVE OPERANDS VALIDATION
			{
				cout<<"\nTWO OPERANDS CANNOT BE CONSECUTIVE.PLEASE ENTER A VALID EXPRESSION:- ";
				return 1;
			}
			else if((x== '+' || x=='-' || x== '*' || x== '/' || x=='%' || x=='^') && (temp[i-1]== '+' || temp[i-1]=='-' || temp[i-1]=='*' || temp[i-1]=='/' || temp[i-1]=='%' || temp[i-1]=='^') )
			{
				cout<<"\nTWO OPERATORS CANNOT BE CONSECUTIVE.PLEASE ENTER A VALID EXPRESSION:-";	//CONSECUTICE OPERATOR VALIDATION
				return 1;
			}
			else if((isalpha(temp[i-1]) && x=='(') || (isalpha(x) && temp[i-1]==')'))	//OPERAND CANNOT BE GIVEN BEFORE OR AFTER A BRACE
			{
				cout<<"\nOPERAND CANNOT BE GIVEN BEFORE OR AFTER A BRACE.PLEASE ENTER A VALID EXPRESSION:-";
				return 1;
			}
		}
		i++;
	}
	if(count1==0)	//to check opening braces = closing braces
	{
		if(count3==(count2-1))	//BINARY EXPRESSION VALIDATION- (OPERATOR=OPERAND-1)
		{
			return 0;
		}
		else
		{
			cout<<"OPERATOR AND OPERATOR RELATION(OPERATOR=OPERAND-1) IS  NOT MATCHING.PLEASE ENTER A VALID EXPRESSION:-";
			return 1;
		}
	}
	else
	{
		cout<<"\nOPENING AND CLOSING BRACES ARE NOT MATCHING.PLEASE ENTER A VALID EXPRESSION:-";
		return 1;
	}
}

int main() {
	int ch,ch2;
	char equation[30];//to store the given equation
	Expression e;
	float ans1,ans2,c=0;
		do{
			cout << "\nMENU :\n 1.ENTER EXPRESSION \n 2.INFIX TO PREFIX \n 3.INFIX TO POSTFIX \n 4.EXIT\n" << endl;
			cin >> ch;
			switch(ch){
			case 1:
				    cout << "ENTER AN EXPRESSION" << endl;
					cin >> equation;
					if(input(equation)==0){
					c++;
					}
		             break;

			case 2:
				if(c!=0){
					e.infix_to_prefix(equation);
					do{
					     cout << "ENTER CHOICE \n1.EVALUATE PREFIX \n2.EXIT" << endl;
					     cin >> ch2;
					     switch(ch2){
					     	 	 case 1 :
					     	 		 	 ans1 = e.eval_prefix();
					     	 		 	 cout << "======================================================================" << endl;
					     	 		 	 cout << "EVALUATION OF PREFIX FORM OF EXPRESSION IS : " <<ans1 << endl;
					     	 		 	 cout << "======================================================================" << endl;
					     	 		 	 break;
					     	 	 case 2:
					     	 		 	 break;
					     }
					}
					while(ch2!=2);

				}
				else{
					cout << "PLEASE ENTER THE EXPRESSION FIRST" << endl;
				}
				     break;

			case 3:
				if(c!=0){
					e.infix_to_postfix(equation);

					do{
							cout << "ENTER CHOICE \n1.EVALUATE POSTFIX \n2.EXIT" << endl;
							cin >> ch2;
							switch(ch2){
									case 1 :ans2 = e.eval_postfix();
											cout << "======================================================================" << endl;
											cout << "EVALUATION OF POSTFIX FORM OF EXPRESSION IS : " <<ans2 << endl;
											cout << "======================================================================" << endl;
											break;
									case 2:
											break;
							}
					}while(ch2!=2);

				}
				else{
					cout << "PLEASE ENTER THE EXPRESSION FIRST" << endl;
				}
				     break;
			case 4:
				     cout << "EXIT" ;
				     break;

			default:
				     cout << "ENTER PROPER CHOICE " << endl;
			}
		}
		while(ch!=4);
	return 0;
}
