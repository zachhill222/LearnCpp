#include <iostream>

//compile with:
// g++ -o main constructors.cpp
// run with:
// ./main
// OR
// valgrind ./main
// to verify that there are no memory leaks


template<typename T>
struct Demo
{
	Demo(const size_t size) : size(size), _data(new T[size])
	{
		std::cout << "Demo::Demo(const size_t) - initialize _data to size " << size << " with " << sizeof(_data[0]) << " bytes each" << std::endl;
	}

	Demo() : size{0}, _data(nullptr)
	{
		std::cout << "Demo::Demo() - initialized _data to nullptr" << std::endl;
	}

	Demo(const Demo& other) : size(other.size), _data(new T[size])
	{
		std::cout << "Demo::Demo(const Demo&) - copied " << size << " data from other" << std::endl;
		for (size_t i=0; i<size; i++) {_data[i] = other._data[i];}
	}
	
	Demo(Demo&& other) : size(other.size), _data(&other._data)
	{
		other._data = nullptr;
		std::cout << "Demo::Demo(Demo&&) - moved ownership of " << size << " data from other" << std::endl;
	}

	virtual ~Demo()
	{
		size_t freed_space = 0;
		if (_data) {freed_space = size * sizeof(_data[0]);}

		std::cout << "Demo::~Demo() - freed " << freed_space << " bytes" << std::endl;
		delete[] _data;
	}

	Demo& operator=(const Demo& other)
	{
		if (this == &other)
		{
			std::cout << "Demo::operator=(const Demo&) - tried to copy itself" << std::endl;
			return *this;
		}

		size = other.size;
		delete[] _data;
		_data = new T[size];
		for (size_t i=0; i<size; i++) {_data[i] = other._data[i];}

		std::cout << "Demo::operator=(const Demo&) - copied " << size << " data from other" << std::endl;
		return *this;
	}

	Demo& operator=(Demo&& other)
	{
		if (this == &other)
		{
			std::cout << "Demo::operator=(Demo&&) - tried to move itself" << std::endl;
			return *this;
		}

		size = other.size;
		delete[] _data;
		_data = other._data;
		other._data = nullptr;
		std::cout << "Demo::operator=(Demo&&) - moved ownership of " << size << " data" << std::endl;
		return *this;
	}


	size_t size;
	T* _data;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Demo<T>& D)
{
	std::cout << "[ ";
	for (size_t i=0; i<D.size; i++)
	{
		std::cout << D._data[i] << " ";
	}
	std::cout << "]\n";
	return os;
}


int main()
{
	using Demo_t = Demo<short>;

	Demo_t a; //default initialize
	Demo_t b = Demo_t(10); //explicit initialize to 10 then move assignment
	Demo_t c = a; //copy initialize
	c = a; //copy assignment
	c = std::move(b); //move assignment
	c = Demo_t(10); //explicit initialize


	// Demo<Demo_t> a(10);
	// std::cout << "a:\n" << a << std::endl;

	// for (size_t i=0; i<a.size; i++)
	// {
	// 	a._data[i] = Demo_t(i);
	// }

	// std::cout << "\na:\n" << a << std::endl;

	
	return 0;	
}