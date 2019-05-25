#include "book.h"
#include <map>
#include <algorithm>

int main()
{
    multimap<string, Book> library;
    auto exit_flag = false;

    while (! exit_flag)
    {
        cout << endl;
        cout << "1. Insert new book info in a library" << endl;
        cout << "2. Display books sorted by author initials" << endl;        
        cout << "3. Exit" << endl << endl;

        cout << "Please enter menu number: ";
        char menu_number;
        cin >> menu_number;
        cout << endl;

        switch (menu_number)
        {
        case '1':
        {
            cout << "Insert new book info in a library" << endl;
            Book book;
            cout << "Please enter new book info:" << endl;
            cin >> book;
            pair<string, Book> book_info;
            book_info.first = book.getAuthorInitials();
            book_info.second = book;
            library.insert(book_info);
        }
            break;
       
        case '2':
        {
            cout << "Display books sorted by author initials" << endl;
            auto it = library.begin();
            auto eit = library.end();
            for (; it != eit; ++it)
            {
                cout << it->second;
            }
        }
            break;

        case '3':
            exit_flag = true;
            break;
        default:
            cout << "Wrong menu" << endl;
            break;
        }
    }

    system("pause");
    return 0;
}
