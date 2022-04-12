#ifndef ullItem
#define ullItem
    #include "ull.h"
    #include "Item.h"
#endif

#ifndef PLAYER_H
#define PLAYER_H
#include "MapV2.h"


class Player{
  public:
    uLList<Item*> items;

        Player(){
        lastLocation = NULL;
        currentLocation = NULL;
    }

    static void setLives(int lives){
        PlayerLives = lives;
    }

    static int getLives(){
        return PlayerLives;
    }

    void setCurrent(areaNode* loc){
        lastLocation = currentLocation;
        currentLocation = loc;
    }

    bool playerMoved(){
        bool found = false;
        for(int i=0;i<visitedRooms.size();i++){
            if(currentLocation == visitedRooms[i]){
                found = true;
            }
        }
        if(!found){
            visitedRooms.push_back(currentLocation);
        }
        return !(lastLocation == currentLocation);
    }
    areaNode* getCurrent(){
        return currentLocation;
    }

    void inventory(){
        nodeType<Item*>* temp;
            temp = items.getFirst();
        //cout<<temp<<endl;
        if(temp == NULL){
            cout<<"No items are in your inventory."<<endl;
        }
        else{
            cout<<"You have the following items:"<<endl;
            while(temp != NULL){
                cout<<"\t"<<temp->info->getName()<<endl;
                temp = temp->link;
            }
        }
    }

    void take(){
        cout<<"Take what item?"<<endl;
        string n;
        getline(cin, n);
        //cout<<"Looking for item: "<<n<<endl;
            nodeType<Item*>* temp = NULL;
        temp = currentLocation->info.items.getFirst();
        //cout<<temp<<endl;
        if(temp == NULL){
            cout<<"No items are in this room to take."<<endl;
        }
        else{
            bool found = false;
            while(temp != NULL && !found){
                if(n == temp->info->getName()){
                    found = true;
                    //add to player list
                    items.insertLast(temp->info);
                    //delete from room list
                    currentLocation->info.items.deleteNode(temp->info);
                }
                else{
                    temp = temp->link;
                }
            }
            if(found){
                cout<<"You have taken: "<<n<<endl;
            }
            else{
                cout<<"No item by that name here."<<endl;
            }
        }
    }

    void leave(){
        cout<<"Leave what item?"<<endl;
        string n;
        getline(cin, n);
        //cout<<"Looking for item: "<<n<<endl;
            nodeType<Item*>* temp = NULL;
        temp = items.getFirst();
        //cout<<temp<<endl;
        if(temp == NULL){
            cout<<"You have no items in your inventory."<<endl;
        }
        else{
            bool found = false;
            while(temp != NULL && !found){
                if(n == temp->info->getName()){
                    found = true;
                    //add to room list
                    currentLocation->info.items.insertLast(temp->info);
                    //delete from player list
                    items.deleteNode(temp->info);
                }
                else{
                    temp = temp->link;
                }
            }
            if(found){
                cout<<"You have dropped: "<<n<<endl;
            }
            else{
                cout<<"No item by that name in your inventory."<<endl;
            }
        }
    }
    void roomInfo(){
        cout<<currentLocation->info.getDescription();
    }
    void teleport(){
        int destRm;
        cout<<"Rooms for teleportation: "<<visitedRooms.size()<<endl;
        for(int i=0;i<visitedRooms.size();i++){
            cout<<"Room "<<i+1<<" "<<visitedRooms[i]<<" ";
        }
        cout << "\nWhich room do you want to teleport to? " << endl;
        cin >> destRm;
        cout<<"check: "<<visitedRooms[destRm-1]<<"\n\n";
        if(destRm == 1 && visitedRooms[destRm-1] == nullptr){
            cout<<"Your in the same room"<<endl;
            return;
        }else if(destRm <= 0 || destRm > visitedRooms.size()){
            cout << "Error: Invalid Room Input -- Not in the \nWhich room do you want to teleport to? " << endl;
            cin >> destRm;
        }else{
            currentLocation = visitedRooms[destRm-1];
            cout<<"Teleported to Room "<<destRm<<endl;
        }
        // cout<<currentLocation->info.getDescription();
    }
   
    void examine(){
        cout<<"Examine what item?"<<endl;
        string n;
        getline(cin, n);
        //cout<<"Looking for item: "<<n<<endl;
            nodeType<Item*>* temp = NULL;
        temp = items.getFirst();
        //cout<<temp<<endl;
        if(temp == NULL){
            cout<<"You have no items in your inventory to examine."<<endl;
        }
        else{
            bool found = false;
            while(temp != NULL && !found){
                if(n == temp->info->getName()){
                    found = true;
                    //display item description
                    cout<<temp->info->getDesc()<<endl;
                }
                else{
                    temp = temp->link;
                }
            }
            if(!found){
                cout<<"No item by that name in your inventory."<<endl;
            }
        }
    };
   
    virtual int isGameOver() = 0;
    virtual void resetPlayerStats() = 0;
    virtual void reportStats() = 0;
    virtual void consume(Map* mapptr) = 0;
    virtual void use(Map* mapptr) = 0;
    virtual void armor(Map* mapptr) = 0;


  protected:
        areaNode* currentLocation;
        areaNode* lastLocation;
        static int PlayerLives;
        vector<areaNode*> visitedRooms;

};

#endif