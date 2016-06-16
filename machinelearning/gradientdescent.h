#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

typedef struct {
	double *weights;
	long numOfFeatures;
} GD_Model;

GD_Model* gd_create(long numOfFeatures);
void gd_destroy(GD_Model* model);

void gd_train(GD_Model* model, double* data,long rows,double eps);
double gd_predict(GD_Model* model,double *features);

#endif