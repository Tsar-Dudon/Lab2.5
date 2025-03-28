#include <iostream>

class MyVector
{
	int* m_arr;
	size_t m_size;
	size_t m_cap = 0;
public:
	MyVector()
	{
		m_size = 0;
		m_cap = m_size;
		m_arr = nullptr;
	}
	MyVector(size_t size, int value)
	{
		m_arr = new int[size];
		m_size = size;
		m_cap = m_size;
		for(size_t i = 0; i < m_size; i++)
			m_arr[i] = value;
	}
	MyVector(const MyVector& other){
		m_size = other.m_size;
		m_cap = m_size;
		m_arr = new int[m_size];
		std::copy(other.m_arr, other.m_arr+m_size, m_arr);
	}
	MyVector& operator=(const MyVector& other){
		if(&other != this) {
			m_size = other.m_size;
			m_cap = m_size;
			if(m_arr != nullptr)
				delete[] m_arr;
			m_arr = new int[m_size];
			std::copy(other.m_arr, other.m_arr+m_size, m_arr);
		}
		return *this;
	}
	~MyVector()
	{
		if(m_arr != nullptr)
			delete[] m_arr;
	}


	void push_back(int value){
		if(m_size+1 <= m_cap)
		{
			m_arr[m_size] = value;
			m_size++;
			return;
		}
		m_cap = m_cap*2 + 1;
		int* tmp = new int[m_cap];
		std::copy(m_arr, m_arr + m_size, tmp);
		tmp[m_size] = value;
		delete[] m_arr;
		m_arr = tmp;
		m_size++;
	}

	void reserve(size_t cap){
		if(m_size >= m_cap)
			return;
		m_cap = cap;
		int* tmp = new int[m_cap];
		std::copy(m_arr, m_arr + m_size, tmp);
		delete[] m_arr;
		m_arr = tmp;
	}

	void shrink_to_fit(){
		m_cap = m_size;
		int* tmp = new int[m_cap];
		std::copy(m_arr, m_arr + m_size, tmp);
		delete[] m_arr;
		m_arr = tmp;
	}

	int& operator[](size_t index){
		return m_arr[index];
	}

	int& back(){
		return m_arr[m_size-1];
	}

	int& front(){
		return m_arr[0];
	}

	bool empty(){
		if(m_size > 0)
			return false;
		return true;
	}

	void resize(size_t size){
		int* tmp = new int[size];
		std::copy(m_arr, m_arr + size, tmp);
		delete[] m_arr;
		m_arr = tmp;
		if(size > m_size)
		{
			for(size_t i = m_size; i < size; i++)
				m_arr[i] = 0;
		}
		m_size = size;
		m_cap = size;
	}

	void insert(size_t position, int value){
		int* tmp = new int[m_size + 1];
		for(size_t i = 0; i < position; i++)
			tmp[i] = m_arr[i];
		tmp[position] = value;
		for(size_t i = position + 1; i < m_size+1; i++)
			tmp[i] = m_arr[i-1];
		delete[] m_arr;
		m_arr = tmp;
		m_size += 1;
		m_cap += 1;
	}

	void erase(size_t position){
		int* tmp = new int[m_size - 1];
		for(size_t i = 0; i < position; i++)
			tmp[i] = m_arr[i];
		for(size_t i = position; i < m_size-1; i++)
			tmp[i] = m_arr[i+1];
		delete[] m_arr;
		m_arr = tmp;
		m_size -= 1;
		m_cap -= 1;
	}

	size_t size(){
		return m_size;
	}
	size_t capacity(){
		return m_cap;
	}
};


int main()
{	
	MyVector mas(15, 23);
	mas[9] = 3;
	mas.insert(9, 4);
	for(short i = 0; i < mas.size(); i++)
		std::cout << mas[i] << std::endl;
	return 0;
}