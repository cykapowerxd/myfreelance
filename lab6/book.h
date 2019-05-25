#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <istream>
#include <string>

using namespace std;

class Book
{
public:
    string getAuthorInitials() const { return m_author_initials; }
    int getPublishYear() const { return m_publish_year; }

    friend istream& operator >> (istream& in, Book& book);
    friend ostream& operator << (ostream& out, const Book& book);

private:
    string m_author_initials;
    string m_name;
    int m_publish_year;
    int m_number_of_copies;
};

istream& operator >> (istream& in, Book& book)
{
    cout << "\nNew book info: " << endl;
    cout << "Author initials: ";
    in >> book.m_author_initials;
    cout << "Book name: ";
    in >> book.m_name;
    cout << "Publishing year: ";
    in >> book.m_publish_year;
    cout << "Number of copies: ";
    in >> book.m_number_of_copies;

    return in;
}

ostream& operator << (ostream& out, const Book& book)
{
    cout << "\nAuthor initials: ";
    out << book.m_author_initials << endl;
    cout << "Book name: ";
    out << book.m_name << endl;
    cout << "Publishing year: ";
    out << book.m_publish_year << endl;
    cout << "Number of copies: ";
    out << book.m_number_of_copies << endl;

    return out;
}

#endif // BOOK_H
