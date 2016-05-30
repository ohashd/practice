//Default constructor
template <typename T>
DHeap<T>::DHeap():
m_size(0),
m_maxsize(7){
	m_heap = new T[7];
}

//Copy constructor
template <typename T>
DHeap<T>::DHeap(const DHeap<T>& other):
m_size(other.m_size),
m_maxsize(other.m_maxsize){
	m_heap = new T[m_maxsize];
	std::memcpy(m_heap,other.m_heap,sizeof(T)*other.m_size);
}

//Copy construct from darray
template <typename T>
DHeap<T>::DHeap(const DArray<T> &other):
m_size(other.m_size),
m_maxsize(other.m_maxsize){
	m_heap = new T[m_maxsize];
	std::memcpy(m_heap,other.m_arr,sizeof(T)*other.m_size);

	for(int start = (m_size&1 ? (m_size-1)/2 : (m_size-2)/2);
		start>=0;start--){
		bubdwn(start);
	}
}

//Move construct from darray
template <typename T>
DHeap<T>::DHeap(DArray<T> &&other):
m_size(other.m_size),
m_maxsize(other.m_maxsize){
	m_heap = other.m_arr;
	other.m_arr=NULL;

	for(int start = (m_size&1 ? (m_size-1)/2 : (m_size-2)/2);
		start>=0;start--){
		bubdwn(start);
	}
}

//Move constructor
template <typename T>
DHeap<T>::DHeap(DHeap<T> &&other) noexcept:
m_size(other.m_size),
m_maxsize(other.m_maxsize),
m_heap(other.m_heap){
	other.m_heap=NULL;
}

//Destructor
template <typename T>
DHeap<T>::~DHeap(){
	delete [] m_heap;
}

//Assignment Operator
template <typename T>
DHeap<T>& DHeap<T>::operator=(const DHeap<T>& other){
	if(this!=&other){

		m_maxsize=other.m_maxsize;
		m_size = other.m_size;

		delete [] m_heap;
		m_heap=NULL;
		m_heap = new T[m_maxsize];
		std::memcpy(m_heap,other.m_heap,sizeof(T)*other.m_size);
	}

	return *this;
}

//Move Assignement
template <typename T>
DHeap<T>& DHeap<T>::operator=(DHeap<T> &&other) noexcept{

	m_size = other.m_size;
	m_maxsize = other.m_maxsize;

	delete m_heap;
	m_heap = other.m_heap;
	other.m_heap = NULL;

	return *this;
}

template <typename T>
void DHeap<T>::push(T elem){
	if(m_size>=m_maxsize){
		T *newheap = new T[m_maxsize*2];
		m_maxsize=m_maxsize*2+1;
		std::memcpy(newheap,m_heap,sizeof(T)*m_size);
		delete [] m_heap;
		m_heap = newheap;
	}
	m_heap[m_size]=elem;
	bubup(m_size);
	m_size++;
}

template <typename T>
void DHeap<T>::bubup(int ind){
	while(ind > 0){
		int parent = (ind&1 ? (ind-1)/2 : (ind-2)/2);
		if(m_heap[ind]>m_heap[parent]){
			std::swap(m_heap[ind],m_heap[parent]);
			ind=parent;
		}else{
			break;
		}
	}
}

template <typename T>
void DHeap<T>::bubdwn(int ind){
	while(true){
		int right = ind*2+2;
		int left = ind*2+1;
		if(left<m_size && right<m_size){
			if(m_heap[ind]<m_heap[left] && m_heap[left] >=m_heap[right]){
				std::swap(m_heap[ind],m_heap[left]);
				ind=left;
			}else if(m_heap[ind]<m_heap[right]){
				std::swap(m_heap[ind],m_heap[right]);
				ind=right;
			}else{
				break;
			}
		}else if(left<m_size){
			if(m_heap[ind]<m_heap[left]){
				std::swap(m_heap[ind],m_heap[left]);
				break;			}
		}else{
			break;
		}
	}
}

template <typename T>
const int DHeap<T>::size() const{
	return m_size;
}

template <typename T>
T& DHeap<T>::operator[](int ind){
	return m_heap[ind];
}

template <typename T>
const T& DHeap<T>::operator[](int ind) const{
	return m_heap[ind];
}