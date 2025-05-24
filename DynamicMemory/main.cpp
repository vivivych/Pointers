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


void FillRand(int arr[], const int n);
int** Allocate(int rows, int cols);
void FillRand(int** arr, const int rows, const int cols);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);


int* push_back(int arr[], int& n, const int value);
int* push_front(int arr[], int& n, const int value);
int* insert(int arr[], int& n, const int value, int index);
int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);
int* erase(int arr[], int& n, int index);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
int** push_row_front(int** arr, int& rows, int cols);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);
int** pop_row_front(int** arr, int& rows, int cols);
void push_col_back(int** arr, const int rows, int& cols);
void push_col_front(int** arr, int rows, int& cols);
template<typename T> void pop_col_back(T** arr, const int rows, int& cols);
template<typename T> void pop_col_front(T** arr, int rows, int& cols);

void Clear(int**& arr, int rows);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2
void main()

{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива : "; cin >> n;
	int* arr = new int[n];
	
	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение :"; cin >> value;

	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение :"; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого значения : "; cin >> index;
	cout << "Введите добавляемое значение :"; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);
	cout << "Удаление последнего элемента : " << endl;
	Print(arr = pop_back(arr, n), n);
	cout << "Удаление нулевого элемента : " << endl;
	Print(arr = pop_front(arr, n), n);
	cout << "Введите индекс удаляемого значения : "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
#endif DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_front(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_front(arr, rows, cols);
	Print(arr, rows, cols);

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	arr = pop_row_front(arr, rows, cols);
	Print(arr, rows, cols);

	pop_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	pop_col_front(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);

#endif
}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;

	}
}
int** Allocate(int rows, int cols)
{
	int** arr = new int* [rows];

	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;
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

void Print(int arr[], const int n)
{	
	for (int i = 0; i < n; i++)
	{

		cout << arr[i] << "\t";

	}
	cout << endl;
}

void Print(int** arr, const int rows, const int cols)
{
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


int* push_back(int arr[], int& n, const int value)
{

	int* buffer = new int[n + 1];

	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];

	}
	delete[] arr;
	arr = buffer;

	arr[n] = value;
	n++;
	return arr;
}
int* push_front(int arr[], int& n, const int value)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}
int* insert(int arr[], int& n, const int value, int index)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < index; i++)
		buffer[i] = arr[i];
	for (int i = index; i < n; i++)
		buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i + 1];
	}
	delete[] arr;
	return buffer;
}

int* erase(int arr[], int& n, int index)
{
	int* buffer = new int[n - 1];
	for (int i = 0; i < index; i++)
		buffer[i] = arr[i];
	for (int i = index + 1; i < n; i++)
		buffer[i - 1] = arr[i];
	delete[] arr;
	n--;
	return buffer;

}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{

	T** buffer = new T* [rows + 1];

	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}

	delete[] arr;

	//4) Создаем добавляемую строку, и записываем ее адрес в массив указателей:
	buffer[rows] = new T[cols] {};

	//5) При добавлении в массив строки, количество его строк увеличивается на 1:
	rows++;

	//6) Возвращаем новый массив на место вывоза:
	return buffer;
}

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	T** buffer = new T* [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr[rows];	//Удаление строки
	delete[] arr;		//Удаление массива указателей
	return buffer;
}

int** pop_row_front(int** arr, int& rows, int cols)
{
	int** buffer = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i + 1];
	}
	delete[] arr;
	rows--;
	return buffer;
}



int** push_row_front(int** arr, int& rows, int cols)
{
	int** buffer = new int* [rows + 1];

	for (int i = 0; i < rows; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = new int[cols] {};
	rows++;
	return buffer;
}

void push_col_front(int** arr, int rows, int& cols)
{

	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1];
		buffer[0] = 0;
		for (int j = 0; j < cols; j++)
		{
			buffer[j + 1] = arr[i][j];
		}
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
	
}


void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}

template<typename T> void pop_col_back(T** arr, const int rows, int& cols)
{
	cols--;
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols];
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
}

template<typename T> void pop_col_front(T** arr, int rows, int& cols)
{
	cols--;
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols];
		for (int j = 0; j < cols; j++)
		{
			buffer[j] = arr[i][j + 1];
		}
		delete[] arr[i];
		arr[i] = buffer;
	}
	
}

void Clear(int**& arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	delete[] arr;
}

