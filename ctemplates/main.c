#include <stdio.h>
#include "arrayint.h"

int main(){
	array_int* a = new_array_int();

	char buffer[100];
	while(fgets(buffer,100,stdin)){
		array_int_insert(a,atoi(buffer));
	}

	array_int_set(a,0,1111);

	for(int i=0;i<array_int_size(a);i++){
		printf("%d\n",array_int_get(a,i));
	}

	delete_array_int(a);
	return 0;
}