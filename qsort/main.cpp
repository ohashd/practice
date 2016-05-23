#include <iostream>
#include "darray.h"

void qsort(DArray<int>& arr){
	
}

int main(){
	DArray<int> nums;
	int in;
	while(std::cin >> in){
		nums.push(in);
	}
	qsort(nums);
	for(int i=0;i<nums.size();i++){
		printf("%d\n",nums[i]);
	}
}