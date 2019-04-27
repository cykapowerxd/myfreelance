#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include "windows.h"
using namespace std;

#define MAX_STRING_LEN 100 // ������������ ����� ����� � ��������

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

// ����� ���������� ������ (������������ ������ ������)
class �1 : public StringObj
{
protected:
	string name; // ��� �������
	string value;// ��������(������) �������
public:
	//����������� ��-���������
	�1() {	}
	�1(string _name) :name(_name) {}// ����������� � ����������: ��� �������
	�1(string _name, string _val) :name(_name), value(_val) {}// ����������� � ����� �����������: ��� � ��������
	~�1() {} // ����������

	virtual const string& GetName() { return name; }
	virtual const string& GetVal() { return value; }
	virtual int GetSize() { return value.size(); }
	virtual void Show(void);
};


//����� ���������� ������ (����������� ����������� �����)
class �2 : public �1
{
	int GetDecVal(void);
public:
	�2();// �����������
	�2(string _name);// �����������
	�2(string _name, string _val);// �����������
	void ShowBin(); //����� ��������� ��������
	void ShowOct(); // ����� ������������� ��������
	void ShowHex(); // ����� ������������������ ��������
	virtual void Show(void);

};

void �2::Show(void)
{
	cout << "BIN: "; ShowBin(); //����� ��������� ��������
	cout << "OCT: "; ShowOct();// ����� ������������� ��������
	cout << "HEX: "; ShowHex();// ����� ������������������ ��������
}

int �2::GetDecVal(void)
{
	int ival;

	ival = atoi(value.c_str());

	return ival;
}

// ����� ������������ ������ ���� ������������
class Factory
{
	vector <StringObj*> pObjects; // ������ ���������� �� ������� ����� �������� StringObj
public:
	Factory() {		}
	void AddObject(void);
	void DeleteObject(void);
	void ListAllObjects();
	void ShowObject(void);

};

// ������� ������ �������� ������� �� �������
void �1::Show(void)
{
	cout << value.c_str() << endl;
}



//������ ������ �� ����� ������ ���� ���� ��������
void Factory::ListAllObjects()
{
	int n = pObjects.size();
	cout << endl << "������ ��������: " << endl << "---------------------------" << endl;
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
		cout << "!!!!! � ��������� ��� ��������." << endl;
		return;
	}

	cout << "�������� ����� ������� ��� ������ ��������:" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << (i + 1) << ":" << pObjects[i]->GetName() << endl;
	}

	item = SelectItem(n);
	cout << "��������: " << endl;
	pObjects[item - 1]->Show();

}

// �������� ������� �� ���������
void Factory::DeleteObject(void)
{
	int item, n;

	n = pObjects.size();

	if (n == 0)
	{
		cout << "!!!!! � ��������� ��� ��������." << endl;

		return;

	}
	cout << "------------------------------------" << endl;
	cout << "�������� ����� ���������� �������:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << (i + 1) << ":" << pObjects[i]->GetName() << endl;
	}



	item = SelectItem(n);
	item--;
	string name = pObjects[item]->GetName();

	pObjects.erase(pObjects.begin() + item);
	cout << "������ < " << name << " > ������  �� ���������. " << endl;
}

//������ ���������� ������ ������ � ���������
void Factory::AddObject(void)
{
	int item;
	StringObj *pNewObj;

	string name, value;
	cout << "�������� ��� ������������ �������:" << endl;
	cout << "1.������ ��������." << endl;
	cout << "2.������ ����������." << endl;
	item = SelectItem(2);

	cout << "������� ���:";
	cin >> name;
	cin.get();

	cout << "������� ��������:";

	char buffer[MAX_STRING_LEN];

	cin.getline(buffer, MAX_STRING_LEN);
	value = buffer;
	switch (item)
	{
	case 1: pNewObj = new �1(name, value);
		break;
	case 2: // ��������� �� ������������ �������� ������
		if (isDecStr(value) == false)
		{
			cout << endl << "!!!!! ������������ ��������. ������ ���� ������ �����(0-9)." << endl;
			return;
		}
		pNewObj = new �2(name, value);
		break;
	}// ����� ��������� switch


	pObjects.push_back(pNewObj);
	cout << "������ ������� �������� � ���������." << endl;
}




// �������� �������� ������ �� ���������� �����
bool isDecStr(string s)
{
	const string digits = "0123456789";

	for (int i = 0; i < s.size(); i++)
	{
		if (digits.find_first_of(s[i]) == -1)// ���� ��������� � ������� ���������� ����
			return false;
	}
	return true;
}

//����������� ��-���������
�2::�2() :�1()
{

}
// �����������
�2::�2(string _name) : �1(_name)
{
}

// �����������
�2::�2(string _name, string _val) : �1(_name, _val)
{
}

//����� ��������� ��������
void �2::ShowBin()
{
	unsigned int iv;
	unsigned int mask;
	int shift;

	iv = GetDecVal(); //�������� ���������� �������� ���������� � ������

	mask = 1;
	shift = sizeof(mask) * 8; //��������� ����� ��� 
	mask = mask << (shift - 1);

	// ���� �� ���� ����� �����	
	for (int i = 0; i < shift; i++)
	{
		// ���������� �������� ����: 1 ��� 0
		if ((iv & mask) != 0) cout << '1';
		else cout << '0';
		iv = iv << 1;
	}

	cout << endl;
}

// ����� ������������� ��������
void �2::ShowOct()
{

	unsigned int uiv;

	uiv = GetDecVal();//�������� ���������� �������� ���������� � ������

	cout.unsetf(ios::dec); // ������ ����� ������ � ���������� �������
	cout.setf(ios::oct);  // ��������� ����� ������ � ����������� �������
	cout << uiv << endl;  // ������� �������� � �������

	cout.unsetf(ios::oct);// ������ ����� ������ � ������������ �������
	cout.setf(ios::dec); // ��������� ����� ������ � ���������� �������


}


// ����� ������������������ ��������
void �2::ShowHex()
{

	unsigned int uiv;

	uiv = GetDecVal(); // �������� ���������� �������� ��������� � ������

	cout.unsetf(ios::dec); // ������ ����� ������ � ���������� �������
	cout.setf(ios::hex);// ��������� ����� ������ � ����������������� �������
	cout << uiv << endl;// ������� ��������

	cout.unsetf(ios::hex);// ������� ���� ������ � ����������������� �������
	cout.setf(ios::dec); // ��������� ����� ������ � ���������� �������

}


//����� ������������ � �������
int SelectItem(int n)
{
	int item;
	while (true) // ����������� ���� ���� �� ������ ������ ��������
	{
		cin >> item;
		if ((item > 0 && item <= n) && (cin.peek() == '\n'))
		{
			cin.get();
			break; // ����� �� �����
		}
		else
		{// ����� �������� ��������
			cout << "��������� �����. ��������� ����.(�� 1 �� " << n << "):" << endl;
			cin.clear();

			while (cin.get() != '\n') {}; // ���� ������� ������� Enter

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
		cout << "1.�������� ������" << endl;
		cout << "2.������ ���� ��������" << endl;
		cout << "3.�������� �������� �������" << endl;
		cout << "4.������� ������" << endl;
		cout << "5.����� �� ���������" << endl;
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