#include "gradientdescent.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GD_Model* gd_create(long numOfFeatures){
	GD_Model* ret = malloc(sizeof(GD_Model));
	if(!ret) return NULL;

	ret->weights = malloc(sizeof(double)*(numOfFeatures+1));
	if(!ret->weights){
		free(ret);
		return NULL;
	}

	ret->numOfFeatures = numOfFeatures;
	return ret;
}

void gd_destroy(GD_Model* model){
	if(!model)return;
	free(model->weights);
	free(model);
}

double gd_predict(GD_Model* model, double* features){
	double ret = model->weights[model->numOfFeatures];
	for(int c=0;c<model->numOfFeatures;c++){
		ret+=model->weights[c]*features[c];
	}
	return ret;
}

//Assumes data is a contiguous 2d array (1d array with size rows*numOfFeatures)
//Assumes last column is the dependent
void gd_train(GD_Model* model,double*data,long rows,double eps){
	double learningrate=0.01;
	long cols = model->numOfFeatures+1;
	double*gradients = malloc((cols)*sizeof(double));
	double*errors = malloc(rows*sizeof(double));
	double lastError=INFINITY;//set to infinity
	//zero the weights
	for(int c=0;c<(cols);c++){
		model->weights[c]=0;
	}
	//cap out at 1,000,000 iterations
	for(int i=0;i<1000000;i++){
		double totalError=0;

		//iterate through the rows and features to calculate gradients
		for(int r=0;r<rows;r++){
			//calculate what the model would predict in this row
			errors[r]=model->weights[model->numOfFeatures];
			for(int c=0;c<(model->numOfFeatures);c++){
				errors[r]+=model->weights[c]*data[r*cols+c];
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
				model->weights[c]+=gradients[c]*2*learningrate/rows;
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
			gradients[model->numOfFeatures]+=errors[r];

			//calculate the gradients for the other features
			for(int c=0;c<(model->numOfFeatures);c++){
				gradients[c]+=errors[r]*data[r*cols+c];
			}
		}

		//transfer gradients into weights by a learning factor
		for(int c=0;c<cols;c++){
			model->weights[c]-=gradients[c]*2*learningrate/rows;
		}		
	}
	printf("LAstError: %f",lastError);
	free(errors);
	free(gradients);
}
