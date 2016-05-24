#ifndef __DARRAY__
#define __DARRAY__

#include <cstring>

template<typename T>
class DArray{
public:
	DArray();

	DArray(const DArray& other);
	DArray(DArray &&other) noexcept;

	DArray& operator=(const DArray& other);
	DArray& operator=(DArray &&other) noexcept;

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