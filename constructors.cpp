#include <iostream>

struct Demo
{
	Demo(const size_t size) : size(size), _data(new int[size])
	{
		std::cout << "Demo::Demo(const size_t) - initialize _data to size " << size << " with " << sizeof(int) << " bytes each" << std::endl;
	}

	Demo() : size{0}, _data(nullptr)
	{
		std::cout << "Demo::Demo() - initialized _data to nullptr" << std::endl;
	}

	Demo(const Demo& other) : size(other.size), _data(new int[size])
	{
		std::cout << "Demo::Demo(const Demo&) - copied " << size << " data from other" << std::endl;
		for (size_t i=0; i<size; i++) {_data[i] = other._data[i];}
	}
	
	Demo(Demo&& other) : size(other.size), _data(other._data)
	{
		other._data = nullptr;
		std::cout << "Demo::Demo(Demo&&) - moved ownership of " << size << " data from other" << std::endl;
	}

	virtual ~Demo()
	{
		size_t freed_space = 0;
		if (_data) {freed_space = size * sizeof(int);}

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
		_data = new int[size];
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
	int* _data;
};

std::ostream& operator<<(std::ostream& os, const Demo& D)
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
	Demo a; //default constructor
	Demo b = Demo(10); //explicit constructor!
	Demo c(b); //copy constructor
	Demo d(std::move(c)); //move constructor
	Demo e = std::move(d); //move constructor
	a = std::move(e); //move assignment (make sure this frees any resources a previously owned)
	a = b; //copy assignment (make sure this frees any resources a previously owned)

	return 0;	
}