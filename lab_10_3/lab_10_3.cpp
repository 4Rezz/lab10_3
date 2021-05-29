#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Goods
{
	char name[100];
	char shop[100];
	double price;
	double amount;
	char measurement[20];
};

void Create(char* fname);
void Print(char* fname);
void SortShop(char* fname);
bool SortPrice(char* fname, double min, double max);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char ch;
	double min, max;
	do
	{
		cout << endl;
		cout << "Головне меню:	" << endl;
		cout << "[1] - введення та збереження данних;" << endl;
		cout << "[2] - загрузка та вивід данних;" << endl;
		cout << "[3] - провести пошук по магазинам;" << endl;
		cout << "[4] - провести пошук по цінам;" << endl << endl;

		cout << "[0] - завершення роботи." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
				cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case '2':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case '3':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			SortShop(fname);
			break;
		case '4':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			cout << "Введіть мінімальну ціну(UAH): "; cin.sync(); cin >> min;
			cout << "Введіть максимальну ціну(UAH): "; cin.sync(); cin >> max;
			cout << endl;
			SortPrice(fname, min, max);
			break;
		default:
			cout << "Помилка вводу! ";
		}
	} while (ch != '0');
	return 0;
}

void Create(char* fname) // створення файлу з введених рядків
{
	ofstream fout(fname); // відкрили файл для запису
	char ch; // відповідь користувача – чи продовжувати введення
	string s; // введений користувачем рядок
	Goods goods;
	do
	{
		cout << "Назва товару: "; cin >> goods.name;
		cout << "Магазин: "; cin >> goods.shop;
		cout << "Ціна(UAH): "; cin >> goods.price;
		cout << "Кількість: "; cin >> goods.amount;
		cout << "Од. вимірювання: "; cin >> goods.measurement;
		if (!fout.write((char*)&goods, sizeof(Goods)))
		{
			cerr << "Помилка запису у файл." << endl;
		}
		cout << "Продовжити? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
	fout.close();
}

void Print(char* fname) // виведення файлу на екран
{
	ifstream fin(fname); // відкрили файл для зчитування
	if (fin.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	cout << endl;
	Goods goods;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
			cout << "| " << setw(2) << right << i + 1 << "  "; i++;
			cout << "|   " << setw(6) << left << goods.name
				<< "|   " << setw(6) << left << goods.shop << "  "
				<< "|   " << setw(5) << left << goods.price
				<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
				<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
			cout << endl;
		}
		cout << "========================================================================= "
			<< endl;
		cout << endl;
	cout << endl;
	fin.close();
}

void SortShop(char* fname) 
{
	ifstream fin(fname);
	if (fin.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	cout << endl;
	Goods goods;
	string store;
	int k = 0;
	cout << "Будь ласка, введіть назву магазину: "; cin.sync(); getline(cin, store);
	cout << endl;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
		if (goods.shop == store) {
			cout << "| " << setw(2) << right << i + 1 << "  "; i++;
			cout << "|   " << setw(6) << left << goods.name
				<< "|   " << setw(6) << left << goods.shop << "  "
				<< "|   " << setw(5) << left << goods.price
				<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
				<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
			cout << endl;
			k = 1;
		}
	}
	if (k == 0) {
		cout << "Нажаль, цей магазин не було знайдено. Будь ласка, перевірте правильність вводу." << endl;
	}
	cout << "========================================================================= "
		<< endl;
	cout << endl;
	cout << endl;
	fin.close();
}

bool SortPrice(char* fname, double min, double max)
{
	ifstream fin(fname);
	if (!fin)
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return false;
	}
	cout << endl;
	Goods goods;
	int k = 0;
	cout << "========================================================================="
		<< endl;
	cout << "|  №  |  Товар  |  Магазин  |  Ціна  |  Кількість  |  Од. вимірювання  |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (fin.read((char*)&goods, sizeof(Goods)))
	{
		if (goods.price >= min && goods.price <= max) {
			cout << "| " << setw(2) << right << i + 1 << "  "; i++;
			cout << "|   " << setw(6) << left << goods.name
				<< "|   " << setw(6) << left << goods.shop << "  "
				<< "|   " << setw(5) << left << goods.price
				<< setw(4) << "|     " << setw(6) << left << goods.amount << "  "
				<< setw(6) << "|       " << setw(12) << left << goods.measurement << "|";
			cout << endl;
			k = 1;
		}
	}
	if (k == 0) {
		cout << "Схоже, в цій ціновій категорії нічого не було знайдено. Будь ласка, введіть іншу цінову категорію і повторіть пошук." << endl;
		return false;
	}
	cout << "========================================================================= "
		<< endl;
	cout << endl;
	cout << endl;
	fin.close();
	return true;
}