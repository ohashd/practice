#ifndef __DARRAY__
#define __DARRAY__

template<typename T>
class DArray{
public:
	DArray();
	~DArray();

	DArray(const DArray& other);
	DArray(DArray &&other) noexcept;

	DArray& operator=(const DArray& other);
	DArray& operator=(DArray &&other) noexcept;
	
	T& operator[](int ind);
	const T& operator[](int ind) const;

	const int size() const;
	void push(T item);

private:
	int m_size;
	int m_maxsize;
	T* m_arr;
};

template<typename T>
bool operator==(const DArray<T> &lhs, const DArray<T> &rhs);

#include "darray.tcc" //template implementation

#endif