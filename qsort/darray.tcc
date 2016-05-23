template<typename T>
DArray<T>::DArray():m_size(0),m_maxsize(5){
	m_arr = new T[5];
}

template<typename T>
DArray<T>::DArray(int n):m_size(0),m_maxsize(n){
	m_arr = new T[n];
}

template<typename T>
DArray<T>::DArray(DArray<T> &other){
	m_arr = new T[m_maxsize];
	m_size = other.m_size;
	m_maxsize = other.m_maxsize;
	for(int i=0;i<other.m_size;i++){
		m_arr[i]=other.m_arr[i];
	}
}

template<typename T>
DArray<T>& DArray<T>::operator=(DArray<T> other){
	m_size = other.m_size;
	m_maxsize = other.m_maxsize;
	std::swap(m_arr,other.m_arr);
	return (*this);
}

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