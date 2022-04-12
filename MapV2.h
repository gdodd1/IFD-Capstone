#ifndef MAPV2_H
#define MAPV2_H



#include<iostream>
#include "Map.h"
#include "BasicPlayer.h"
#include "HPSPPlayer.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "EquipItem.h"


using namespace std;

class MapV2 : public Map{
    private:
vector<Item*> itemVec;
    public:
	Player *tempPlayer;
MapV2(){
			ifderr = false;
			parser.tokenIt();

			nextToken = parser.getNext();

			if(nextToken == "<game>"){
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state
					// ptype
					if(nextToken == "<ptype>"){
						parser.eatToken();
						nextToken = parser.getNext();
						createPlayer();
						//cout<<"Return Back";
					}
					// player's lives parsing
					else if(nextToken == "<lives>"){
						string xstr;
						parser.eatToken();
						nextToken = parser.getNext();
						istringstream ss(nextToken);
        				getline(ss, xstr);
						tempPlayer->setLives(atoi(xstr.c_str()));
						parser.eatToken();
						nextToken = parser.getNext();
					}
					else if(nextToken == "<area>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeArea();
					}
					else if(nextToken == "<links>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeLinks();
					}
                    else if(nextToken == "<item>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeItem();
					}
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}
					// cout<<"Token1:" <<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					// cout<<"Token2:" <<nextToken<<endl;

				}// while !</game>

				if(ifderr){
					cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
					cout<<"Game Loading Failed"<<endl;
					cout<<"General Area of Parsing Failure:"<<endl;
					cout<<"-------------------------------------"<<endl;
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					cout<<"-------------------------------------"<<endl;
					return;
				}
				//cout<<"::Found </game>::"<<endl;
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}

			//link up areas
			linkLinks();
			InsertItems();
		//constructor
}

void createPlayer(){
	cout<<"Creating "<<nextToken<<" Player ... READY!"<<endl;
	if(nextToken == "basic") tempPlayer = new Basic();
	else tempPlayer = new HPSPPlayer();
	parser.eatToken();
	nextToken = parser.getNext();
}



Player* checkPlayer(){
	return tempPlayer;
}

void makeItem(){
			string name, description;
            int room;
			string xstr;
			int beginRm;
			char direction;
			int destRm;
			Item* tempItemPtr;
			
			// cout<<"Make item: "<<nextToken<<endl;
			if(nextToken == "<use>"){
				tempItemPtr = new UseItem();
				tempItemPtr->setType("use");
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</use>"){
					if(nextToken == "<actmess>"){
						// actmess code
						parser.eatToken();
						nextToken = parser.getNext();
						tempItemPtr->setActiveMessage(nextToken);
					}
					else if(nextToken == "<actar>"){

						parser.eatToken();
						nextToken = parser.getNext();
						istringstream ss(nextToken);
        				getline(ss, xstr);
						tempItemPtr->setActiveArea(atoi(xstr.c_str()));
					}
					else if(nextToken == "<rule>"){
						parser.eatToken();
						nextToken = parser.getNext();

						Rule *tempRules = new Rule();

						istringstream ss(nextToken);
        				getline(ss, xstr, ',');
						tempRules->beginRm = atoi(xstr.c_str());
						getline(ss, xstr, ',');
						tempRules->direction = (xstr.c_str()[0]);
						getline(ss, xstr, ',');
						tempRules->destRm = atoi(xstr.c_str());

						tempItemPtr->addRule(tempRules);

					}
					else if(nextToken == "<desc>"){
						parser.eatToken();
						nextToken = parser.getNext();
						
						tempItemPtr->setDesc(nextToken);
					}
					else if(nextToken == "<name>"){
						parser.eatToken();
						nextToken = parser.getNext();
						tempItemPtr->setName(nextToken);
					}
					else if(nextToken == "<star>"){
						parser.eatToken();
						nextToken = parser.getNext();
						tempItemPtr->setSR(stoi(nextToken));
					}
					else if(nextToken == "</desc>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</star>" || nextToken == "</name>" || nextToken == "</use>" || nextToken == "</rule>"){
					//do nothing
					}
					else{
						cout<<"Parse Error Location 2"<<endl;
						ifderr = true;
						break;
					}

					parser.eatToken();
					nextToken = parser.getNext();
				}//while !</item>
				//add item to vector
				itemVec.push_back(tempItemPtr);
			}else if(nextToken == "<basic>"){
				tempItemPtr = new Item();
				parser.eatToken();
				nextToken = parser.getNext();
				basicHelper(tempItemPtr);
			}else if(nextToken == "<consume>"){
				tempItemPtr = new ConsumeItem();

				parser.eatToken();
				nextToken = parser.getNext();
				consumeHelper(tempItemPtr);
			}else if(nextToken == "<armor>"){
				tempItemPtr = new EquipItem();
				parser.eatToken();
				nextToken = parser.getNext();
				armorHelper(tempItemPtr);
			}else{
				cout<<"Invalid Item Token Type!"<<endl;
			}

			parser.eatToken();
			nextToken = parser.getNext();

}

