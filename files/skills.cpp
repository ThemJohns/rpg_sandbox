#include "skills.h"
#include "general_functions.h"

#include <iostream>
#include <string>

using namespace std;

Skill::Skill() {	//Not used
	id = 0;
	name = "";
	int manacost = 0;
	int cooldown = 0;
}

Skill::Skill(int a) {		//Creates Skill with ID
	id = a;
	name = "";
	int manacost = 0;
	int cooldown = 0;
}

//Set skill name and mana cost based on ID
void Skill::setValues(){
	switch(id){
	//Warrior Skills
	case 111:
		name = "Double Strike";
		break;
	case 112:
		name = "Charge Attack";
		break;
	case 113:
		name = "Bash";
		break;
	case 114:
		name = "Wrath";
		break;
	case 115:
		name = "Vigor";
		break;
	//Rogue Skills
	case 211:
		name = "Volley";
		break;
	case 212:
		name = "Explosive Arrow";
		break;
	case 213:
		name = "Lifesteal";
		break;
	case 214:
		name = "Poison Dart";
		break;
	case 215:
		name = "Coup de Grace";
		break;
	//Wizard Skills
	case 311:
		name = "Magic Blade";
		break;
	case 312:
		name = "Mana Drain";
		break;
	case 313:
		name = "Focus";
		break;
	//Magic
	case 401:
		name = "Fire";
		break;
	case 402:
		name = "Bolt";
		break;
	case 403:
		name = "Heal";
		break;
	case 404:
		name = "Shield";
		break;
	case 405:
		name = "Weaken";
		break;
	case 406:
		name = "Inferno";
		break;
	case 407:
		name = "Freeze";
		break;
	case 408:
		name = "Shock";
		break;
	case 409:
		name = "Barrier";
		break;
	}
	switch(id){
	//Warrior Skills
	case 111:
		manacost = 3;
		break;
	case 112:
		manacost = 4;
		break;
	case 113:
		manacost = 3;
		break;
	case 114:
		manacost = 5;
		break;
	case 115:
		manacost = 3;
		break;
	//Rogue Skills
	case 211:
		manacost = 3;
		break;
	case 212:
		manacost = 4;
		break;
	case 213:
		manacost = 4;
		break;
	case 214:
		manacost = 5;
		break;
	case 215:
		manacost = 6;
		break;
	//Wizard Skills
	case 311:
		manacost = 3;
		break;
	case 312:
		manacost = 1;
		break;
	//Magic
	case 401:
		manacost = 3;
		break;
	case 402:
		manacost = 3;
		break;
	case 403:
		manacost = 3;
		break;
	case 404:
		manacost = 4;
		break;
	case 405:
		manacost = 4;
		break;
	case 406:
		manacost = 8;
		break;
	case 407:
		manacost = 6;
		break;
	case 408:
		manacost = 6;
		break;
	case 409:
		manacost = 10;
		break;
	default:
		manacost = 0;
		break;
	}
	cooldown = 0;
}

int Skill::getID() {
	return id;
}

string Skill::getName() {
	return name;
}

int Skill::getManaCost() {
	return manacost;
}

void Skill::reduceManaCost() {
	manacost--;
}

int Skill::getCooldownTime() {
	return cooldown;
}

void Skill::getSkillStats() {
	cout << name;
	if(manacost > 0) {
		cout << " (" << manacost << " Mana)";
	}
	if(cooldown > 0) {
		cout << " [COOLDOWN: " << cooldown << " turn(s)]"; 
	}
	cout << endl;
}

//Returns true if skill is on cooldown
bool Skill::onCooldown() {
	if(cooldown > 0) {
		return true;
	}
	return false;
}

//Places skill on cooldown based on ID.
void Skill::setCooldown() {
	switch(id){
	//Warrior Skills
	case 113:
		cooldown = 2;
		break;
	case 114:
		cooldown = 3;
		break;
	case 115:
		cooldown = 4;
		break;
	//Rogue Skills
	case 213:
		cooldown = 3;
		break;
	case 214:
		cooldown = 6;
		break;
	case 215:
		cooldown = 4;
		break;
	//Wizard Skills
	case 312:
		cooldown = 4;
		break;
	case 313:
		cooldown = 2;
		break;
	//Magic
	case 407:
		cooldown = 6;
		break;
	case 408:
		cooldown = 2;
		break;
	case 409:
		cooldown = 6;
		break;
	default:
		cooldown = 1;
		break;
	}
}

//Lowers cooldown by 1 turn
void Skill::reduceCooldown() {
	if(cooldown > 0) cooldown--;
}

//Sets cooldown to 0
void Skill::refreshCooldown() {
	cooldown = 0;
}

