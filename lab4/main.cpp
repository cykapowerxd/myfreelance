#include "dbase.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    const int nRecord = 10;

    DBase dbase(nRecord);
    dbase.InitInput();
    dbase.Show();

    int experience;
    cout << "Please input experience: ";
    cin >> experience;
    dbase.ShowObjectsWithExperienceMoreThan(experience);
	system("pause");

    return 0;
}
