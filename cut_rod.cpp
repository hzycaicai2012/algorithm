/*************************************************************************
	> File Name: cut_rod.cpp
	> Author: hzycaicai
	> Mail: hzycaicai4@163.com 
	> Created Time: Thu 30 May 2013 09:22:05 AM CST
	>
	> This is a program for rod cut to get the max profit using NP
	> Length of rod is n and profit is in array p
 ************************************************************************/

#include <iostream>
#include <cstdio>

#define MIN -1

int n;
int p[100];
int memo[100];
int path[100];


int memo_init(int p[],int n);
int cut_rod(int p[],int n,int memo[]);
void bottom_cut_rod(int p[], int n);
void print_cut(int p[], int n);
void print_bottom_cut(int p[], int n);
int max(int a, int b);

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	print_cut(p,n);
	for(int i=0;i<=n;i++)
	  memo[i] = MIN;
	print_bottom_cut(p,n);
	printf("%d\n",memo[n]);
	return 0;
}

int memo_init(int p[], int j){
	for(int i=0;i<=j;i++){
	  memo[i] = MIN;
	}
	return cut_rod(p,j,memo);
}

int cut_rod(int p[], int j, int memo[]){
	int q;
	if(memo[j]>=0)
		return memo[j];
	if(j==0)
		q = 0;
	else{
	  q = MIN;
	  for(int i=1;i<=j;i++){
		if(q<p[i]+cut_rod(p,j-i,memo)){
			q = (p[i]+cut_rod(p,j-i,memo));
			path[j] = i;
		}
	  }
	}
	memo[j] = q;
	return q;
}

void bottom_cut_rod(int p[], int n){
	memo[0] = 0;
	path[0] = -1;
	int max = MIN;
	int rod_end[2];
	for(int j=1;j<=n;j++){
		int q = MIN;
		for(int i=1;i<=j;i++)
		  if(q<(p[i]+memo[j-i])){
			q = p[i]+memo[j-i];
			path[j] = i;
		  }
		memo[j] = q;
	}
}

void print_bottom_cut(int p[],int n){
	bottom_cut_rod(p,n);
	while(n>0){
	  printf("%d ",path[n]);
	  n -= path[n];
	}
}

void print_cut(int p[],int n){
	int profit = memo_init(p,n);
	while(n>0){
	  printf("%d ",path[n]);
	  n -= path[n];
	}
	printf("%d\n",profit);
}

int max(int a, int b){
	return (a>b) ? a:b;
}