//Prints description of skill/equipment based on ID.
void getSkillInfo(int id){
	switch(id){
	//Warrior Skills
	case 101:
		cout << "Berserker: Gain 2 Attack for every 10% of missing HP." << endl;
		break;
	case 102:
		cout << "Reckless: Deal 50% more physical damage, but take 20% increased damage." << endl;
		break;
	case 103:
		cout << "Blood Knight: Each physical hit you land heals you for 10% of missing HP." << endl;
		break;
	case 104:
		cout << "Fortify: You gain 2 Attack every odd turns and 1 Defense every even turns (until battle ends)." << endl;
		break;
	case 105:
		cout << "Last Stand: If you are below 1/3 HP, gain 20 Defense." << endl;
		break;
	case 111:
		cout << "Double Strike: Hits twice, dealing 150% damage each hit. (3 Mana)" << endl;
		break;
	case 112:
		cout << "Charge Attack: Charge up for an attack. On next turn, deal 500% attack damage. Gain 40% damage reduction while charging. (4 Mana)" << endl;
		break;
	case 113:
		cout << "Bash: Deal 200% attack damage and stuns the enemy for 1 turn. (3 Mana, 1 turn cooldown)" << endl;
		break;
	case 114:
		cout << "Wrath: Deal 300% attack damage, ignoring defense. (5 Mana, 2 turn cooldown)" << endl;
		break;
	case 115:
		cout << "Vigor: After getting attacked, heal for 500% of damage taken. (Buff, 3 Mana, 3 turn cooldown)" << endl;
		break;
	break;

	//Rogue Skills
	case 201:
		cout << "Critical Hit: Your physical hits have a 20% chance to deal 1.5x damage." << endl;
		break;
	case 202:
		cout << "Wild Strikes: Each physical hit gains 0 to (x2 Level) damage." << endl;
		break;
	case 203:
		cout << "Quickening: Doubles cooldown recovery." << endl;
		break;
	case 204:
		cout << "Reflex: You have a 15% chance to dodge physical attacks. Automatically attack upon dodging an attack." << endl;
		break;
	case 205:
		cout << "Lucky: Increases your Critical Hit chance to 35% or increases the dodge chance from Reflex to 25%." << endl;
		break;
	case 211:
		cout << "Volley: Hits 4 times, dealing 60% attack damage per hit. (3 Mana)" << endl;
		break;
	case 212:
		cout << "Explosive Arrow: Deals 50% damage on hit. Next turn, the arrow explodes and deals 250% attack damage. (4 Mana)" << endl;
		break;
	case 213:
		cout << "Lifesteal: Deal 200% attack damage and heals you equal to the damage dealt (4 Mana, 2 turn cooldown)" << endl;
		break;
	case 214:
		cout << "Poison Dart: Deal 1 damage and stuns enemy. Enemy loses 20% of its current HP for 3 turns. (Debuff, 5 Mana, 5 turn cooldown)" << endl;
		break;
	case 215:
		cout << "Coup De Grace: Deal 350% attack damage. If the enemy is below 1/3 HP, deal 700% damage instead. (6 Mana, 3 turn cooldown)" << endl;
		break;

	//Wizard Skills
	case 301:
		cout << "Wisdom: -1 Mana Cost, status effects you apply last 1 turn longer." << endl;
		break;
	case 302:
		cout << "Overload: Deal 50% more damage with spells, but lose 1 Defense per 2 Mana spent every time you cast a damaging spell (until battle ends)." << endl;
		break;
	case 303:
		cout << "Amplify: Your damaging skills deal additional magic damage equal to your Level + Spell Power." << endl;
		break;
	case 304:
		cout << "Recycle Mana: Heal equal to 2x Mana spent." << endl;
		break;
	case 305:
		cout << "Mana Shield: Gain 1 Defense for every 20 Mana you have." << endl;
		break;
	case 311:
		cout << "Magic Blade: Hit twice for 100% Attack damage each. The second hit deals magic damage and gains spell bonuses. (3 Mana)" << endl;
		break;
	case 312:
		cout << "Mana Drain: Deal your Attack Damage and gain Mana equal to half your Level (rounded down). (1 Mana, 3 turn cooldown) " << endl;
		break;
	case 313:
		cout << "Focus: Restore 2 Mana and doubles spell damage bonus from your level on your next attack. (1 turn cooldown)" << endl;
		break;

	//Magic
	case 401:
		cout << "Fire: Deal 6 magic damage + 3 per level. (3 Mana)" << endl;
		break;
	case 402:
		cout << "Bolt: Deal 8 magic damage + 5 per level. (4 Mana)" << endl;
		break;
	case 403:
		cout << "Heal: Heal 14 HP + 6 per level. (3 Mana)" << endl;
		break;
	case 404:
		cout << "Shield: Gain 5 Defense for 4 turns. (Buff, 4 Mana)" << endl;
		break;
	case 405:
		cout << "Weaken: Enemy deals 30% less damage and takes 30% more damage for 3 turns. (Debuff, 4 Mana)" << endl;
		break;
	case 406:
		cout << "Inferno: Deals 14 magic damage + 8 per level. (8 Mana)" << endl;
		break;
	case 407:
		cout << "Freeze: Stuns the enemy for 2 turns. (6 Mana, 5 turn cooldown)" << endl;
		break;
	case 408:
		cout << "Shock: Damages the enemy 2-4 times, each hit dealing 1 to 2x level damage. Bonus damage increases maximum damage. (6 Mana, 1 turn cooldown)" << endl;
		break;
	case 409:
		cout << "Barrier: Gain 30% damage reduction for 3 turns. (Buff, 10 Mana, 5 turn cooldown)" << endl;
		break;

	//Warrior Equipment
	case 511:
		cout << "Steel Axe: A simple, reliable axe. +7-8 Damage" << endl;
		break;
	case 512:
		cout << "Flail: Strong, but unpredictable. +3-14 Damage" << endl;
		break;
	case 513:
		cout << "Cursed Blade: Powerful, but weakens you. +14-18 Damage, -30 HP, -4 Defense" << endl;
		break;
	case 514:
		cout << "Platemail: +4 Defense" << endl;
		break;
	case 515:
		cout << "Rune Plate: +20 HP, +6 Mana, +2 Spell Power" << endl;
		break;
	case 516:
		cout << "Loincloth: +30 HP, +5 HP Regen per turn" << endl;
		break;
	//Rogue Equipment
	case 521:
		cout << "Dagger: A rogue's trademark. +8-9 Damage" << endl;
		break;
	case 522:
		cout << "Parrying Dagger: Not sharp, but helps you defend. +5-7 Damage, +2 Defense" << endl;
		break;
	case 523:
		cout << "Assassin's Knife: Tricky, but deadly. +1-2 Damage, Critical Hits deal 2x damage" << endl;
		break;
	case 524:
		cout << "Leather Armor: +20 HP, +2 Defense" << endl;
		break;
	case 525:
		cout << "Bandit Gear: +10 HP, +10 Mana, +1 Mana Regen per turn" << endl;
		break;
	case 526:
		cout << "Ninja Outfit: -3 Defense, +6 Damage, +3 Spell Power" << endl;
		break;
	//Mage Equipment
	case 531:
		cout << "Staff: Typical magic catalyst. +2-3 Damage, +4 Spell Power" << endl;
		break;
	case 532:
		cout << "Magic Sword: Jack of all trades. +6-7 Damage, +2 Spell Power, +2 Defense" << endl;
		break;
	case 533:
		cout << "Mystic Orb: Filled with magic. +6 Spell Power, +1 Mana Regen per turn" << endl;
		break;
	case 534:
		cout << "Wizard Robe: +20 HP, +10 Mana" << endl;
		break;
	case 535:
		cout << "Magic Armor: +3 Defense, +15 Mana" << endl;
		break;
	case 536:
		cout << "Blessed Robe: +7 HP Regen per turn, +1 Mana Regen per turn" << endl;
		break;
	}
}

