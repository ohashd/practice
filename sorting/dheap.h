#ifndef __DHEAP__
#define __DHEAP__

#include <cstring>

template <typename T>
class DArray;

template <typename T>
class DHeap{
public:
	DHeap();
	~DHeap();

	DHeap(const DHeap&);
	DHeap(DHeap &&) noexcept;
	DHeap(const DArray<T> &);
	DHeap(DArray<T> &&);

	DHeap& operator=(const DHeap&);
	DHeap& operator=(DHeap &&) noexcept;

	T& operator[](int);
	const T& operator[](int) const;

	const int size() const;
	void push(T);
	
private:
	int m_size;
	int m_maxsize;
	T *m_heap;
};

#include "dheap.tcc"

#endif