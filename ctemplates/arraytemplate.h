#include <stdlib.h>
#include <assert.h>

#define DEFARRAY(type) \
	typedef struct array_##type array_##type; \
	\
	array_##type* new_array_##type(); \
	void delete_array_##type(array_##type*); \
	type array_##type##_get(array_##type*,int); \
	void array_##type##_set(array_##type*,int,type); \
	int array_##type##_insert(array_##type*,type); \
	int array_##type##_size(array_##type *o); \

#define DECLARRAY(type) \
	struct array_##type{ \
			type *arr; \
			int size, maxsize; \
	}; \
	\
	array_##type* new_array_##type(){ \
		array_##type * ret = malloc(sizeof(array_##type)); \
		if(ret==NULL)return NULL; \
		ret->arr = malloc(sizeof(type)*7); \
		if((ret->arr) == NULL){ \
			free(ret); \
			return NULL;\
		} \
		ret->size=0; \
		ret->maxsize=7; \
		return ret; \
	} \
	\
	void delete_array_##type(array_##type * o){ \
		free(o->arr); \
		free(o); \
	} \
	\
	type array_##type##_get(array_##type* o, int ind){ \
		assert(o);assert(ind>=0);assert(ind<(o->size)); \
		return o->arr[ind]; \
	} \
	void array_##type##_set(array_##type*o,int ind, type val){ \
		assert(o);assert(ind>=0);assert(ind<(o->size)); \
		o->arr[ind]=val; \
	} \
	\
	int array_##type##_insert(array_##type*o,type val){ \
		assert(o); \
		if((o->size)==(o->maxsize)){ \
			void * temp = realloc(o->arr,sizeof(type)*(o->maxsize*2+1)); \
			if(temp){ \
				o->arr = temp; \
				o->maxsize = o->maxsize*2+1; \
			}else return 0; \
		} \
		o->arr[o->size]=val; \
		o->size++; \
		return 1; \
	} \
	int array_##type##_size(array_##type *o){ \
		return o->size; \
	}