//Returns status name based on ID.
string getStatusName(int id) {
	string s;
	switch(id){
	case 0: 
		s = "Stun";
		break;
	case 1: 
		s = "Charge Attack";
		break;
	case 2: 
		s = "Vigor";
		break;
	case 3: 
		s = "Explosive Arrow";
		break;
	case 4: 
		s = "Poison Dart";
		break;
	case 5: 
		s = "Focus";
		break;
	case 6: 
		s = "Shield";
		break;
	case 7: 
		s = "Weaken";
		break;
	case 8: 
		s = "Barrier";
		break;
	default:
		s = "ERROR";
		break;
	}
	return s;
}
/*
0: Stun
1: Charge Attack
2: Vigor
3: Explosive Arrow	(Stores damage value)
4: Poison Dart
5: Focus
6: Shield
7: Weaken
8: Barrier
*/

string getPassiveName(int id){
	string s;
	switch(id){
	case 101:
		s = "Berserker";
		break;
	case 102:
		s = "Reckless";
		break;
	case 103:
		s = "Blood Knight";
		break;
	case 104:
		s = "Fortify";
		break;
	case 105:
		s = "Last Stand";
		break;
	case 201:
		s = "Critical Hit";
		break;
	case 202:
		s = "Wild Strikes";
		break;
	case 203:
		s = "Quickening";
		break;
	case 204:
		s = "Reflex";
		break;
	case 205:
		s = "Lucky";
		break;
	case 301:
		s = "Wisdom";
		break;
	case 302:
		s = "Overload";
		break;
	case 303:
		s = "Magic Boost";
		break;
	case 304:
		s = "Blood Magic";
		break;
	case 305:
		s = "Mana Shield";
		break;
	}
	return s;
}

//Returns a skill with values pre-determined based on ID
Skill addSkill(int id) {
	Skill newSkill(id);
	newSkill.setValues();
	return newSkill;
}
