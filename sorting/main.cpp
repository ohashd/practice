#include <iostream>
#include <cstdlib>
#include <utility>
#include "darray.h"

//dupe qsort
void dqsort(int*left, int*right){
	if(left>=right)return;
	int* pivot = left + std::rand() % (1+right-left);
	std::swap(*pivot,*left);
	int *i=left+1;
	int *lt=left;
	int *gt=right;
	while(i<=gt){
		if(*i==*lt){
			i++;
		}else if(*i<*lt){
			std::swap(*lt,*i);
			i++;
			lt++;
		}else if(*i>*lt){
			std::swap(*gt,*i);
			gt--;
		}
	}
	dqsort(left,lt-1);
	dqsort(gt+1,right);
}
//nondupe qsort
void qsort(int*left, int*right){
	if(left>=right)return;
	int* pivot = left + std::rand() % (1+right-left);
	std::swap(*pivot,*right);
	int *i=left;
	int *j=right-1;
	while(i<=j){
		if(*i <= *right){
			i++;
		}else if(*j > *right){
			j--;
		}else{
			std::swap(*j,*i);
			j--;
			i++;
		}
	}
	if(i==right){
		qsort(left,i-1);
		return;
	}
	std::swap(*right,*i);
	qsort(left,i-1);
	qsort(i+1,right);
}

void sort(DArray<int>& arr){
	if(arr.size()>0)
	dqsort(&arr[0],&arr[arr.size()-1]);
	//qsort(&arr[0],&arr[arr.size()-1]);
}

int main(){
	DArray<int> nums;
	int in;
	while(std::cin >> in){
		nums.push(in);
	}
	sort(nums);
	for(int i=0;i<nums.size();i++){
		printf("%d\n",nums[i]);
	}
}