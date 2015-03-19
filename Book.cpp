/*********************************
 * Author: Charles Bennett
 * Date: 3/8/15
 * Description: The Book class is used for creating book objects, which include a unique id code, a name, and an author. It also is used to set who the book is checked out or requested by and how long it has been checked out, as well as the location of the book. 
 * *******************************/
#include "Book.hpp"
#include <string>

using namespace std;

// Default Constructor
Book::Book()
{
}

// Overloaded constructor
Book::Book(string idc, string t, string a)
{
  setIdCode(idc);
  setTitle(t);
  setAuthor(a);
  setCheckedOutBy(NULL);
  setRequestedBy(NULL);
  setLocation(ON_SHELF);
}

// setIdCode(string)
void Book::setIdCode(string idc)
{
  idCode=idc;
}

// getIdCode
string Book::getIdCode()
{
  return idCode;
}

// setTitle(string)
void Book::setTitle(string t)
{
  title=t;
}

// getTitle
string Book::getTitle()
{
  return title;
}

// setAuthor(string)
void Book::setAuthor(string a)
{
  author=a;
}

// getAuthor
string Book::getAuthor()
{
  return author;
}

// setLocation(Locale)
void Book::setLocation(Locale lo)
{
  location=lo;
}

// getLocation
Locale Book::getLocation()
{
  return location;
}

// setCheckedOutBy(Patron*)
void Book::setCheckedOutBy(Patron* p)
{
  checkedOutBy=p;
}

// getCheckedOutBy
Patron* Book::getCheckedOutBy()
{
  return checkedOutBy;
}

// setRequestedBy(Patron*)
void Book::setRequestedBy(Patron* p)
{
  requestedBy=p;
}

// getRequestedBy
Patron* Book::getRequestedBy()
{
  return requestedBy;
}

// setDateCheckedOut(int)
void Book::setDateCheckedOut(int d)
{
  dateCheckedOut=d;
}

// getDateCheckedOut
int Book::getDateCheckedOut() 
{
  return dateCheckedOut;
}
