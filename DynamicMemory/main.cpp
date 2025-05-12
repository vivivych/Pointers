#include<iostream>
using namespace std;

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
void Print(int arr[], const int n);
int* push_back(int arr[], int& n, const int value);
int* push_front(int arr[], int& n, const int value);
int* insert(int arr[], int& n, const int value, int index);
int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);
int* erase(int arr[], int& n, int index);

void main()

{
	setlocale(LC_ALL, "");

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
}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;

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
