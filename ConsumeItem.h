#include <iostream>
#include "Item.h"

using namespace std;

class ConsumeItem : public Item{
    public:
        void addEffect(Effect *effect){
            effectsVec.push_back(effect);
        }
        vector<Effect*> getItemConsumeEffects(){
            return effectsVec;
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