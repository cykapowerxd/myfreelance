#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include "windows.h"
using namespace std;

#define MAX_STRING_LEN 100 // максимальная длина строк в символах

int SelectItem(int n);
bool isDecStr(string s);

class StringObj
{
public:
	virtual const string& GetName() = 0;
	virtual const string& GetVal() = 0;
	virtual int GetSize() = 0;
	virtual void Show(void) = 0;
};

// класс Символьная строка (произвольная строка данных)
class Т1 : public StringObj
{
protected:
	string name; // имя объекта
	string value;// значение(данные) объекта
public:
	//конструктор по-умолчанию
	Т1() {	}
	Т1(string _name) :name(_name) {}// конструктор с параметром: имя объекта
	Т1(string _name, string _val) :name(_name), value(_val) {}// конструктор с двумя параметрами: имя и значение
	~Т1() {} // деструктор

	virtual const string& GetName() { return name; }
	virtual const string& GetVal() { return value; }
	virtual int GetSize() { return value.size(); }
	virtual void Show(void);
};


//Класс Десятичная строка (изображение десятичного числа)
class Т2 : public Т1
{
	int GetDecVal(void);
public:
	Т2();// конструктор
	Т2(string _name);// конструктор
	Т2(string _name, string _val);// конструктор
	void ShowBin(); //показ двоичного значения
	void ShowOct(); // показ восьмиричного значения
	void ShowHex(); // показ шестнадцатеричного значения
	virtual void Show(void);

};

void Т2::Show(void)
{
	cout << "BIN: "; ShowBin(); //показ двоичного значения
	cout << "OCT: "; ShowOct();// показ восьмиричного значения
	cout << "HEX: "; ShowHex();// показ шестнадцатеричного значения
}

int Т2::GetDecVal(void)
{
	int ival;

	ival = atoi(value.c_str());

	return ival;
}

// Класс организующий работу меню пользователя
class Factory
{
	vector <StringObj*> pObjects; // вектор указателей на объекты строк потомков StringObj
public:
	Factory() {		}
	void AddObject(void);
	void DeleteObject(void);
	void ListAllObjects();
	void ShowObject(void);

};

// функция вывода значения объекта на консоль
void Т1::Show(void)
{
	cout << value.c_str() << endl;
}



//фунция вывода на экран списка имен всех объектов
void Factory::ListAllObjects()
{
	int n = pObjects.size();
	cout << endl << "Список объектов: " << endl << "---------------------------" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << pObjects[i]->GetName() << endl;;
	}
	cout << "---------------------------" << endl;
}

void Factory::ShowObject(void)
{
	int item, n;

	n = pObjects.size();
	if (n == 0)
	{
		cout << "!!!!! В хранилище нет объектов." << endl;
		return;
	}

	cout << "Выберите номер объекта для показа значения:" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << (i + 1) << ":" << pObjects[i]->GetName() << endl;
	}

	item = SelectItem(n);
	cout << "Значение: " << endl;
	pObjects[item - 1]->Show();

}

// удаление объекта из хранилища
void Factory::DeleteObject(void)
{
	int item, n;

	n = pObjects.size();

	if (n == 0)
	{
		cout << "!!!!! В хранилище нет объектов." << endl;

		return;

	}
	cout << "------------------------------------" << endl;
	cout << "Выберите номер удаляемого объекта:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << (i + 1) << ":" << pObjects[i]->GetName() << endl;
	}



	item = SelectItem(n);
	item--;
	string name = pObjects[item]->GetName();

	pObjects.erase(pObjects.begin() + item);
	cout << "Объект < " << name << " > удален  из хранилища. " << endl;
}

