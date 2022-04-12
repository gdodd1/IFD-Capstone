#include <iostream>
#include "Item.h"


using namespace std;

class UseItem : public Item{
    protected:
    // no code
    public:
        void addRule(Rule* tempRule){
            rulesVec.push_back(tempRule);
        }
        vector<Rule*> getItemUseRules(){
            return rulesVec;
        }
        void setActiveArea(int i){
            activeArea = i;
        }
        int getActiveArea(){
            return activeArea;
		}
        string getActiveMessage(){
            return activeMessage;
		}
        void setActiveMessage(string s){
            activeMessage = s;
		}
        
};
