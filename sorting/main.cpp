#include <iostream>
#include <utility>
#include <cstring>
#include "darray.h"

//Radix Sort for 32 bit Ints
void rsort(int*arr, int size){
	int *end = arr+size;
	int *workarr = new int[size];
	int *workend = workarr+size;
	//convert to uint
	for(int* p=arr; p<end; p++){
		*p = (*p) ^ (1 << 31);
	}

	for(int shift=0;shift<32;shift+=8){

		int count[256]={0};
		for(int* p=arr; p<end; p++){
			count[(*p>> shift) & 255]++;
		}
		int*bucketStarts[256];
		int *starts = workarr;
		for(int i=0;i<256;i++){
			bucketStarts[i]=starts;
			starts+=count[i];
		}
		for(int *p=arr;p<end;p++){
			*(bucketStarts[(*p >> shift) & 255])++=*p;
		}
		std::swap(arr,workarr);
		std::swap(end,workend);
	}
	//convert back to int
	for(int* p=arr; p<end; p++){
		*p = (*p) ^ (1 << 31);
	}

	delete [] workarr;
}

void splitAndMerge(int*arr, int *work, int left, int right){
	if(left>=right)return;
	int size = right - left + 1;
	int mid = int((left+right)/2);
	splitAndMerge(work,arr,left,mid);
	splitAndMerge(work,arr,mid+1,right);

	int r=mid+1;
	int l=left;

	for(int i=left;i<size+left;i++){
		if(l<=mid && (r>right || *(work+l)< *(work+r) )){
			*(arr+i)=*(work+l);
			l++;
		}else{
			*(arr+i)= *(work+r);
			r++;
		}
	}

}

//Merge sort
void msort(int *left, int size){
	int *work = new int[size];
	std::memcpy(work,left,sizeof(int)*size);
	splitAndMerge(left,work,0,size-1);
	delete [] work;
}

//Comb Sort
void csort(int *left, int size){

	int gap = size;
	bool swap = false;
	while(size>1 && swap){

		swap=false;
		gap =int(gap/1.3);
		gap = gap < 1 ? 1 : gap;

		for(int i=gap;i<size;i++){
			if(*(left+i)<*(left+i-1)){
				swap=true;
				std::swap(*(left+i),*(left+i-1));
			}
		}

	}

}

//Bubble Sort
void bsort(int *left, int size){
	bool swap;
	do{
		swap=false;
		for(int i=1;i<size;i++){
			if(*(left+i)<*(left+i-1)){
				swap=true;
				std::swap(*(left+i),*(left+i-1));
			}
		}
		size--;
	}while(swap);
}

//Shell Sort
void shellsort(int *left, int size){
	//Ciura gap sequence
	static const int gaps[] = {701,301,132,57,23,10,4,1};
	for(int i=0;i<8;i++){//loop through gaps
		for(int j=gaps[i];j<size;j++){
			int* ind = left+j;
			int tmp = *ind;
			while(ind>left && *(ind-1)>tmp){
				*ind = *(ind-1);
				ind--;
			}
			*ind=tmp;
		}
	}
}


void bubdwn(int*root,int i,int size){
	for(;;){
		int child = i*2+1;
		if(child>=size)return;
		if(child+1<size && root[child]<root[child+1])child++;
		if(root[child]>root[i]){
			std::swap(root[child],root[i]);
			i=child;
		}else return;
	}
}

//heap sort
void hsort(int*left, int size){
	//HEAPIFY (max heap)
	int firstBub = size&1 ? (size-3)/2 : (size-2)/2;
	for(int j=firstBub;j>=0;j--){
		bubdwn(left,j,size);
	}
	//Extract from top to sort:
	while(size>1){
		std::swap(left[0],left[size-1]);
		bubdwn(left,0,size-1);
		size--;
	}
}

//selection sort
void ssort(int*left, int size){
	for(int i=size-1;i>=0;i--){
		int *highest=left;
		for(int j=0;j<i;j++){
			if(*(left+j)>*highest){
				highest=(left+j);
			}
		}
		if(*highest>*(left+i)){
			std::swap(*highest,*(left+i));
		}
	}
}

//insertion sort
void isort(int*left,int size){
	for(int i=1;i<size;i++){
		int *j=(left+i);
		int temp = *j;
		while(j>left && temp<*(j-1)){
			*j=*(j-1);
			j--;
		}
		*j=temp;
	}
}

//dupe qsort
void dqsort(int*left, int*right){
	if(left>=right)return;
	int* pivot = left + std::rand() % (1+right-left);
	std::swap(*pivot,*left);
	int *i=left+1;
	int *lt=left;
	int *gt=right;
	while(i<=gt){
		if(*i==*lt){
			i++;
		}else if(*i<*lt){
			std::swap(*lt,*i);
			i++;
			lt++;
		}else if(*i>*lt){
			std::swap(*gt,*i);
			gt--;
		}
	}
	dqsort(left,lt-1);
	dqsort(gt+1,right);
}
//nondupe qsort
void qsort(int*left, int*right){
	if(left>=right)return;
	int* pivot = left + std::rand() % (1+right-left);
	std::swap(*pivot,*right);
	int *i=left;
	int *j=right-1;
	while(i<=j){
		if(*i <= *right){
			i++;
		}else if(*j > *right){
			j--;
		}else{
			std::swap(*j,*i);
			j--;
			i++;
		}
	}
	if(i==right){
		qsort(left,i-1);
		return;
	}
	std::swap(*right,*i);
	qsort(left,i-1);
	qsort(i+1,right);
}

void sort(DArray<int>& arr){
	if(arr.size()>0)
	rsort(&arr[0],arr.size());
	//msort(&arr[0],arr.size());
	//bsort(&arr[0],arr.size());
	//shellsort(&arr[0],arr.size());
	//hsort(&arr[0],arr.size());
	//ssort(&arr[0],arr.size());
	//isort(&arr[0],arr.size());
	//dqsort(&arr[0],&arr[arr.size()-1]);
	//qsort(&arr[0],&arr[arr.size()-1]);
}

int main(){
	DArray<int> nums;
	int in;
	while(std::cin >> in){
		nums.push(in);
	}
	sort(nums);
	for(int i=0;i<nums.size();i++){
		std::cout << nums[i] <<std::endl;
	}
}