//Default constructor
template <typename T>
DHeap<T>::DHeap():m_size(0),m_maxsize(5),m_heap(NULL){
	m_heap = new T[5];
}

//Copy constructor
template <typename T>
DHeap<T>::DHeap(const DHeap<T>& other):
m_size(other.m_size),
m_maxsize(other.m_maxsize),
m_heap(NULL){
	m_heap = new T[m_maxsize];
	std::memcpy(m_heap,other.m_heap,sizeof(T)*other.m_size);
}

//Moce constructor
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
const int DHeap<T>::size() const{
	return m_size;
}