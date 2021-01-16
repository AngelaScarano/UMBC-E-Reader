#include "EReader.h"
using namespace std;

//const int SPACE_LIST_NUM = 3;

const int SENTINEL = 5;
const int MENU_MIN = 1;
const int MENU_MAX = 5;
const string MAIN_MENU[MENU_MAX] = {"Display All Books",
				    "Add Book To Readlist",
				    "Display Readlist",
				    "Sort Readlist By Price",
				    "Quit"};

//default constructor
EReader::EReader(){}

//overloaded constructor
EReader::EReader(string filename){
  LoadCatalog(filename);
}

//destructor
EReader::~EReader(){
  //deallocates dynamic pointers in m_bookCatalog
  for (unsigned i = 0; i < m_bookCatalog.size(); i++){
    delete m_bookCatalog.at(i);
    m_bookCatalog.at(i) = NULL;
  }

  //deallocates dynamic pointers in m_readList
  m_readList.Clear();
}

//loads the file of books into the m_bookCatalog (as books)
void EReader::LoadCatalog(string filename){
  string title, author, strRank, strPrice;
  int rank;
  double price;
  Book* bookPtr;

  fstream bookData;
  bookData.open(filename);

  if (bookData.is_open()){
    while (!bookData.eof()){
      getline(bookData, title, ',');
      getline(bookData, author, ',');
      getline(bookData, strRank, ',');
      getline(bookData, strPrice);
      rank = stoi(strRank);
      price = stod(strPrice);
      

      bookPtr = new Book(title, author, rank, price);
      m_bookCatalog.push_back(bookPtr);

      if(bookData.peek() == bookData.eof())
	return;
    }
    bookData.close();
  }
}

//manages the application as a whole, and runs the main menu
void EReader::MainMenu(){
  bool proceed = true;
  int choice;

  //cout << "Welcome to UMBC E-Reader" << endl;
  cout << "Catalog populated with " << m_bookCatalog.size()
       << " books." << endl;
  do{
    //displays menu choices and takes validated user input selection
    do{
      cout << "What would you like to do?" << endl;
      for (int i = 0; i < MENU_MAX; i++){
	cout << i + 1 << ". " << MAIN_MENU[i] << endl;
      }
      cin >> choice;
    }while(choice < MENU_MIN || choice > MENU_MAX);

    switch(choice){

    case 1:
      DisplayBooks();
      break;

    case 2:
      AddBook();
      break;

    case 3:
      DisplayReadlist();
      break;

    case 4:
      SortReadlist();
      break;

    case 5:
      cout << "Quit" << endl;
      proceed = false;
    }
    
  }while(proceed);
  cout << "Thank you for using UMBC EReader!" << endl;
}

//displays all books (150) in the master list
void EReader::DisplayBooks(){
  for (unsigned i = 0; i < m_bookCatalog.size(); i++){
    cout << right << setw(SPACE_LIST_NUM)
	 << m_bookCatalog[i]->getRank() << ".";
    cout << *m_bookCatalog[i];
  }
}

//displays the current master list and adds a book to m_readList
void EReader::AddBook(){
  int bookNum;

  //gets user book selection to add to m_readList
  do{
    DisplayBooks();
    cout << "Choose the book you would like to add to "
	 << "your reading list." << endl;
    cin >> bookNum;
  }while(bookNum < MENU_MIN || bookNum > int(m_bookCatalog.size()));

  //sets boolean based on if m_readList is empty. Adds book to m_readList
  if (m_readList.GetSize() == 0){
    bool boolVal = false;
    Book *bookPtr = m_bookCatalog.at(bookNum - 1);
    m_readList.Push(*bookPtr, boolVal);
  }

  else{
    bool boolVal = true;
    Book *bookPtr = m_bookCatalog.at(bookNum - 1);
    m_readList.Push(*bookPtr, boolVal);
  }
}

//displays the current readList m_readList
void EReader::DisplayReadlist(){
  cout << m_readList;
}

//uses the overloaded < operator from Book to sort prices
//from high to low in m_readList
void EReader::SortReadlist(){
  bool notSorted;

  //compares price values of books in m_readList. Swaps as needed to sort from highest to lowest
  do{
    notSorted = false;
    
    for (int count = 1; count < m_readList.GetSize(); count ++){
      if (m_readList[count - 1] < m_readList[count]){
	m_readList.Swap(count);
	notSorted = true;
	count = 1;
      }
    }
  }while (notSorted);
}
