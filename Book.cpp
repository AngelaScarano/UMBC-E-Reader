#include "Book.h"
using namespace std;

const int SPACE_RANK = 3;
const int SPACE_TITLE = 40;
const int SPACE_AUTHOR = 22;
const int SPACE_PRICE = 8;

//default constructor
Book::Book(){}

//overloaded constructor
Book::Book(string title, string author, int rank, double price){
  m_title = title;
  m_author = author;
  m_rank = rank;
  m_price = price;
}

//getter for m_title
string Book::getTitle()const{
  return m_title;
}

//getter for m_author
string Book::getAuthor()const{
  return m_author;
}

//getter for m_rank
int Book::getRank()const{
  return m_rank;
}

//getter for m_price
double Book::getPrice()const{
  return m_price;
}

//mutator for m_title
void Book::setTitle(string title){
  m_title = title;
}

//mutator for m_author
void Book::setAuthor(string author){
  m_author = author;
}

//mutator for m_rank
void Book::setRank(int rank){
  m_rank = rank;
}

//mutator for m_price
void Book::setPrice(double price){
  m_price = price;
}

//returns an output stream with the details of a book
ostream& operator<<(ostream& output, Book& book){
  output << right << setw(SPACE_TITLE) << book.getTitle()
	 << right << setw(SPACE_AUTHOR) << book.getAuthor()
	 << right << setw(SPACE_PRICE) << "(" << fixed << setprecision(2)
	 << book.getPrice() << ")" << endl;
  return output;
}

//compares two Book objects - returns true if lhs is lower priced
bool operator < (Book const & lhs, Book const & rhs){
  if (lhs.getPrice() < rhs.getPrice())
    return true;
  return false;
}
