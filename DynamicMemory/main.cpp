#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

//Динамические массивы
//Динамическим называется массив, массив которого можно задать переменным значением на этапе выполнения программы.
//Для объявления динамического массива нужно объявить указатель и выделить память при помощи оператара "new"
//Оператор new выделяет непрерывный блок памяти для n элементов заданного типа. И возвращает адрес выделенной памяти. Этот адрес записываем в указатель arr.
//Оператор new запрашивает память операционной системы. После использования эту память нужно вернуть обратно. Это делает оператор delete
//Он освобождает память, выделенную оператором new и возрващает ее обратно системе. 
// Если не вернуть память ОС то произойдет утечка памяти (memory leak) Если утечки памяти происходят постоянно то рано или поздно вся свободная память заполнится. 
// Оператор delete должен быть вызван столько раз, сколько был вызван new. 
//Обращаться к элементам динамич массива можно так же как к элементам статического. Через арифметику указателей и оператор наименования или через оператор индексирования. 
//Одна и та же функция может работать как со статическими так и с динамическими массивами. 
// В динамич массив можно добавлять элементы. Это требует перееопределения памяти. Нужно выделить новую область памяти нужного размера, скопировать туда все значения из исходного массива, 
// Только после этого в конце массива свободный элемент, в который можно добавить значение.

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
	cout << "Введите размер массива: "; cin >> n;
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
	cout << "Введите добавляемое значение: "; cin >> value;

	arr = push_back(arr, n, value);

	//7) Значение добавлено, проверяем результат:
	Print(arr, n);


	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	Print(arr = pop_back(arr, n), n);
	

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	typedef double DataType;	//сущестующему типу данных дает второе имя

	//1) Создаем массив указателей:
	char** arr = Allocate<char>(rows, cols);

	/*cout << "Память выделена, для добавления столбца";
	system("PAUSE");

	push_col_back(arr, rows, cols);

	cout << "Столбец добавлен" << endl;*/

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//int   - 'int';
	//int*  - Указатель на 'int';
	//int** - Указатель на указатель на 'int';

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
//ПРИМЕЧАНИЕ : ПРИ ПЕРЕДАЧЕ УКАЗАТЕЛЯ В ФУНКЦИЮ СЛЕДУЕТ УЧИТЫВАТЬ ЧТО ИМЕННО СКОПИРУЕТСЯ В ФУНКЦИЮ. АДРЕС УКАЗАТЕЛЯ ИЛИ АДРЕС В УКАЗАТЕЛЕ. 

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

	//1) Создаем буферный массив нужного размера:
	T* buffer = new T[n + 1];

	//2) Копируем все содержимое исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив:
	delete[] arr;

	//4) Подменяем адрес в указателе 'arr' адресом нового массива:
	arr = buffer;

	//5) Только после всего этого в конце массива появляется элемент, 
	//	 в который можно сохранить добавляемое значение:
	arr[n] = value;

	//6) После того как в массив добавился элемент, 
	//	 количество его элементов увеличивается на 1:
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
	delete[] arr[rows - 1];	//Удаление строки
	return pop_back(arr, rows);
}
template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());	//T() - значение по умолчанию для шаблонного типа
		cols--;	//компенсируем увеличение строки на 1 элемент
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
