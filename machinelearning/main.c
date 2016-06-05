#include <stdio.h>
#include "darray.h"

int main(){
	darray* a = darray_init();
	int in;
	while(EOF != scanf("%d",&in)){
		darray_insert(a,in);
	}

	for(int i=0;i<darray_size(a);i++){
		printf("%d\n",darray_get(a,i));
	}
	darray_destroy(a);
}