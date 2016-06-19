#include <stdio.h>
#include <errno.h>
#include "gradientdescent.h"
#include "darray.h"

int main(){
	int numOfCols=1;
	int numOfRows=0;
	GD_Model gd_model;
	double *features=0;
	darray* a = darray_init();
	char buff[1024];

	//open file
	FILE *fp = fopen("testdata.csv", "r");
	if(!fp){
		printf("Error opening file.");
		goto exit;
	};

	//Get number of columns
	if(!fgets(buff,1024,fp))goto exit;
	for(char*c=buff; *c!=0;c++){
		if(*c==',')numOfCols++;
	}

	do{/*read a line*/
		char *p=buff;
		for(;;){/* Process Numbers */
			double temp = strtod(p,&p);

			if(*p==','){ /*Check if read succeeded*/
				darray_insert(a,temp);
				p++;//skip the comma
			}else if(*p=='\n'||*p==0){
				darray_insert(a,temp);
				break;//read next line
			}else{
				printf("Error converting to double\n");
				goto exit;			
			}
		}
		numOfRows++;
	}while(fgets(buff,1024,fp));

	if(ferror(fp)){
		printf("Error reading\n");
		goto exit;
	}
	//check number of entries is correct
	if(numOfRows*numOfCols!=darray_size(a)){
		printf("Error: number of data entries is not number of rows x number of columns.");
		goto exit;
	}

	//allocate space for weights
	if(!gd_init(&gd_model,darray_get_addr(a,0),numOfRows,numOfCols,0.001)){
		printf("Error allocating memory for gradient descent model");
	}
	features = malloc(sizeof(double)*(numOfCols-1));


	//use the model to predict from stdin
	while(fgets(buff,1024,stdin)){
		char *p=buff;
		for(int i=0;i<numOfCols-1;i++){/* Process Numbers */
			double temp = strtod(p,&p);
			if(*p==','){ /*Check if read succeeded*/
				features[i]=temp;
				p++;//skip the comma
			}else if(*p=='\n'){
				features[i]=temp;
				break;//read next line
			}else{
				printf("Error converting to double\n");
				goto exit;			
			}
		}
		printf("%f\n",gd_predict(&gd_model,features));
	}

	if(ferror(stdin)){
		printf("Error reading from stdin.");
		goto exit;
	}

exit:
	free(features);
	gd_cleanup(&gd_model);
	darray_destroy(a);
	if(fp)fclose(fp);	
	return 0;
}