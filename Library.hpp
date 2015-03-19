

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "Patron.hpp"
#include "Book.hpp"

class Patron;  // forward declarations
class Book;

class Library
{
private:
    std::vector<Book> holdings;
    std::vector<Patron> members;
    int currentDate;
    Book* findBook(std::string bookID); 
    Patron* findPatron(std::string patronID);
public:
    Library();
    void addBook();
    void addMember();
    void checkOutBook(std::string patronID, std::string bookID);
    void returnBook(std::string bookID);
    void requestBook(std::string patronID, std::string bookID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    void viewBookInfo(std::string bookID);
};

#endif
