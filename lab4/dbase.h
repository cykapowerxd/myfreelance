#ifndef DBASE_H
#define DBASE_H

#include <ctime>
#include "worker.h"

class DBase
{
public:
    DBase(int);
    ~DBase();
    void InitInput();
    void Show();
    void ShowObjectsWithExperienceMoreThan(const int experience);
private:
    Worker* m_workers;
    int nRecords;
};

DBase::DBase(int nRec)
    : m_workers(new Worker[nRec])
    , nRecords(nRec)
{}

DBase::~DBase() { if (m_workers) delete [] m_workers; }

void DBase::InitInput()
{
    cout << "\nInput values in format: " << endl;
    cout << "Worker surname, initials, position, year of employment" << endl;
    for (auto i = 0; i < nRecords; ++i)
    {
        cout << (i + 1) << ". ";
        cin >> m_workers[i];
    }

    for (auto i = 0; i < nRecords - 1; ++i)      //алфавитный порядок
    {
        for (auto j = 0; j < nRecords - i - 1; ++j)
        {
            if (m_workers[j].getInitials() > m_workers[j + 1].getInitials())
            {
                auto temp = m_workers[j];
                m_workers[j] = m_workers[j + 1];
                m_workers[j + 1] = temp;
            }
        }
    }
}

void DBase::Show()
{
    cout << "=========================" << endl;
    cout << "Show content:" << endl;
    for (auto i = 0; i < nRecords; ++i)
    {
        cout << (i + 1) << ". " << m_workers[i] << endl;
    }
}

void DBase::ShowObjectsWithExperienceMoreThan(const int experience)
{
    auto not_found = true;
    cout << "\nShow items with experience most than " << experience << endl;
	system("pause");

    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);

    auto current_year = 1900 + timePtr->tm_year;

    for (auto i = 0; i < nRecords; ++i)
    {
        if (experience < current_year - m_workers[i].getYearOfEmployment())
        {
            cout << m_workers[i];
            not_found = false;
        }
    }

    if (not_found)
    {
        cout << "Workers not found" << endl;
		system("pause");
    }
}

#endif // DBASE_H
