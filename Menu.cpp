/******************************
 * Author: Charles Bennett
 * Date: 3/9/15
 * Description: This program utilizes the Book, Patron, and Library classes to simulate a library. The menu provided in the program has options for each of the functions in the library class.
 * ***************************/
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  // Declare variables
  string bookID,
         patronID;
  double payment;
  int selection;
  Library lib;

  cout << endl;
  cout << "Welcome to the library!" << endl;
  cout << "Use the menu to navigate the library." << endl;
  cout << endl;

  // MENU
  do
  {
    cout << "Please select one of the following options:" << endl;
    cout << "1. Add a book to the library" << endl;
    cout << "2. Add a patron to the library" << endl;
    cout << "3. Check out a book" << endl;
    cout << "4. Return a book" << endl;
    cout << "5. Request a book to be put on hold" << endl;
    cout << "6. Pay fine" << endl;
    cout << "7. View patron info" << endl;
    cout << "8. View book info" << endl;  
    cout << "9. Increment the date" << endl;
    cout << "0. Exit the program" << endl; 
    cin >> selection; 

    switch(selection)
    {
      case 1: // Add Book 
        lib.addBook();
        break;
      case 2: // add patron
        lib.addMember();
        break;
      case 3: // check out book
        cout << endl;
        cout << "Please input the ID number of the patron whom is checking out the book." << endl;
        cin.ignore(1000,'\n');
        getline(cin,patronID);
        cout << "Please input the ID code of the book." << endl;
        getline(cin,bookID);
        lib.checkOutBook(patronID, bookID);
        break;
      case 4: // return book 
        cout << endl;
        cout << "Please input the ID code of the book you wish to return." << endl; 
        cin.ignore(1000,'\n');
        getline(cin,bookID);
        lib.returnBook(bookID);
        break;
      case 5: // place book on hold 
        cout << endl;
        cout << "Please input the ID number of the patron whom is requesting the book." << endl;
        cin.ignore(1000,'\n');
        getline(cin,patronID);
        cout << "Please input the ID code of the book." << endl;
        getline(cin,bookID);
        lib.requestBook(patronID, bookID);
        break;   
      case 6: // pay fine
        cout << endl;
        cout << "Please input the ID number of the patron whom is paying their fine." << endl;
        cin.ignore(1000,'\n');
        getline(cin,patronID); 
        cout << "Please input the amount the patron is paying towards the fine." << endl;
        cin >> payment;
        lib.payFine(patronID,payment);
        break;
      case 7: // view patron info
        cout << endl;
        cout << "Please input the ID number of the patron whose info you wish to view." << endl;
        cin.ignore(1000,'\n');
        getline(cin,patronID); 
        lib.viewPatronInfo(patronID);
        break;
      case 8: // view book info
        cout << endl;
        cout << "Please input the ID code of the book you wish to view." << endl;
        cin.ignore(1000,'\n');
        getline(cin,bookID); 
        lib.viewBookInfo(bookID);
        break;
      case 9: // increment date 
        lib.incrementCurrentDate();
        break;
      case 0: // Say goodbye!
        cout << endl;
        cout << "Goodbye!" << endl << endl;
        break;
    }
  } while (selection!=0);
 
  return 0;
}   
