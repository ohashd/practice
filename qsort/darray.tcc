//Default Constructor
template<typename T>
DArray<T>::DArray():m_size(0),m_maxsize(5){
	m_arr = new T[5];
}

//Copy Constructor
template<typename T>
DArray<T>::DArray(const DArray<T> &other):
m_size(other.m_size),
m_maxsize(other.m_maxsize){
	m_arr = new T[m_maxsize];
	std::memcpy(m_arr,other.m_arr,sizeof(T)*other.m_size);
}

//Move Constructor
template<typename T>
DArray<T>::DArray(DArray<T>&& other) noexcept:
m_arr(other.m_arr),
m_size(other.m_size),
m_maxsize(other.m_maxsize){
	other.m_arr=NULL;
}

//Assignment Operator
template<typename T>
DArray<T>& DArray<T>::operator=(const DArray<T>& other){

	if(this!=&other){

		m_size=other.m_size;
		m_maxsize=other.m_maxsize;

		delete [] m_arr;
		m_arr=NULL;
		m_arr = new T[m_maxsize];
		std::memcpy(m_arr,other.m_arr,sizeof(T)*other.m_size);
	}

	return (*this);
}

//Move Operator
template<typename T>
DArray<T>& DArray<T>::operator=(DArray<T>&& other) noexcept{
	m_size = other.m_size;
	m_maxsize = other.m_maxsize;

	delete [] m_arr;
	m_arr = other.m_arr;
	other.m_arr=NULL;

	return (*this);
}

//Destructor
template<typename T>
DArray<T>::~DArray(){
	delete [] m_arr;
}

template<typename T>
const int DArray<T>::size() const{
	return m_size;
}

template<typename T>
void DArray<T>::push(T n){
	if(m_size>=m_maxsize){
		T *newarr = new T[m_maxsize*2];
		for(int i=0;i<m_size;i++){
			newarr[i]=m_arr[i];
		}
		delete [] m_arr;
		m_arr = newarr;
	}
	m_arr[m_size]=n;
	m_size++;
}

template<typename T>
T& DArray<T>::operator[](int i){
	return m_arr[i];
}