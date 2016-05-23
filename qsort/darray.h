#ifndef __DARRAY__
#define __DARRAY__

#include <utility>

template<typename T>
class DArray{
public:
	DArray();
	explicit DArray(int n);
	DArray(const DArray &other);
	DArray& operator=(DArray other);
	~DArray();
	const int size() const;
	void push(T item);
	T& operator[](int ind);
private:
	int m_size;
	int m_maxsize;
	T *m_arr;
};

#include "darray.tcc" //template implementation

#endif