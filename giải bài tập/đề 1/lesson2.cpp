/*Lesson 2. Write a program to input a series of integers and perform the following:
- Calculate the sum of the series
- Calculate the average of the series
- Find the largest value of the series
- Find the smallest value of the series
- Count the number of even elements of the series that are less than x 
(x is entered from the keyboard)*/

#include <stdio.h>
int a[100];
int n;

void input(int x[100],int &n){
	do{
		printf("\nEnter the number of elements:");
		scanf("%d",&n);
	}while(n<1 || n>100);
	for(int i=0;i<n;i++){
		printf("\na[%d]=",i);
		scanf("%d",&x[i]);
	}
}

void output(int x[100],int n){
	printf("\nArray: ");
	for(int i=0;i<n;i++){
		printf(" %d",x[i]);
	}
}

int sum(int x[100],int n){
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=x[i];
	}
	return sum;
}

float average(int x[100],int n){
	int count=0;
	for(int i=0;i<n;i++){
		count++;
	}
	return (float)sum(x,n)/count;
}

void findMax(int x[100],int n){
	int max=x[0];
	for(int i=0;i<n;i++){
		if(x[i]>max){
			max=x[i];
		}
	}
	printf("\nThe largest value is: %d",max);
}

void findMin(int x[100],int n){
	int min=x[0];
	for(int i=0;i<n;i++){
		if(x[i]<min){
			min=x[i];
		}
	}
	printf("\nThe smallest value is: %d",min);
}

void elementLessThanX(int a[100],int n){
	int x;
	printf("\nEnter X: ");
	scanf("%d",&x);
	
	int count=0;
	for(int i=0;i<n;i++){
		if(a[i]<x && a[i]%2==0){
			count++;
		}
	}
	printf("\nNumber of elements less than x: %d",count);
}

int main(){
	input(a,n);
	output(a,n);
	printf("\nSUM=%d",sum(a,n));
	printf("\nAVERAGE=%.2f",average(a,n));
	findMax(a,n);
	findMin(a,n);
	elementLessThanX(a,n);
}
