#include "gradientdescent.h"
#include <stdlib.h>
#include <math.h>

//Assumes data is a contiguous 2d array (1d array with size rows*cols)
//Assumes last column is the dependent
GD_Model* gd_init(GD_Model* model,double *data, long rows,long cols, double eps){
	model->weights = calloc(cols,sizeof(double));
	if(!model->weights){
		return NULL;
	}

	double*gradients = malloc((cols+rows)*sizeof(double));
	if(!gradients){
		free(model->weights);
		return NULL;
	}
	double*errors = gradients+cols;
	long features = model->numOfFeatures = cols-1;

	double learningrate=0.01;
	double lastError=INFINITY;//set to infinity

	//cap out at 1,000,000 iterations
	for(int i=0;i<1000000;i++){
		double totalError=0;

		//iterate through the rows and features to calculate gradients
		for(int r=0;r<rows;r++){
			//calculate what the model would predict in this row
			errors[r]=model->weights[features];
			for(int c=0;c<(features);c++){
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
			gradients[features]+=errors[r];

			//calculate the gradients for the other features
			for(int c=0;c<(features);c++){
				gradients[c]+=errors[r]*data[r*cols+c];
			}
		}

		//transfer gradients into weights by a learning factor
		for(int c=0;c<cols;c++){
			model->weights[c]-=gradients[c]*2*learningrate/rows;
		}		
	}
	free(gradients);

	return model;
}

void gd_cleanup(GD_Model* model){
	free(model->weights);
}

double gd_predict(GD_Model* model, double* features){
	double ret = model->weights[model->numOfFeatures];
	for(int c=0;c<model->numOfFeatures;c++){
		ret+=model->weights[c]*features[c];
	}
	return ret;
}
