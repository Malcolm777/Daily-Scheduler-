/*****************************************                                                                                                                                                                                                                                                                                                                                                                                                                                                     
** File:    Manager.cpp                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
** Project: CMSC 202 Project 3, Fall 2021                                                                                                                                                                                                                                                                                                                                                                                                                                                      
** Author:  Malcolm Gilbert                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
** Date:    11/02/21                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
** Section: 14                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
** E-mail:  malcolm7@gl.umbc.edu                                                                                                                                                                                                                                                                                                                                                                                                                                                               
**                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
** This file contains the Manager.cpp file for Project 3.                                                                                                                                                                                                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
**Manager.cpp contains the class managing the loading of files,                                                                                                                                                                                                                                                                                                                                                                                                                                
**the user input, and the schedules                                                                                                                                                                                                                                                                                                                                                                                                                                                            
** It has two pieces of data:                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
**a vector to hold the Schedules (m_schedules)                                                                                                                                                                                                                                                                                                                                                                                                                                                 
** and a string holding the name of the input file (m_fileName).                                                                                                                                                                                                                                                                                                                                                                                                                               
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
*/
#include "Manager.h"

//Manager overloaded constructor                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//Displays all schedules available in m_schedules                                                                                                                                                                                                                                                                                                                                                                                                                                              
Manager::Manager(string fileName){
  //string holding name of input file                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  m_fileName = fileName;
  ReadFile();
  MainMenu();
}

//Manager destructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//Deallocates the memory for the m_schedules dynamic memory allocation                                                                                                                                                                                                                                                                                                                                                                                                                         
Manager::~Manager(){
  cout << "Deleting schedules" << endl;

  //traverses the list to deallocate the memory                                                                                                                                                                                                                                                                                                                                                                                                                                                
  for(unsigned int i = 0; i < m_schedules.size(); i++){
    delete m_schedules.at(i);
  }
}

//DisplaySchedules                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
//Displays each schedule in m_schedules                                                                                                                                                                                                                                                                                                                                                                                                                                                        
void Manager::DisplaySchedules(){
  if(m_schedules.size() >= 1){

    //Displays each schedule in m_schedules                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    for(unsigned int i = 0; i < m_schedules.size(); i++){
      cout << *m_schedules.at(i) << endl;
    }
  }
}

//ReadFile                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//Reads in a file that has                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//the schedule name, start time, and the activity                                                                                                                                                                                                                                                                                                                                                                                                                                              
void Manager::ReadFile(){
  Item *newItem;
  Schedule *newSchedule;
  ifstream iFile;
  int count = 0;
  int location; //tracking the index                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  string scheduleName, time, name;

  iFile.open(m_fileName);
  cout << "File opened." << endl;

  //reads in the file with ; delimiter                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  while(getline(iFile, scheduleName, ';') && getline(iFile, time, ';') && getline(iFile, name, '\n')){
    newItem = new Item(name, stoi(time));
    location = FindSchedule(scheduleName);

    //If new schedule, inserts a new schedule                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    //and indicates a new schedule was created                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    if(location == -1){
      newSchedule = new Schedule(scheduleName);
      m_schedules.push_back(newSchedule);
      m_schedules.at(m_schedules.size()-1)->InsertSorted(newItem);
    } else {
      m_schedules.at(location)->InsertSorted(newItem);
    }
    count++;
  }
  iFile.close();
  cout << count << " nodes loaded across " << m_schedules.size() <<  " schedules." << endl;
}


//InsertNewItem                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//Allows user to insert an item into a schedule of their choice including a new one                                                                                                                                                                                                                                                                                                                                                                                                            
void Manager::InsertNewItem(){
  int location;
  Schedule *newSchedule;
  Item *newItem;
  string scheduleName;
  int count = 0;
  cout << "Which schedule would you like to insert into?" << endl;
  cin.ignore(256, '\n');
  getline(cin, scheduleName);
  location = FindSchedule(scheduleName);

  //creates new item                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  newItem = new Item();
  cout << "What is the start time of the activity?" << endl;
  int start;
  cin >> start;
  cout << "What is the name of the activity?" << endl;
  string name;
  cin.ignore(256, '\n');
  getline(cin, name);

  newItem->SetTime(start);
  newItem->SetName(name);

  //indicates a new schedule was created                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  if(location == -1){
    newSchedule = new Schedule(scheduleName);
    cout << "New schedule was created" << endl;

    //Either inserts a new item into existing schedule                                                                                                                                                                                                                                                                                                                                                                                                                                         
    //or inserts into a new schedule                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    m_schedules.push_back(newSchedule);
    m_schedules.at(m_schedules.size()-1)->InsertSorted(newItem);
  } else {
    m_schedules.at(location)->InsertSorted(newItem);
  }
  count++;
}


//FindSchedule                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//Returns the index of the schedule from m_schedules, else -1                                                                                                                                                                                                                                                                                                                                                                                                                                  
int Manager::FindSchedule(string scheduleName){
  //given m_schedules                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  //Returns the index of schedule with the matching name or it returns -1                                                                                                                                                                                                                                                                                                                                                                                                                      
  if(m_schedules.size() == 0){
    return -1;
  } else {
    for(unsigned int i = 0; i < m_schedules.size(); i++){
      if(scheduleName == m_schedules.at(i)->GetName()){
        return i;
      }
    }
  }
  return -1;
}

//Main menu                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
//Displays the main menu and manages exiting                                                                                                                                                                                                                                                                                                                                                                                                                                                   
void Manager::MainMenu(){
  int choice = 0;
  do {
    cout << "What would you like to do? " << endl;
    cout << "1. Display Schedules" << endl;
    cout << "2. Reverse Schedules" << endl;
    cout << "3. Insert New Item" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;

    //gets user input and calls Manager functions                                                                                                                                                                                                                                                                                                                                                                                                                                              
    if(choice == 1){
      DisplaySchedules();
    }
    if(choice == 2){
      ReverseSchedule();
    }
    if(choice == 3){
      InsertNewItem();
    }
  } while (choice != 4);
}

//ReverseSchedule                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
//User chooses a schedule and the schedule is reversed                                                                                                                                                                                                                                                                                                                                                                                                                                         
void Manager::ReverseSchedule(){
  string scheduleChosen;
  int found;
  cout << "Which schedule would you like to choose?" << endl;
  cin.ignore(256, '\n');
  getline(cin, scheduleChosen);
  found = FindSchedule(scheduleChosen);

  //If only one schedule in m_schedules                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  //automatically reverses it without prompting the user                                                                                                                                                                                                                                                                                                                                                                                                                                       
  if(found != -1){
    m_schedules[found]->ReverseSchedule();
  }
}