//фунция добавления нового обекта в хранилище
void Factory::AddObject(void)
{
	int item;
	StringObj *pNewObj;

	string name, value;
	cout << "Выбирите тип добавляемого объекта:" << endl;
	cout << "1.Строка символов." << endl;
	cout << "2.Строка десятичная." << endl;
	item = SelectItem(2);

	cout << "Введите имя:";
	cin >> name;
	cin.get();

	cout << "Введите значение:";

	char buffer[MAX_STRING_LEN];

	cin.getline(buffer, MAX_STRING_LEN);
	value = buffer;
	switch (item)
	{
	case 1: pNewObj = new Т1(name, value);
		break;
	case 2: // проверяем на корректность значение строки
		if (isDecStr(value) == false)
		{
			cout << endl << "!!!!! Некорректное значение. Должны быть только цифры(0-9)." << endl;
			return;
		}
		pNewObj = new Т2(name, value);
		break;
	}// конец оператора switch


	pObjects.push_back(pNewObj);
	cout << "Объект успешно добавлен в хранилище." << endl;
}




// проверка значения строки на десятичное число
bool isDecStr(string s)
{
	const string digits = "0123456789";

	for (int i = 0; i < s.size(); i++)
	{
		if (digits.find_first_of(s[i]) == -1)// ищем вхождение в алфавит десятичных цифр
			return false;
	}
	return true;
}

//конструктор по-умолчанию
Т2::Т2() :Т1()
{

}
// конструктор
Т2::Т2(string _name) : Т1(_name)
{
}

// конструктор
Т2::Т2(string _name, string _val) : Т1(_name, _val)
{
}

//показ двоичного значения
void Т2::ShowBin()
{
	unsigned int iv;
	unsigned int mask;
	int shift;

	iv = GetDecVal(); //получаем десятичное значение записанное в строке

	mask = 1;
	shift = sizeof(mask) * 8; //вычисляем число бит 
	mask = mask << (shift - 1);

	// цикл по всем битам числа	
	for (int i = 0; i < shift; i++)
	{
		// определяем значение бита: 1 или 0
		if ((iv & mask) != 0) cout << '1';
		else cout << '0';
		iv = iv << 1;
	}

	cout << endl;
}

// показ восьмиричного значения
void Т2::ShowOct()
{

	unsigned int uiv;

	uiv = GetDecVal();//получаем десятичное значение записанное в строке

	cout.unsetf(ios::dec); // снятие флага вывода в десятичном формате
	cout.setf(ios::oct);  // установка флага вывода в восмеричном формате
	cout << uiv << endl;  // выводим значение в консоль

	cout.unsetf(ios::oct);// снятие флага вывода в восьмеричном формате
	cout.setf(ios::dec); // установка флага вывода в десятичном формате


}


// показ шестнадцатеричного значения
void Т2::ShowHex()
{

	unsigned int uiv;

	uiv = GetDecVal(); // получаем десятичное значение записаное в строке

	cout.unsetf(ios::dec); // снятие флага вывода в десятичном формате
	cout.setf(ios::hex);// установка флага вывода в шестнадцатиричном формате
	cout << uiv << endl;// выводим значение

	cout.unsetf(ios::hex);// снимаем флаг вывода в шестнадцатиричном формате
	cout.setf(ios::dec); // установка флага вывода в десятичном формате

}


//выбор пользователя в консоли
int SelectItem(int n)
{
	int item;
	while (true) // бесконечный цикл пока не введут верное значение
	{
		cin >> item;
		if ((item > 0 && item <= n) && (cin.peek() == '\n'))
		{
			cin.get();
			break; // выход из цикла
		}
		else
		{// ввели неверное значение
			cout << "Ошибочный выбор. Повторите ввод.(от 1 до " << n << "):" << endl;
			cin.clear();

			while (cin.get() != '\n') {}; // ждем нажатия клавиши Enter

		}
	}
	return item;
}



int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Factory factory;
	bool bQuit;
	int k;

	bQuit = false;

	while (!bQuit)
	{
		cout << "1.Добавить объект" << endl;
		cout << "2.Список всех объектов" << endl;
		cout << "3.Показать значение объекта" << endl;
		cout << "4.Удалить объект" << endl;
		cout << "5.Выход из программы" << endl;
		cout << endl;


		k = SelectItem(5);

		switch (k)
		{
		case 1: factory.AddObject(); break;
		case 2: factory.ListAllObjects(); break;
		case 3: factory.ShowObject(); break;
		case 4: factory.DeleteObject(); break;
		case 5: bQuit = true; break;

		}
		cout << endl;
	}

}