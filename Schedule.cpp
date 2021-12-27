/*****************************************                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
** File:    Schedule.cpp                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
** Project: CMSC 202 Project 3, Fall 2021                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
** Author:  Malcolm Gilbert                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
** Date:    10/30/21                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
** Section: 14                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
** E-mail:  malcolm7@gl.umbc.edu                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
**                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
** This file contains the Schedule.cpp file for Project 1.                                                                                                                                                                                                                                                                                                                                                                                                                                                                
** Schedule.cpp is a linked list class which contains four pieces of data:                                                                                                                                                                                                                                                                                                                                                                                                                                                
** A name for the schedule (m_name)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
** an Item pointer tracking the front of the Schedule (m_head)                                                                                                                                                                                                                                                                                                                                                                                                                                                            
** an Item pointer tracking the end of the Schedule (m_tail)                                                                                                                                                                                                                                                                                                                                                                                                                                                              
** and an integer tracking the size of Schedule (m_size).                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
*/

#include "Schedule.h"
#include "Item.h"

//Schedule constructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
//creates a new schedule with name of “Default” and pointers                                                                                                                                                                                                                                                                                                                                                                                                                                                              
Schedule::Schedule(){
  m_name = "Default";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

//Schedule overloaded constructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
//populates the name based on passed value and pointers                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
Schedule::Schedule(string name){
  m_name = name;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

//Schedule destructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//Destructs the whole schedule                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
Schedule::~Schedule(){
  Item *curr = m_head;
  //traverses the LL to destroy dynamically allocated memory                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  while(curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

void Schedule::InsertSorted(Item* item){
  //first base case  - no head node                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  //assigns m_head and m_tail ptr and value                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
  if(m_head == nullptr){
    m_head = item;
    m_tail = item;
    m_size++;
    return;
  }

  //second base case - new min time                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  //if m_head time > new item time, item inserts before                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  else if (m_head->GetTime() >= item->GetTime()){
    item->SetNext(m_head);
    m_head = item;
    m_size++;
    return;
  }

  //third base case - new max time                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  //if item time > tail time, item insert after                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  else if (item->GetTime() > m_tail->GetTime()){
    m_tail->SetNext(item);
    m_tail = item;
    m_size++;
    return;
  }
  //iterate through the list                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  //uses curr node to traverse the linked list w/o losing any data                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  Item *prev = m_head;
  Item *curr = m_head;
  while(curr != nullptr){
    if(item->GetTime() > curr->GetTime()){
      //move previous pointer to next node                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
      prev = curr;
      //move current pointer to next node                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
      curr = curr->GetNext();
    } else {
      //once this condition is false, then I will insert nodes                                                                                                                                                                                                                                                                                                                                                                                                                                                            
      //insert new node and adjust required links                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
      item->SetNext(curr);
      prev->SetNext(item);
      m_size++;
      return;
    }
  }
}


//GetName                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//Returns m_name                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
string Schedule::GetName(){
  return m_name;
}

//GetSize                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
int Schedule::GetSize(){
  return m_size;
}

//ReverseSchedule                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
//Schedule is reversed in place, nothing is returned                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
void Schedule::ReverseSchedule(){


  //Step 1: Create 3 node pointers                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  Item *curr = m_head;
  Item *prev = nullptr;
  Item *next = nullptr;

  //updates m_tail                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  m_tail = m_head;
  //Step 2: Iterate and update the pointers until the end                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
  while(curr != nullptr){
    next = curr->GetNext();
    curr->SetNext(prev);

    //Step 3: Move prev and curr one step forward                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    prev = curr;
    curr = next;
  }
  //Step 4: Assign the head to the previous node                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  m_head = prev;
  cout << "Schedule successfully reversed" << endl;
}


// Name: GetData                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
// Desc: Returns the time at a specific location in the Schedule                                                                                                                                                                                                                                                                                                                                                                                                                                                          
Item* Schedule::GetData(int nodeNum){
  //returns the time at a specific location in the schedule pass                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  Item *curr = m_head;
  int counter = 0;
  while(curr != nullptr){
    if (counter == nodeNum){
      return curr;
    }
    counter++;
  } //return item pointer                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
  return curr;//at this point, it's a nullptr                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
}


//Name: operator <<                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
//Returns ostream populated for each Item in schedule                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
ostream &operator<< (ostream &output, Schedule &mySchedule){
  //create a pointer to traverse the LL                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  Item *curr = mySchedule.m_head;
  output << mySchedule.m_name << endl;
  while(curr != nullptr){
    output << *curr << endl;
    curr = curr->GetNext();
  }
  return output;
}