void armorHelper(Item *tempItemPtr){
	string xstr;
	while(nextToken != "</armor>"){
		tempItemPtr->setType("armor");
		if(nextToken == "<name>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setName(nextToken);
		}else if(nextToken == "<life>"){
			parser.eatToken();
			nextToken = parser.getNext();
			istringstream ss(nextToken);
			getline(ss, xstr);
			tempItemPtr->setArmorLife(atoi(xstr.c_str()));
		}else if(nextToken == "<star>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setSR(stoi(nextToken));
		}else if(nextToken == "</star>" || nextToken == "</life>" || nextToken == "</name>"){
			// do nothing
		}else{
			cout<<"Parsing Error in Armor Code Section File Name: MapV2.h";
			ifderr = true;
			break;
		}

		parser.eatToken();
		nextToken = parser.getNext();
	}
	itemVec.push_back(tempItemPtr);
}

void consumeHelper(Item *tempItemPtr){
	while(nextToken != "</consume>"){
		tempItemPtr->setType("consume");
		if(nextToken == "<actmess>"){
			// actmess code
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setActiveMessage(nextToken);
		}
		else if(nextToken == "<actar>"){
			parser.eatToken();
			nextToken = parser.getNext();

			string xstr;
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			tempItemPtr->setActiveArea(atoi(xstr.c_str()));
			// cout<<"\n\n This is my Actar: "<<nextToken[0]<<"\n\n";
			// some code
		}
		else if(nextToken == "<desc>"){
			parser.eatToken();
			nextToken = parser.getNext();
			
			tempItemPtr->setDesc(nextToken);
		}
		else if(nextToken == "<name>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setName(nextToken);
		}
		else if(nextToken == "<star>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setSR(stoi(nextToken));
		}
		else if(nextToken == "<effect>"){
			string xstr;

			parser.eatToken();
			nextToken = parser.getNext();

			nextToken = parser.getNext();

			Effect *tempEffect = new Effect();
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			tempEffect->effectID = atoi(xstr.c_str());
			getline(ss, xstr, ',');
			tempEffect->effectAmt = atoi(xstr.c_str());
			
			tempItemPtr->addEffect(tempEffect);
		}
		else if(nextToken == "</desc>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</star>" || nextToken == "</name>" || nextToken == "</effect>"){
			//do nothing
		}
		else{
			cout<<"Parse Error Location consume area"<<endl;
			ifderr = true;
			break;
		}

		parser.eatToken();
		nextToken = parser.getNext();
	}
	itemVec.push_back(tempItemPtr);
}

void basicHelper(Item *tempItemPtr){
	while(nextToken != "</basic>"){
		if(nextToken == "<desc>"){
			parser.eatToken();
			nextToken = parser.getNext();
			
			tempItemPtr->setDesc(nextToken);
		}
		else if(nextToken == "<name>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setName(nextToken);
		}
		else if(nextToken == "<star>"){
			parser.eatToken();
			nextToken = parser.getNext();
			tempItemPtr->setSR(stoi(nextToken));
		}
		else if(nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</name>"){
		//do nothing
		}
		else{
			cout<<"Parse Error Location basic area"<<endl;
			ifderr = true;
			break;
		}

		parser.eatToken();
		nextToken = parser.getNext();
	}//while !</item>
	itemVec.push_back(tempItemPtr);
}

void InsertItems(){
	for(int i = 0; i < itemVec.size(); i++){
		areasVec[itemVec[i]->getSR() - 1]->info.items.insertLast(itemVec[i]);
	}
}



void resetItems(){
	
	for(int i = 0; i < areasVec.size(); i++){
		areasVec[i]->info.items.destroyList(); 
	}
	InsertItems();
}

friend ostream& operator<<(ostream& os, MapV2& map){
			os<<"******************************************************************"<<endl;
			os<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			os<<"******************************************************************"<<endl;
			for(int i=0; i<map.areasVec.size(); i++){
				os<<"This is area: "<<i+1<<endl;
				os<<map.areasVec[i]->info.getDescription()<<endl;
				if(map.areasVec[i]->info.getID() == 1){
					os<<"Area is INSTADEATH."<<endl;
				}
				if(map.areasVec[i]->info.getGoal() == 1){
					os<<"Area is GOAL."<<endl;
				}
				os<<"Connections:"<<endl;
				os<<"\t u: Area #"<<map.reverseLookUp(map.areasVec[i]->u)<<endl;
				os<<"\t d: Area #"<<map.reverseLookUp(map.areasVec[i]->d)<<endl;
				os<<"\t l: Area #"<<map.reverseLookUp(map.areasVec[i]->l)<<endl;
				os<<"\t r: Area #"<<map.reverseLookUp(map.areasVec[i]->r)<<endl;
			}
			for (int i = 0; i < map.areasVec.size(); i++){
				
				os<<"\nItems for area " << i << ": " << map.areasVec[i]->info.getDescription() << endl;
				map.areasVec[i]->info.items.printNames();
			};
			return os;
		}

};
#endif //MAPV2_H