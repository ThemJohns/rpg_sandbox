#ifndef CHARACTER_H
#define CHARACTER_H

#include "skills.h"

#include <iostream>
#include <vector>

using namespace std;

class Character {
	protected:
		string name;
		int hp;
		int maxhp;
		int mindamage;
		int maxdamage;
		int defense;
		int damagebonus;
		int damagebonus2;
		int defbonus;
		int defbonus2;
		int defmulti;
		int hpregen;
		int * status;		//Turns left of status effect
	public:
		Character();
		~Character();
		string getName();
		int getHp();
		int getMaxHp();
		int getMinDmg();
		int getMaxDmg();
		int getDef();
		int getHpRegen();
		void addAttack(int);
		void setAttack2(int);
		void addDefense(int);
		void setDefense2(int);
		void setDefMulti(int);
		int checkStatus(int);
		double getHpPercent();
		bool isLowHP();
		bool checkSkill(int);
		int dealDamage(int,int);		//Damage, type
		void Heal(int);
		void applyStatus(int,int);
		void removeStatus(int);
		void statusTimer();
		void viewStatus();
};

class Player : public Character {
	private:
		int classType;	//1 = Warrior, 2 = Rogue, 3 = Mage
		int level;
		int spellpower;
		int mana;
		int maxmana;
		int manaregen;
		int hpperlvl;
		int manaperlvl;
		int damageperlvl;
		double critmulti;	//Only used by Rogues
		std::vector<Skill> skills;
		std::vector<Skill> magic;
		std::vector<int> passives;
	public:
		Player();
		Player(string);
		int getClass();
		int getLevel();
		int getSpellPower();
		int getMana();
		int getMaxMana();
		int getManaRegen();
		int getHpPerLvl();
		int getManaPerLvl();
		int getDamagePerLvl();
		double getCritMulti();
		bool checkPassive(int);
		Skill& getSkill(int);
		Skill& getSpell(int);
		void getSkillList();
		int getSkillLength();
		void getSpellList();
		int getSpellLength();
		int getSkillCooldownTimer(int);
		int getMagicCooldownTimer(int);
		void cooldownTimer();
		bool canUseSkill(int);
		bool canUseSpell(int);
		void chooseClass();
		void setClassSkills(int);
		void chooseEquips(int);
		void equipItem(int);
		void WisdomBonus();
		void printStatSheet();
		void restoreMana(int);
		void deductMana(int);
		void levelUp();
		double returnDamageTaken();
		int rollCrit(int);
		void Regenerate();
};

class Enemy : public Character {
	private:
		//std::vector<int> prefix;
		int * prefix;
		int pref_len;
		//std::vector<int> suffix;
		int * suffix;
		int suff_len;
	public:
		Enemy();
		~Enemy();
		void getBossAffix();
		void printEnemyStats();
		void generateEnemy(int);
		bool checkAffix(int);
		double returnDamageTaken(int);
		int rollCrit(int);
};

void createPlayer();
string getAffixName(int);

#endif