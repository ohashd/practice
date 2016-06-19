#include "knn.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

KNN_Model* knn_init(KNN_Model* model,double* data, long rows, long cols, long k){
	model->data = malloc(sizeof(double)*rows*cols);
	if(!model->data){
		return NULL;
	}
	memcpy(model->data,data,sizeof(double)*cols*rows);
	model->rows = rows;
	model->cols = cols;
	model->k = k;
	return model;
}
void knn_cleanup(KNN_Model* model){
	free(model->data);
}

typedef struct{
	double prediction;
	double distance;
} closePair;

double knn_predict(KNN_Model* model,double *features){
	closePair* closestRows = malloc(sizeof(closePair)*model->k);
	if(!closestRows){
		return NAN;
	}

	for(long k=0;k<model->k;k++){
		closestRows[k].distance=INFINITY;
	}

	long numOfFeatures = model->cols-1;

	for(long r = 0;r<model->rows;r++){
		double dist = 0;
		for(long c =0;c<numOfFeatures;c++){
			double ldist = (features[c]-model->data[r*model->cols+c]);
			dist+= ldist*ldist;
		}

		//check if this row is closer to features (first item in closestRows will always be the most distant closest point)
		if(dist>=closestRows[0].distance)continue;

		long k=1;
		while(k<model->k && dist<closestRows[k].distance) k++;
		k--;
		//move all elements back
		for(long i=0;i<k;i++){
			closestRows[i]=closestRows[i+1];
		}
		
		closestRows[k].prediction = model->data[(r+1)*model->cols-1];
		closestRows[k].distance = dist;

	}


	double prediction=0;

	for(long k=0;k<model->k;k++){
		prediction+=closestRows[k].prediction;
	}
	prediction/=model->k;

	return prediction;
}