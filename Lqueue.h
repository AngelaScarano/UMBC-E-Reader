#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int SPACE_LIST_NUM = 3;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue& l);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = false, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T& data, bool isTrue);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here


//default constructor
template <class T>
Lqueue<T>::Lqueue(){
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}

//default destructor
template <class T>
Lqueue<T>::~Lqueue(){
  Clear();
}

//Copy constructor
template <class T>
Lqueue<T>::Lqueue(const Lqueue & l){
  m_size = 0;
  Node<T> *temp1 = l.m_head;
  Node<T> *temp2;

  while (temp1 != NULL){
    Node<T> *newNode = new Node<T>(temp1->GetData());

    //set the head node for the new list
    if (m_size == 0){
      m_head = newNode;
      temp1 = temp1->GetNext();
      temp2 = m_head;
      m_size ++;
    }

    //set remaining nodes for the new list
    else{
      temp2->SetNext(newNode);
      temp1 = temp1->GetNext();
      temp2 = newNode;
      m_size ++;
    }
  }
  m_tail = temp2;
}


//Overloaded Assignment Operator. Copies given Lqueue into an existing Lqueue
template <class T>
Lqueue<T>& Lqueue<T>::operator= (const Lqueue& l){
  if (this == &l)
    return *this;

  this->Clear();
  m_size = 0;
    
  Node<T> *temp1 = l.m_head;
  Node<T> *temp2;
  
  while (temp1 != NULL){
    Node<T> *newNode = new Node<T>(temp1->GetData());
    
    //set the head node for the new list
    if (m_size == 0){
      m_head = newNode;
      temp1 = temp1->GetNext();
      temp2 = m_head;
      m_size ++;
    }
    
    //set remaining nodes for the new list
    else{
      temp2->SetNext(newNode);
      temp1 = temp1->GetNext();
      temp2 = newNode;
      m_size ++;
    }
  }
  m_tail = temp2;
  return *this;
}


//Takes in data to make a new node. If the bool is false
//adds node to the front. Otherwise, adds it to the back.
template <class T>
void Lqueue<T>::Push(const T& data, bool isTrue){

  //adds the first node to the Lqueue if its empty
  if (m_size == 0){
    Node<T> *newNode = new Node<T>(data);
    m_head = newNode;
    m_tail = newNode;
    m_size ++;
  }

  //adds node to the back of the Lqueue if bool is true
  else if (isTrue){
    Node<T> *newNode = new Node<T>(data);
    m_tail->SetNext(newNode);
    m_tail = newNode;
    m_size ++;
  }

  //adds node to the front of the Lqueue if bool is false
  else{
    Node<T> *newNode = new Node<T>(data);
    newNode->SetNext(m_head);
    m_head = newNode;
    m_size ++;
  }
}

//Removes first node in Lqueue, returns the data from the removed node
template <class T>
T Lqueue<T>::Pop(){
  T data = m_head->GetData();
  Node<T> *oldFirst = m_head;
  m_head = m_head->GetNext();
  m_size --;

  //delete dynamic memory from the removed node, prevent memory leak
  delete oldFirst;
  oldFirst = NULL;
  
  return data;
}

//Displays the data in each node of Lqueue
template <class T>
void Lqueue<T>::Display(){
  Node<T> *temp;
  temp = m_head;
  while(temp != NULL){
    cout << temp->GetData() << endl;
    temp = temp->GetNext();
  }
}

//Gets data from the first node in the Lqueue
template <class T>
T Lqueue<T>::Front(){
  return m_head->GetData();
}

//checks if the Lqueue is empty
template <class T>
bool Lqueue<T>::IsEmpty(){
  if (m_size == 0)
    return true;
  
  return false;
}

//returns the size of the Lqueue
template <class T>
int Lqueue<T>::GetSize(){
  return m_size;
}

//swaps the node at the index with the node prior to it
template <class T>
void Lqueue<T>::Swap(int index){
  //temp2 will hold index position prior to passed in index.
  //temp1 will hold index position prior to temp2
  Node<T> *temp1, *temp2;
  Node<T> *oldCurr = m_head;

  //cannot swap the first node, no node previous to it
  if (index == 0){
    return;
  }
  
  //iterate to the node at passed in index to access it
  for (int i = 0; i < index; i++){
    temp1 = temp2;
    temp2 = oldCurr;
    oldCurr = oldCurr->GetNext();
  }

  //if the first node, thus m_head, is affected:
  if (index == 1){
    m_head = oldCurr;
    temp2->SetNext(oldCurr->GetNext());
    oldCurr->SetNext(temp2);
  }

  else{

    //swap positions of entire nodes
    temp1->SetNext(oldCurr);
    temp2->SetNext(oldCurr->GetNext());
    oldCurr->SetNext(temp2);
    
    //if the last node, thus m_tail, is affected:
    if (index == m_size - 1)
      m_tail = oldCurr->GetNext();
  }
}

//removes all nodes in an Lqueue
template <class T>
void Lqueue<T>::Clear(){
  Node<T> *current = m_head;
  Node<T> *temp;
  
  while (current != NULL){
    temp = current->GetNext();
    delete current;
    current = temp;
    m_size --;
  }
  m_head = NULL;
  m_tail = NULL;
}

//displays the data at m_head and m_tail
template <class T>
void Lqueue<T>::TestHeadTail(){
  cout << m_head->GetData() << endl;
  cout << m_tail->GetData() << endl;
}

//returns an ostream with data from each node on a new line
template <class U>
ostream &operator<< (ostream &output, const Lqueue<U>& l){
  Node<U> *temp;
  temp = l.m_head;
  int counter = 1;
  while(temp != NULL){
    output << right << setw(SPACE_LIST_NUM) << counter << ".";
    output << temp->GetData();
    temp = temp->GetNext();
    counter ++;
  }  
  return output;
}


//returns data from the xth node in the linked list
template <class T>
T& Lqueue<T>::operator[](int x){
  Node<T> *neededNode = m_head;

  //loop to the desired node in the Lqueue
  for (int i = 0; i < x; i++){
    neededNode = neededNode->GetNext();
  }
  return neededNode->GetData();
}


//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;
  
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);

  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;

  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;

  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;

  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;

  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;

  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;
  
  return 0;
}

*/
