#include <iostream>
#include "darray.h"

int main(){
	DArray<int> nums;
	int in;
	while(std::cin >> in){
		nums.push(in);
	}
	for(int i=0;i<nums.size();i++){
		printf("%d\n",nums[i]);
	}
}