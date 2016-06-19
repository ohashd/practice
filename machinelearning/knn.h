#ifndef KNN_H
#define KNN_H

typedef struct {
	double *data;
	long rows;
	long cols;
} KNN_Model;

KNN_Model* knn_init(KNN_Model* model,double* data, long rows, long cols);
void knn_cleanup(KNN_Model* model);

double knn_predict(KNN_Model* model,double *features);

#endif