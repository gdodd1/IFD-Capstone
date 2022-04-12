#include "Item.h"

class EquipItem: public Item{
    int armorLifePoints;
    int equipped;
    public:
        EquipItem(){
            armorLifePoints = equipped = 0;
        }
        void setArmorLife(int life){
            armorLifePoints += life;
        }
        int getArmorLife(){
            return armorLifePoints;
        }
        void armorEqipped(){
            equipped = 1;
        }
        int getEqipped(){
            return equipped;
        }
        void setEqipped(){
            equipped = 1;
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