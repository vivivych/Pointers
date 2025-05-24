#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

//������������ �������
//������������ ���������� ������, ������ �������� ����� ������ ���������� ��������� �� ����� ���������� ���������.
//��� ���������� ������������� ������� ����� �������� ��������� � �������� ������ ��� ������ ��������� "new"
//�������� new �������� ����������� ���� ������ ��� n ��������� ��������� ����. � ���������� ����� ���������� ������. ���� ����� ���������� � ��������� arr.
//�������� new ����������� ������ ������������ �������. ����� ������������� ��� ������ ����� ������� �������. ��� ������ �������� delete
//�� ����������� ������, ���������� ���������� new � ���������� �� ������� �������. 
// ���� �� ������� ������ �� �� ���������� ������ ������ (memory leak) ���� ������ ������ ���������� ��������� �� ���� ��� ������ ��� ��������� ������ ����������. 
// �������� delete ������ ���� ������ ������� ���, ������� ��� ������ new. 
//���������� � ��������� ������� ������� ����� ��� �� ��� � ��������� ������������. ����� ���������� ���������� � �������� ������������ ��� ����� �������� ��������������. 
//���� � �� �� ������� ����� �������� ��� �� ������������ ��� � � ������������� ���������. 
// � ������� ������ ����� ��������� ��������. ��� ������� ���������������� ������. ����� �������� ����� ������� ������ ������� �������, ����������� ���� ��� �������� �� ��������� �������, 
// ������ ����� ����� � ����� ������� ��������� �������, � ������� ����� �������� ��������.

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T**& arr, const int rows);

void FillRand(int arr[], const int n);
void FillRand(double arr[], const int n);
void FillRand(char arr[], const int n);

void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);
void FillRand(char** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, const T value);
template<typename T>T* push_front(T arr[], int& n, const T value);
template<typename T>T* insert(T arr[], int& n, const T value, int index);

template<typename T>T* pop_back(T arr[], int& n);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);
template<typename T>void pop_col_back(T** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

#define DATA_TYPE double

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "������� ������ �������: "; cin >> n;
	double* arr = new double[n];

	FillRand(arr, n);
	Print(arr, n);
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
	/*
	----------------------------------
	+, -, ++, --;
	----------------------------------
	*/

	double value;
	cout << "������� ����������� ��������: "; cin >> value;

	arr = push_back(arr, n, value);

	//7) �������� ���������, ��������� ���������:
	Print(arr, n);


	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	Print(arr = pop_back(arr, n), n);
	

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������� ������: "; cin >> cols;

	typedef double DataType;	//������������ ���� ������ ���� ������ ���

	//1) ������� ������ ����������:
	char** arr = Allocate<char>(rows, cols);

	/*cout << "������ ��������, ��� ���������� �������";
	system("PAUSE");

	push_col_back(arr, rows, cols);

	cout << "������� ��������" << endl;*/

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//int   - 'int';
	//int*  - ��������� �� 'int';
	//int** - ��������� �� ��������� �� 'int';

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols);
	Print(arr, rows, cols);

	arr = push_row_front(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	pop_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);
	cout << arr << endl;
	Print(arr, rows, cols);
#endif // DYNAMIC_MEMORY_2
}

template<typename T>T** Allocate(const int rows, const int cols)
{
	T** arr = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols]{};
	}
	return arr;
}
template<typename T>void Clear(T**& arr, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}
//���������� : ��� �������� ��������� � ������� ������� ��������� ��� ������ ����������� � �������. ����� ��������� ��� ����� � ���������. 

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
		//Index operator, Subscript operator;
	}
}

void FillRand(double arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 10000;
		arr[i] /= 100;
		//Index operator, Subscript operator;
	}
}
void FillRand(char arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
		//Index operator, Subscript operator;
	}
}

void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}
void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double(rand() % 10000) / 100;
		}
	}
}
void FillRand(char** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand();
		}
	}
}

template<typename T>void Print(T arr[], const int n)
{
	cout << arr << ":\n";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
{
	if (arr == nullptr)
	{
		cout << "Error: No memory aloocated" << endl;
		return;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << delimiter << endl;
	cout << endl;
}

template<typename T>T* push_back(T arr[], int& n, const T value)
{

	//1) ������� �������� ������ ������� �������:
	T* buffer = new T[n + 1];

	//2) �������� ��� ���������� ��������� ������� � ��������:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) ������� �������� ������:
	delete[] arr;

	//4) ��������� ����� � ��������� 'arr' ������� ������ �������:
	arr = buffer;

	//5) ������ ����� ����� ����� � ����� ������� ���������� �������, 
	//	 � ������� ����� ��������� ����������� ��������:
	arr[n] = value;

	//6) ����� ���� ��� � ������ ��������� �������, 
	//	 ���������� ��� ��������� ������������� �� 1:
	n++;

	return arr;
}

template<typename T>T* push_front(T arr[], int& n, const T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}
template<typename T>T* insert(T arr[], int& n, const T value, int index)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < index; i++)
		buffer[i] = arr[i];
	for (int i = index; i < n; i++)
		buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	return push_back(arr, rows, new T[cols]{});
}
template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
{
	return push_front(arr, rows, new T[cols]{});
}
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	delete[] arr[rows - 1];	//�������� ������
	return pop_back(arr, rows);
}
template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());	//T() - �������� �� ��������� ��� ���������� ����
		cols--;	//������������ ���������� ������ �� 1 �������
	}
	cols++;
}
template<typename T>void pop_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = pop_back(arr[i], cols);
		cols++;
	}
	cols--;
}
