#ifndef AREA_H
#define AREA_H

#include <string>
#include <iostream>
#include "Item.h"
#include "ull.h"

using namespace std;

class Area{
  public:
    void setDescription (string desc){
    	description = desc;
    }
    void setGoal(bool g){
	goal = g;
    }
    void setID(bool id){
	instadeath = id;
    }
    string getDescription(){
    	return description;
    }
    bool getID(){
    	return instadeath;
    }
    bool getGoal(){
	return goal;
    }
    void displayArea(){
	cout<<description<<endl;
    }
    void search(){
        nodeType<Item*>* current = items.getFirst();
        // nodeType<Item*>* next = current;
        // nodeType<Item*>* temp;
        if(current == NULL){
            cout <<"There are no items in this area\n";
            return;
        }
        cout<<"The following items are in this area:\n";
        while(current != nullptr){
            cout<<"\t"<<current->info->getName()<<endl;
            current = current->link;
        }

    }
    uLList<Item*> items;
  private:
    string description;
    bool instadeath;
    bool goal;
};

#endif