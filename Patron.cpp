/************************************
 * Author: Charles Bennett
 * Date: 3/8/15
 * Description: The Patron class is used to create Patron objects, which include their id number and name.  The class is also used to store which books a Patron has checked out and how much their fines are on those books if they have had them checked out more than 21 days.
 * *********************************/
#include "Patron.hpp"
#include "Book.hpp"
#include <string>
#include <vector>

using namespace std;

// Default constructor
Patron::Patron()
{
}

// Overloaded constructor
Patron::Patron(string idn, string n)
{
  setIdNum(idn);
  setName(n);
  setFineAmount(0.00);
  checkedOutBooks.reserve(100);  
}

// setIdNum(string)
void Patron::setIdNum(string idn)
{
  idNum=idn;
}

// getIdNum
string Patron::getIdNum()
{
  return idNum;
}

// setName(string)
void Patron::setName(string n)
{
  name=n;
}

// getName()
string Patron::getName()
{
  return name;
}

// getCheckedOutBooks
vector<Book*> Patron::getCheckedOutBooks()
{
  return checkedOutBooks;
}

/*******************************
 *        addBook              *
 *Description: adds a book to  *
   the book vector             *
  Parameter: book pointer      *
*******************************/           
void Patron::addBook(Book* b)
{
  checkedOutBooks.push_back(b);
}

/*******************************
 *       removeBook            *
 *Description: checks if a book
   is present in the book vect
   or then removes it
  Parameter: book pointer      *
*******************************/       
void Patron::removeBook(Book* b)
{
  for(int i=0; i<checkedOutBooks.size(); i++)
  {
    if(checkedOutBooks[i]==b)
    {
      checkedOutBooks.erase(checkedOutBooks.begin()+i);
      return;
    }
    else
    {
      continue;
    }
  }
}

// setFineAmount(double)
void Patron::setFineAmount(double f)
{
  fineAmount=f;
}

// getFineAmount
double Patron::getFineAmount()
{
  return fineAmount;
}

// amendFine(double)
void Patron::amendFine(double amount)
{
  fineAmount+=amount;
}
