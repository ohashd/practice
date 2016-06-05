#include "darray.h"

struct darray{
	int size;
	int capacity;
	int* arr;
};

darray* darray_init(){
	darray* ret = malloc(sizeof(darray));
	if(!ret){
		return NULL;
	}
	ret->arr = malloc(sizeof(int)*7);
	if(!ret->arr){
		free(ret);
		return NULL;
	}
	ret->size=0;
	ret->capacity=7;
	return ret;
}
int darray_get(darray* darr, int ind){
	return darr->arr[ind];
}
void darray_set(darray* darr, int ind, int val){
	darr->arr[ind]=val;
}
void darray_insert(darray* darr, int val){
	if(darr->size==darr->capacity){
		int *newarr = realloc(darr->arr,sizeof(int)*darr->capacity*2);
		if(!newarr)return;
		darr->arr=newarr;
		darr->capacity*=2;
	}
	darr->arr[darr->size]=val;
	darr->size++;
}
void darray_destroy(darray* darr){
	free(darr->arr);
	free(darr);
}

int darray_size(darray* darr){
	return darr->size;
}