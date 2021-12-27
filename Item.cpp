/*****************************************                                                                                                                                                                                                
** File:    Item.cpp                                                                                                                                                                                                                      
** Project: CMSC 202 Project 3, Fall 2021                                                                                                                                                                                                 
** Author:  Malcolm Gilbert                                                                                                                                                                                                               
** Date:    11/02/21                                                                                                                                                                                                                      
** Section: 14                                                                                                                                                                                                                            
** E-mail:  malcolm7@gl.umbc.edu                                                                                                                                                                                                          
**                                                                                                                                                                                                                                        
** This file contains the Item.cpp file for Project 3.                                                                                                                                                                                    
                                                                                                                                                                                                                                          
** This program contains the access modifiers, the setters and getters                                                                                                                                                                    
** for the item Node class                                                                                                                                                                                                                
                                                                                                                                                                                                                                          
*/

#include "Item.h"

//Item                                                                                                                                                                                                                                    
//Default constructor                                                                                                                                                                                                                     
Item::Item(){
  m_name = "activity";
  m_time = 1;
  m_next = nullptr;
}

//Item overloaded constructor                                                                                                                                                                                                             
Item::Item(string name, int time){
  m_name = name;
  m_time = time;
  m_next = nullptr;
}
//accessors                                                                                                                                                                                                                               
//GetName                                                                                                                                                                                                                                 
string Item::GetName(){
  return m_name;
}

//GetTime                                                                                                                                                                                                                                 
int Item:: GetTime(){
  return m_time;
}

//GetNext                                                                                                                                                                                                                                 
Item* Item::GetNext(){
  return m_next;
}

//mutators                                                                                                                                                                                                                                

//SetName                                                                                                                                                                                                                                 
void Item::SetName(string name){
  m_name = name;
}

//SetTime                                                                                                                                                                                                                                 
void Item::SetTime(int time){
  m_time = time;
}

//SetNext                                                                                                                                                                                                                                 
void Item::SetNext(Item* item){
  m_next = item;
}





