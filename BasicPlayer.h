#include "Player.h"

using namespace std;

class Basic : public Player{
    public:
        int isGameOver(){
            if (currentLocation->info.getID() == 1){
                return 2;
            }
            else if(currentLocation->info.getGoal() == 1){
                return 1;
            }
            else if(currentLocation->info.getID() == 0 && currentLocation->info.getGoal() == 0){
                return 0;
            }
            else{
                return 0;
            }
        };
        void resetPlayerStats(){
            // No Use
        };
        void reportStats(){
            cout<<"No player statistics to report."<<endl;
        };

    virtual void armor(Map* mapptr){}
        virtual void consume(Map* mapptr){
       cout<<"What would you like to consume?"<<endl;
                string n;
                getline(cin, n);
                nodeType<Item*>* temp = NULL;
                temp = items.getFirst();
                if(temp == NULL){
                    cout<<"You have no items in your inventory."<<endl;
                }
                else{
                    bool found = false;
                    while(temp != NULL && !found){
                    if(n == temp->info->getName()){
                    found = true;
                    if(temp->info->getType()!="consume"){
                        cout<<"That proves impossible"<<endl;
                        return;
                    }
                }
                else{
                temp = temp->link;
                }
                }
                if(found){
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                    
                }else{
                    cout<<"You cannot consume the "<<temp->info->getName()<<" here."<<endl;
                }
            }
                else{
                    cout<<"No item by that name in your inventory."<<endl;
                }
            }
    }


        virtual void use(Map* mapptr){
        cout<<"What would you like to use?"<<endl;
        string item;
        getline(cin, item);
        nodeType<Item*>* temp = NULL;
        temp = items.getFirst();
        if(temp == NULL){
            cout<<"You have no items in your inventory."<<endl;
        }
        else{
            bool found = false;
            while(temp != NULL && !found){
            if(item == temp->info->getName()){
            found = true;
            }
            else{
            temp = temp->link;
            }
        }
        if(found){
                if(temp->info->getType()!="use"){
                        cout<<"There's no way to use this item."<<endl;
                        return;
                    }
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                    vector<Rule*> vec = temp->info->getItemUseRules();
                    // cout<<"Size of vec: "<<vec.size()<<endl;
                    for(int i=0;i<vec.size();i++){
                        mapptr->setNewLinks(vec[i]->beginRm, vec[i]->destRm, vec[i]->direction);
                    }
                }else{
                    cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                }
        }
            else{
                cout<<"No item by that name in your inventory."<<endl;
            }
        }
    }
};