#include "cintarray.h"
#include <iostream>
CIntArray::CIntArray():m_size(0),m_maxsize(5){
	m_arr = new int[5];
}

CIntArray::CIntArray(int n):m_size(0),m_maxsize(n){
	m_arr = new int[n];
}

CIntArray::CIntArray(CIntArray &other){
	m_size = other.m_size;
	m_maxsize = other.m_maxsize;
	m_arr = new int[m_maxsize];
	for(int i=0;i<other.m_size;i++){
		m_arr[i]=other.m_arr[i];
	}
}

CIntArray& CIntArray::operator=(CIntArray other){
	m_size = other.m_size;
	m_maxsize = other.m_maxsize;
	std::swap(m_arr,other.m_arr);
	return (*this);
}

CIntArray::~CIntArray(){
	delete [] m_arr;
}

const int CIntArray::size() const{
	return m_size;
}

void CIntArray::push(int n){
	if(m_size>=m_maxsize){
		int *newarr = new int[m_maxsize*2];
		for(int i=0;i<m_size;i++){
			newarr[i]=m_arr[i];
		}
		delete [] m_arr;
		m_arr = newarr;
	}
	m_arr[m_size]=n;
	m_size++;
}

int CIntArray::operator[](int i){
	return m_arr[i];
}