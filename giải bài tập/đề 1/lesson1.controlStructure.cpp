/*Lesson 1. Control structure:
1.1 Write a program to input two numbers a and b, enter one of the following 
operations: +, -,*, /. ^. Print on the screen the result of the expression a pt b. 
For example: a=5, b=2, pt=^ then the screen displays 5 ^ 2 = 25.
1.2 Modify the above program so that the user can perform many operations 
until he wants to end by pressing the escape key (ESC, n…).    */

#include <stdio.h>
#include <math.h>
#include <conio.h>

void enterAnyKey(){
	printf("\nEnter any key to continue!");
	getch();
}

int main(){
	int a;
	int b;
	char operation;
	printf("\nEnter 2 integer a,b: ");
	scanf("%d%d",&a,&b);
	getchar();
	while(1){
		printf("\nPress ESC to exit");
		printf("\nEnter one of the operations(+,-,*,/,^): \n");
		operation=_getch(); //Get a character without pressing Enter
	
		//exit:ESC=27
		if(operation == 27){
			printf("\nExiting the program!");
			break;
		}
		
		switch(operation){
		case '+':
			printf("\n%d + %d = %d",a,b,a+b);
			enterAnyKey();
			break;
	
		case '-':
			printf("\n%d - %d = %d",a,b,a-b);
			enterAnyKey();
			break;
		
		case '*':
			printf("\n%d * %d = %d",a,b,a*b);
			enterAnyKey();
			break;
		
		case '/':
			if(b==0){
				printf("\nError!");
				enterAnyKey();
				break;
			}else{
				printf("\n%d / %d = %.2f",a,b,(float)a/b);
				enterAnyKey();
				break;
			}
		
		case '^':
			printf("\n%d ^ %d = %d",a,b,(int)pow(a,b));		
			enterAnyKey();
			break;
	
		default:
	        printf("\nInvalid operation! Please enter +, -, *, /, ^.");
	        enterAnyKey();
		}
	}
}
