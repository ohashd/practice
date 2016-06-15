#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>
#include "darray.h"

//Assumes `weights` is big enough for `cols` doubles
//Assumes data is a contiguous 2d array (1d array with size rows*cols)
//Assumes last column is the dependent
void gradientDescent(double*weights,double*data,int rows,int cols,double eps){
	double learningrate=0.01;
	double*gradients = malloc((cols)*sizeof(double));
	double*errors = malloc(rows*sizeof(double));
	double lastError=INFINITY;//set to infinity
	//zero the weights
	for(int c=0;c<(cols);c++){
		weights[c]=0;
	}
	//cap out at 1,000,000 iterations
	for(int i=0;i<1000000;i++){
		double totalError=0;

		//iterate through the rows and features to calculate gradients
		for(int r=0;r<rows;r++){
			//calculate what the model would predict in this row
			errors[r]=weights[cols-1];
			for(int c=0;c<(cols-1);c++){
				errors[r]+=weights[c]*data[r*cols+c];
			}
			//convert to error
 			errors[r]-=data[(r+1)*cols-1];
 			//add to totalErr
 			totalError+=errors[r]*errors[r];
 		}
		//break if error is below a threshold
		if(totalError/rows<eps)break;

 		//if we overshot, lessen the learning rate and recalulate new weights for next iteration attempt
 		if(lastError<totalError){
 			learningrate/=2;
			for(int c=0;c<cols;c++){
				weights[c]+=gradients[c]*2*learningrate/rows;
			}		
 			continue;
 		}

		learningrate*=1.05;

 		lastError=totalError;

		//rezero gradients
		for(int c=0;c<(cols);c++){
			gradients[c]=0;
		}

		for(int r=0;r<rows;r++){
			//calculate the gradient for the constant feature weight
			gradients[cols-1]+=errors[r];

			//calculate the gradients for the other features
			for(int c=0;c<(cols-1);c++){
				gradients[c]+=errors[r]*data[r*cols+c];
			}
		}

		//transfer gradients into weights by a learning factor
		for(int c=0;c<cols;c++){
			weights[c]-=gradients[c]*2*learningrate/rows;
		}		
	}
	free(errors);
	free(gradients);
}

int main(){
	int numOfCols=1;
	int numOfRows=0;
	double *weights=0;
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
	weights = malloc(numOfCols*sizeof(double));
	features = malloc(sizeof(double)*(numOfCols));

	gradientDescent(weights,darray_get_addr(a,0),numOfRows,numOfCols,0.01);

	for(int i=0;i<numOfCols;i++){
		printf("%f\n",weights[i]);
	}

	//use the model to predict from stdin
	while(fgets(buff,1024,stdin)){
		double prediction=weights[numOfCols-1];
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
		//Predict with learned weights!
		for(int i=0;i<numOfCols-1;i++){
			prediction+=(features[i]*weights[i]);
		}
		printf("%f\n",prediction);
	}

	if(ferror(stdin)){
		printf("Error reading from stdin.");
		goto exit;
	}

exit:
	free(features);
	free(weights);
	darray_destroy(a);
	if(fp)fclose(fp);	
	return 0;
}