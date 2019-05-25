#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <iostream>
#include "windows.h"
using namespace std;

class Worker
{
public:
	 string getsurname() { return m_initials; }
    string getInitials() { return m_initials; }
    string getPosition() { return m_position; }
    int getYearOfEmployment() { return m_year_of_employment; }

	void getsurname(const string surname) { m_surname = surname; }
    void getInitials(const string initials) { m_initials = initials; }
    void getPosition(const string position) { m_position = position; }
    void getYearOfEmployment(const int year_employment) { m_year_of_employment = year_employment; }

    Worker& operator = (const Worker& other);

    friend istream& operator >> (istream& in, Worker& worker);
    friend ostream& operator << (ostream& out, const Worker& worker);
private:
	string m_surname;
    string m_initials;
    string m_position;
    int m_year_of_employment;
};

Worker& Worker::operator = (const Worker& other)
{ 
	m_surname = other.m_surname;
    m_initials = other.m_initials;
    m_position = other.m_position;
    m_year_of_employment = other.m_year_of_employment;

    return (*this);
}

istream& operator >> (istream& in, Worker& worker)
{
	in >> worker.m_surname;
    in >> worker.m_initials;
    in >> worker.m_position;
    in >> worker.m_year_of_employment;

    return in;
}

ostream& operator << (ostream& out, const Worker& worker)
{
	out << worker.m_surname << ' ';
    out << worker.m_initials << ' ';
    out << worker.m_position << ' ';
    out << worker.m_year_of_employment << endl;

    return out;
}

#endif // WORKER_H
