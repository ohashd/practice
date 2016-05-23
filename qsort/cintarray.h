#ifndef __CINTARRAY__
#define __CINTARRAY__

class CIntArray{
public:
	CIntArray();
	CIntArray(int n);
	CIntArray(CIntArray &other);
	CIntArray& operator=(CIntArray other);
	~CIntArray();
	const int size() const;
	void push(int n);
	int operator[](int i);
private:
	int m_size;
	int m_maxsize;
	int *m_arr;
};

#endif