#include <iostream>
#include "cintarray.h"

int main(){
	CIntArray nums;
	int in;
	while(std::cin >> in){
		nums.push(in);
	}
	for(int i=0;i<nums.size();i++){
		printf("%d\n",nums[i]);
	}
}