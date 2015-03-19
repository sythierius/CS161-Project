/*******************************
 * Author: Charles Bennett
 * Date: 3/8/15
 * Description: The library class combines the book and patron classes to make a list of all members and all books. There are functions to add books, add members, check out books, return books, request books, pay fines, increment the date, view patron, and view book.
 * *****************************/
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Constructor
Library::Library()
{
  holdings.reserve(100);
  members.reserve(100);
  currentDate=0;
}

/********************************
 *          findBook            *
 *Description: Locates a book in
   holdings, then returns the 
    location of that book       *
  Parameter: string             *
********************************/          
Book* Library::findBook(string bookID)
{
  for (int i=0; i<holdings.size(); i++)
  {
    if(holdings[i].getIdCode()==bookID)
    {
      return &holdings[i]; // return location of the book
    }
  }

  return NULL;
} 

/*********************************
 *         findPatron            *
 *Description: Locates a patron 
   in members, then returns the 
   location of that patron
  parameter: string              *
*********************************/        
Patron* Library::findPatron(string patronID)
{
  for (int i=0; i<members.size(); i++)
  {
    if(members[i].getIdNum()==patronID)
    {
      return &members[i]; // return location of the patron
    }
  }

  return NULL;
}      

/**********************************
 *           addBook              *
 *Description: allows the user to *
   add a book to the library
  Parameter: none                 *
**********************************/           
void Library::addBook()
{
  string id,
         title,
         author; 
  
  cin.ignore(1000, '\n');

  // Prompt for ID code
  cout << endl;
  cout << "Adding a book to the library..." << endl;
  cout << "Please input the ID code of the book." << endl; 
  getline(cin, id); 

  // Check if book exists
  if(findBook(id)!=NULL)
  {
    cout << endl;
    cout << "ID code is already in use. Returning to menu." << endl << endl;  
    return;
  }
  
  // Prompt for other info
  cout << "Please input the title of the book." << endl;
  getline(cin, title);
  cout << "Please input the author of the book." << endl;
  getline(cin, author);

  // Add book to holdings vector
  holdings.push_back(Book(id,title,author));
  cout << endl; 
}

/****************************************
 *           addMember                  *
 *Description: Allows user to add a 
   patron to the library
  Parameter: none                       *
****************************************/          
void Library::addMember()
{
  string id,
         name;

  cin.ignore(1000,'\n');
  
  // Ask for patron ID
  cout << endl;
  cout << "Adding a patron to the library..." << endl;
  cout << "Please input the ID number of the patron." << endl;
  getline(cin, id);
  
  // Check if patron is in members vector 
  if(findPatron(id)!=NULL)
  {
    cout << endl;
    cout << "ID number is already in use. Returning to menu." << endl << endl;
    return;
  }
  
  // input name of patron
  cout << "Please input the name of the patron." << endl;
  getline(cin, name);
  
  // add patron to members vector
  members.push_back(Patron(id,name));
  cout << endl;
}  

