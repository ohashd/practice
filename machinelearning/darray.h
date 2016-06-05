#ifndef __DARRAY__
#define __DARRAY__

#include <stdlib.h>

typedef struct darray darray;

darray* darray_init();
int darray_get(darray*, int ind);
void darray_set(darray*, int ind, int val);
void darray_insert(darray*, int val);
void darray_destroy(darray*);
int darray_size(darray*);


#endif