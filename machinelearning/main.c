#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include "darray.h"

int main(){
	darray* a = darray_init();
	char buff[100];

	while(fgets(buff,100,stdin)){/*read a line*/
		char *p=buff;
		for(;;){/* Process Numbers */
			double temp = strtod(p,&p);

			if(isspace(*p)||*p==0){ /*Check if read succeeded*/
				darray_insert(a,temp);
				while(isspace(*p)){ /*Go to next number*/
					p++;
				}
				if(*p==0)break;
			}else{
				printf("Error converting to double\n");
				goto exit;			}
		}
	}

	if(ferror(stdin)){
		printf("Error reading\n");
		goto exit;
	}

	for(int i=0;i<darray_size(a);i++){
		printf("%f\n",darray_get(a,i));
	}

exit:
	darray_destroy(a);
	return 0;
}