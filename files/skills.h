#ifndef SKILLS_H
#define SKILLS_H

//#include "character.h"

#include <string>
#include <iostream>

using namespace std;

class Skill {
	private:
		int id;
		string name;
		int manacost;
		int cooldown;			//Cooldown timer
	public:
		Skill();
		Skill(int);				//id
		void setValues();
		int getID();
		string getName();
		int getManaCost();
		void reduceManaCost();
		int getCooldownTime();
		bool onCooldown();
		void setCooldown();
		void reduceCooldown();
		void refreshCooldown();
		void getSkillStats();
};

Skill addSkill(int);
string getPassiveName(int);
void getSkillInfo(int);
string getStatusName(int);


#endif