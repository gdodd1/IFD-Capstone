#include "Player.h"

class HPSPPlayer : public Player{
    private:
        int HP;
        int SP;
        nodeType<Item*>* armorEnabled;
    public:
    
    HPSPPlayer() : Player() {
        HP = 100;
        SP = 100;
        armorEnabled = NULL;
    }   
    int isGameOver(){
        if(HP <= 0 || SP <= 0){
            return 1;
        }
        else if (currentLocation->info.getID() == 1){
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
    }
    void resetPlayerStats(){
        HP = 100;
        SP = 100;
    }
    void reportStats(){
        cout<<"Player Stats: "<<endl;
        cout << "\tHit Points: " << HP << endl;
        cout << "\tSanity Points: " << SP << endl;
    }

    virtual void armor(Map* mapptr){
        cout<<"What item to eqip?"<<endl;
        string item;
        getline(cin, item);
        nodeType<Item*>* tempItem = items.getFirst();
        // cout<<"Item [0] - "<<tempItem->info-()<<"\n\n\n";
        if(tempItem == nullptr){
            cout<<"You have no items in your inventory."<<endl;
        }
        else{
            bool found = false;
            while(tempItem != nullptr && !found){
                if(item == tempItem->info->getName()){
                    found = true;
                }else
                    tempItem = tempItem->link;
            }
            if(found){
                tempItem->info->setEqipped();
            }
        }
        armorEnabled = tempItem;
        cout<<"Armor is ready to use now!"<<endl;
        
    }

    virtual void consume(Map* mapptr){
        cout<<"What would you like to consume?"<<endl;
        string n;
        getline(cin, n);
        nodeType<Item*>* temp = NULL;
        Effect* effect;
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
            // cout<<mapptr->reverseLookUp(currentLocation)<<" - "<<temp->info->getActiveArea()<<endl;
            if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                cout<<temp->info->getActiveMessage()<<endl;
                int i=0;
                vector<Effect*> vec = temp->info->getItemConsumeEffects();
                for(int i=0;i<vec.size();i++){
                    switch(vec[0]->effectID){
                        case 0:
                            HP-=vec[i]->effectAmt;
                            break;
                        case 1:
                            HP+=vec[i]->effectAmt;
                            break;
                        case 2:
                            SP-=vec[i]->effectAmt;
                            break;
                        case 3:
                            SP+=vec[i]->effectAmt;
                            break;
                        default:
                            cout<<"Default error, effectID not recognized."<<endl;
                            break;
                    }
                }
            }else{
                cout<<"You cannot consume the "<<temp->info->getName()<<" here."<<endl;
            }
        }
        else{
        cout<<"No item by that name in your inventory."<<endl;
        }
        }
    }



void useArmor(){
    cout<<"\nArmor Used"<<endl;
    if(armorEnabled != nullptr && armorEnabled->info->getEqipped() == 1){
        if(armorEnabled->info->getArmorLife() > 1){
            HP = HP + armorEnabled->info->getArmorLife();
            int recovedLife = HP - 100;
            if(HP > 100) HP = HP - 100;
            
            cout<<"Health recoved by armor HP added: "<<recovedLife<<endl;
        }
    }else{
        cout<<"Armor equip is required to use it."<<endl;
    }

}
	// virtual void use(Map* mapptr){
    //     cout<<"Use what item?"<<endl;
    //     string item;
    //     getline(cin, item);
        
    // };
    virtual void use(Map* mapptr){
        cout<<"What item to use?"<<endl;
        string item;
        getline(cin, item);
        nodeType<Item*>* tempItem = items.getFirst();
        // cout<<"Item [0] - "<<tempItem->info-()<<"\n\n\n";
        if(tempItem == nullptr){
            cout<<"You have no items in your inventory."<<endl;
        }
        else{
            bool found = false;
            while(tempItem != nullptr && !found){
                if(item == tempItem->info->getName()){
                    found = true;
                }else
                    tempItem = tempItem->link;
            }
            if(found){
                if(tempItem->info->getType() == "armor"){
                    useArmor();
                    return;
                }
                if(tempItem->info->getType()!="use"){
                        cout<<"There's no way to use this item."<<endl;
                        return;
                    }
                if(mapptr->reverseLookUp(currentLocation) == tempItem->info->getActiveArea() || tempItem->info->getActiveArea() == 0){
                    // show message
                    cout<<tempItem->info->getActiveMessage()<<endl;
                    
                    vector<Rule*> vec = tempItem->info->getItemUseRules();
                    // cout<<"Size of vec: "<<vec.size()<<endl;
                    for(int i=0;i<vec.size();i++){
                        mapptr->setNewLinks(vec[i]->beginRm, vec[i]->destRm, vec[i]->direction);
                    }
                }else{
                    cout<<"You cannot use the "<<tempItem->info->getName()<<" here."<<endl;
                }
            }
            else{
            cout<<"No item by that name in your inventory."<<endl;
            }
        }
    }
};

