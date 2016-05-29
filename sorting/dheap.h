#ifndef __DHEAP__
#define __DHEAP__

#include <cstring>

template <typename T>
class DHeap{
public:
	DHeap();
	~DHeap();

	DHeap(const DHeap&);
	DHeap(DHeap &&) noexcept;

	DHeap& operator=(const DHeap&);
	DHeap& operator=(DHeap &&) noexcept;

	const int size() const;
	void insert(T);
private:
	int m_size;
	int m_maxsize;
	T *m_heap;
};

#include "dheap.tcc"

#endif