/******************************************
 *            checkOutBook                *
 *Description: allows a patron to check 
   out a book if that book is not already
   on hold by another patron or checked out
  Parameters: string, string              *
******************************************/            
void Library::checkOutBook(string patronID, string bookID)
{
  Patron* pat; 
  Book* book;

  // Create pointer to book if it is found in holdings
  if(findBook(bookID)!=NULL)
  {
    book=findBook(bookID);
  }
  else 
  {
    cout << endl;
    cout << "The book ID code does not match any books on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // Create pointer to patron if it is found in members
  if(findPatron(patronID)!=NULL)
  {
    pat=findPatron(patronID);
  }
  else
  {
    cout << endl;
    cout << "The patron ID number does not match any members on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }
  
  // Check if book is checked out
  if(book->getLocation()==CHECKED_OUT)
  {
    cout << endl;
    cout << "The book is already checked out and is unavailable." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl; 
    return;
  }
  
  // Check if book is on hold by somebody else
  if((book->getLocation()==ON_HOLD_SHELF || book->getLocation()==CHECKED_OUT) && book->getRequestedBy() != pat)
  {
    cout << endl;
    cout << "The book is currently on hold by another person." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }
 
  // Check out book if tests are passed
  book->setCheckedOutBy(pat);
  book->setDateCheckedOut(currentDate);
  book->setLocation(CHECKED_OUT);
 
  // Reset hold status of book if the patron had it on hold
  if(book->getRequestedBy()== pat)
  {
    book->setRequestedBy(NULL);
  }
  pat->addBook(book);
 
  cout << endl;
  cout << book->getTitle() << " has been checked out by ";
  cout << pat->getName() << "." << endl;
  cout << endl;  
}     

/*****************************************
 *            returnBook                 *
 *Description: returns a book to holdings
    if that book is checked out          *
  Parameter: string                      *
*****************************************/            
void Library::returnBook(string bookID)
{
  Book* book;

  // Create book pointer if book is found in holdings
  if(findBook(bookID)!=NULL)
  {
    book=findBook(bookID);
  }
  else
  {
    cout << endl;
    cout << "The book ID code does not match any books on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }
  
  // Check if book is checked out     
  if(book->getLocation()!=CHECKED_OUT)
  {
    cout << endl;
    cout << "That book is currently not checked out by anyone." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
  }
  
  // Place the book back on the shelf
  book->getCheckedOutBy()->removeBook(book);
  if(book->getRequestedBy()==NULL)  
    book->setLocation(ON_SHELF);
  else
    book->setLocation(ON_HOLD_SHELF); // if on hold, place on hold shelf instead
  book->setCheckedOutBy(NULL);
  
  cout << endl;
  cout << book->getTitle() << " has been returned to the library." << endl << endl; 
} 

/*************************************
 *          requestBook              *
 *Description: Allows a patron to put*
   a book on hold if it is available *
   Parameter: string,string          *
*************************************/           
void Library::requestBook(string patronID, string bookID)
{
  Patron* pat;
  Book* book;
  vector<Book*> booksHeld;

  // Check if book exists in holdings
  if(findBook(bookID)!=NULL)
  {
    book=findBook(bookID);
  }
  else
  {
    cout << endl;
    cout << "The book ID code does not match any books on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // Check if patron exists in members
  if(findPatron(patronID)!=NULL)
  {
    pat=findPatron(patronID);
  }
  else
  {
    cout << endl;
    cout << "The patron ID number does not match any members on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // Check if book is already requested by somebody else
  if(book->getRequestedBy()!=NULL)
  {
    cout << endl;
    cout << "The book is already being requested by somebody else." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // Make a vector of the books in the patrons possession
  booksHeld=pat->getCheckedOutBooks();
  
  // Check the books in the patron's possession for the book they wish to put on hold
  for (int i=0; i<booksHeld.size(); i++)
  {
    if(booksHeld[i]->getIdCode()==bookID)
    {
      cout << endl;
      cout << "The patron already has the book in his possession, so it cannot be requested." << endl;
      cout << "Returning to menu..." << endl;
      cout << endl;
      return; 
    }
  }

  // Place to book on hold if checks are passed
  book->setRequestedBy(pat);
  if(book->getLocation()==ON_SHELF)
  {
    book->setLocation(ON_HOLD_SHELF);
  }
  
  cout << endl;
  cout << book->getTitle() << " has been successfully requested by ";
  cout << pat->getName() << "." << endl;
  cout << endl;
}

/**************************************
 *             payFine                *
 *Description: deducts an amount from
   a patron's total fines             *
  Parameters: string, double          *
**************************************/            
void Library::payFine(string patronID, double payment)
{
  Patron* pat;

  // Check if patron exists in members
  if(findPatron(patronID)!=NULL)
  {
    pat=findPatron(patronID);
  }
  else
  {
    cout << endl;
    cout << "The patron ID number does not match any members on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // Make the payment
  pat->amendFine(-payment);

  cout << fixed << setprecision(2) << endl;
  cout << "A payment of $" << payment << " has been made to ";
  cout << pat->getName() << "'s account." << endl;
  cout << "New Fine Balance: $" << pat->getFineAmount() << endl;
  cout << endl;  
} 

/*******************************************
 *             incrementCurrentDate        *
 *Description: adds 1 to the current date  *
   and updates any fines for books
  Parameters: none      
 ******************************************/       
void Library::incrementCurrentDate()
{
  // increment the date
  currentDate++;
  
  // apply fines for each book in the library if applicable 
  for (int i=0; i<holdings.size(); i++)
  {
    if ((currentDate-(holdings[i].getDateCheckedOut()))>(Book::CHECK_OUT_LENGTH))
    {
      holdings[i].getCheckedOutBy()->amendFine(.10);
    }
  }

  cout << endl << "The date has been incremented to " << currentDate << "." << endl << endl;
}

/***********************************************
 *               viewPatronInfo                *
 *Description: Prints all available information
   about a patron to the screen                *
  Parameter: string                            *
***********************************************/               
void Library::viewPatronInfo(string patronID)
{
  Patron* pat;
  vector<Book*> booksHeld;

  // Find the patron in the system
  if(findPatron(patronID)!=NULL)
  {
    pat=findPatron(patronID);
    booksHeld=pat->getCheckedOutBooks(); //make vector to hold the books in the patron's possession
  }
  else
  {
    cout << endl;
    cout << "The patron ID number does not match any members on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }
  
  // Print patron's name and ID
  cout << endl;
  cout << "Patron ID: " << pat->getIdNum() << endl;
  cout << "Name: " << pat->getName() << endl;
 
  // Print the books held by the patron
  cout << "Books checked out:" << endl;
  if (booksHeld.size()==0)
  {
    cout << "  (No books have been checked out)" << endl;
  }
  for (int i=0; i<booksHeld.size();i++)
  {
    cout << "  " << booksHeld[i]->getTitle() << endl;
  }
  // Print fines owed
  cout << fixed << setprecision(2);
  cout << "Amount owed in fines: $" << pat->getFineAmount() << endl;
  cout << endl; 
}

/****************************************
 *               viewBookInfo           *
 *Description: Prints all available
    book info to the screen             *
  Parameter: string                     *
****************************************/                    
void Library::viewBookInfo(string bookID)
{
  Book* book;
  string locationStr,
         requestedStr,
         checkedStr;
 
  // Find the book in holdings
  if(findBook(bookID)!=NULL)
  {
    book=findBook(bookID);
  }
  else
  {
    cout << endl;
    cout << "The book ID code does not match any books on record." << endl;
    cout << "Returning to menu..." << endl;
    cout << endl;
    return;
  }

  // If on shelf
  if(book->getLocation()==ON_SHELF)
  {
    locationStr="On Shelf";
    requestedStr="(Not on Hold)";
    checkedStr="(Not Checked Out)";
  }
  
  // If on hold, say who has it on hold
  if(book->getLocation()==ON_HOLD_SHELF)
  {
    locationStr="On Hold Shelf";
    requestedStr=book->getRequestedBy()->getName();
    checkedStr="(Not Checked Out)";
  }
 
  // If checked out, say if someone has it on hold as well
  if(book->getLocation()==CHECKED_OUT)
  {
    locationStr="Checked Out";
    if (book->getRequestedBy()!=NULL)
    {
      requestedStr=book->getRequestedBy()->getName();
    }
    else
    {
      requestedStr="(Not on Hold)";
    }
    checkedStr=book->getCheckedOutBy()->getName();
  } 

  // Print book info
  cout << endl;
  cout << "Book ID: " << book->getIdCode() << endl;
  cout << "Title: " << book->getTitle() << endl;
  cout << "Author: " << book->getAuthor() << endl;
  cout << "Location: " << locationStr << endl;
  cout << "Requested by: " << requestedStr << endl; 
  cout << "Checked out by: " << checkedStr << endl;
  cout << endl;
} 
