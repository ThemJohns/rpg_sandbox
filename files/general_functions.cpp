#include "general_functions.h"
#include "skills.h"

using namespace std;

void PressEnter(string text)  {
	cout << text << endl;
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

//Gets input and return it it's a number
int validNumber(string s)
{
    int x;
	cout << s << " ";
	cin >> x;
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Bad entry. Enter a NUMBER." << endl;
		cin >> x;
	}
	return x;
}

//Get Y/N and return true/false
bool yesOrNo(string s) {
	string x;
	while(true){
		cout << s << " (y/n) ";
	    cin >> x;
		if(x == "y") {
			return true;
		} else if (x == "n") {
			return false;
		} 
	}
}

//Generate a random number between x and y
int randomNumber(int x, int y) {
	if(x > y) {
		int temp = x;
		x = y;
		y = temp;
	}
	if (y == 1) {
		return rand() % (y - x + 1) + x;
	} else {
		return rand() % (y - x + 1) + x;
	}
}

//Multiply int by damage modifier and return it as an int;
int modifyDamage(int d, double m) {
	double dmg = static_cast<double>(d);
	int t = static_cast<int>(dmg * m);
	return t;
}

//The Manual
void viewManual() {
	int select;
	bool exit = false;
	do {
		cout << endl << "Select a topic to review:" << endl
			<< "1) Gameplay" << endl
			<< "2) Player" << endl
			<< "3) Enemy" << endl
			<< "4) Exit" << endl;
		select = validNumber("Select an option:");
		switch(select) {
			case 1:		//Gameplay
				do {
					cout << endl << "Choose a topic to review:" << endl
						<< "1) Rules" << endl
						<< "2) Stats" << endl
						<< "3) Back" << endl;
					select = validNumber("Select an option:");
					switch(select) {
						case 1:	//Rules
							cout << endl << "==Rules==" << endl
								<< "This a basic RPG the only has combat." << endl
								<< "The goal is to just survive as long as you can against a randomly generated dummy." << endl
								<< "Pick you class and equipment and make do with the skills ou get." << endl
								<< "The EXP system is simple: each time you win, you level up, and so does the enemy." << endl
								<< "Each time you level up, you get to choose a stat to level again, or gain 1 Spell Power" << endl
								<< "You also get the option to level Defense every 3 levels." << endl
								<< "You will recover full HP and half your Mana each time you level up." << endl
								<< "Also, for the record, each hit can't deal less than 1 damage." << endl;
							exit = false;
							break;
						case 2:	//Stats
							cout << endl << "==Stats==" << endl
								<< "- HP: Your life force. If it drops to 0, it's game over." << endl
								<< "- Mana: Used for skills. You need enough of these to use it." << endl
								<< "- Damage: How much you deal with the 'Attack' command or physical skills. Damage is randomized within a range." << endl
								<< "- Defense: Defense reduces damage. How much damage is based on the type of attack:" << endl
								<< "* vs. Physical: Damage is reduced by a percentage, equal to a factor of 1 - {Defense / (Defense + 8)} if it's positive." << endl
								<< "  If it's negative, each negative point of Defense increases the damage you take by 10%."
								<< "  (For example, 2 Defense will reduce damage by 20% (2/10), and -4 Defense will increase damage taken by 40%.)"
								<< "* vs. Magical: Subtracts the total damage taken equal to your Defense (or add if it's negative)." << endl
								<< "Spell Power: Increases the damage of damage-dealing Spells by 1 per Spell Power per character level." << endl
								<< "  (For example, +5 Spell Power at Level 5 means your Spell will deal 25 more damage.)" << endl;
							exit = false;
							break;
						case 3:
							exit = true;
							break;
						default:
							exit = false;
							break;
					}
				} while (!exit);
				exit = false;
				break;
			case 2:
				do {
					cout << endl << "Select a class to learn about its active skills:" << endl
						<< "1) Warrior" << endl
						<< "2) Rogue" << endl
						<< "3) Wizard" << endl
						<< "4) Back" << endl;
					select = validNumber("Select an option:");
					switch(select) {
						case 1:
							cout << endl << "WARRIOR" << endl << "________" << endl;
							cout << "Description: Your generic physical class. Good at hitting things and at living." << endl << endl
								<< "Starting Stats:" << endl << "HP: 40 (+15/Lvl)" << endl << "Mana: 12 (+2/Lvl)" << endl << "Damage: 3-4 (+2/Lvl)" << endl << "Defense: 3" << endl
								<< "Battle Skills: Double Strike, Charge Attack, Bash, Wrath, Vigor" << endl
								<< "Spells: Fire, Heal, Shield" << endl;
							do {
								cout << endl << "Select a skill to review:" << endl
									<< "1) Double Strike" << endl
									<< "2) Charge Attack" << endl
									<< "3) Bash" << endl
									<< "4) Ancestor's Wrath" << endl
									<< "5) Vigor" << endl
									<< "6) Fire" << endl
									<< "7) Heal" << endl
									<< "8) Shield" << endl
									<< "9) Exit" << endl;
								select = validNumber("Select an option:");
								switch(select) {
									case 1:
										getSkillInfo(111);
										exit = false;
										break;
									case 2:
										getSkillInfo(112);
										exit = false;
										break;
									case 3:
										getSkillInfo(113);
										exit = false;
										break;
									case 4:
										getSkillInfo(114);
										exit = false;
										break;
									case 5:
										getSkillInfo(115);
										exit = false;
										break;
									case 6:
										getSkillInfo(401);
										exit = false;
										break;
									case 7:
										getSkillInfo(403);
										exit = false;
										break;
									case 8:
										getSkillInfo(404);
										exit = false;
										break;
									case 9:
										exit = true;
										break;
									default:
										exit = false;
										break;
								}
							} while (!exit);
							exit = false;
							break;
						case 2:
							cout << endl << "ROGUE" << endl << "________" << endl;
							cout << "Description: Your average trickster. Kills its enemies through multiple hits." << endl << endl
								<< "Starting Stats:" << endl << "HP: 30 (+12/Lvl)" << endl << "Mana: 15 (+3/Lvl)"  << endl << "Damage: 5-6 (+3/Lvl)" << endl << "Defense: 1" << endl
								<< "Battle Skills: Volley, Explosive Arrow, Lifesteal, Poison Dart, Coup de Grace" << endl
								<< "Spells: Bolt, Weaken, Heal" << endl;
							do {
								cout << endl << "Select a skill to review:" << endl
									<< "1) Volley" << endl
									<< "2) Explosive Arrow" << endl
									<< "3) Lifesteal" << endl
									<< "4) Poison Dart" << endl
									<< "5) Coup de Grace" << endl
									<< "6) Bolt" << endl
									<< "7) Weaken" << endl
									<< "8) Heal" << endl
									<< "9) Exit" << endl;
								select = validNumber("Select an option:");
								switch(select) {
									case 1:
										getSkillInfo(211);
										exit = false;
										break;
									case 2:
										getSkillInfo(212);
										exit = false;
										break;
									case 3:
										getSkillInfo(213);
										exit = false;
										break;
									case 4:
										getSkillInfo(214);
										exit = false;
										break;
									case 5:
										getSkillInfo(215);
										exit = false;
										break;
									case 6:
										getSkillInfo(402);
										exit = false;
										break;
									case 7:
										getSkillInfo(405);
										exit = false;
										break;
									case 8:
										getSkillInfo(403);
										exit = false;
										break;
									case 9:
										exit = true;
										break;
									default:
										exit = false;
										break;
								}
							} while (!exit);
							exit = false;
							break;
						case 3:
							cout << endl << "WIZARD" << endl << "________" << endl;
							cout << "Description: Your typical spellcaster. Has many ways to blow up enemies and protect themselves." << endl << endl
								<< "Starting Stats:" << endl << "HP: 25 (+8/Lvl)" << endl << "Mana: 25 (+5/Lvl)"  << endl << "Damage: 1-2 (+1/Lvl)" << endl << "Defense: 0" << endl
								<< "Battle Skills: Magic Blade, Mana Drain, Focus" << endl
								<< "Spells: Inferno, Freeze, Shock, Heal, Barrier" << endl;
							do {
								cout << endl << "Select a skill to review:" << endl
									<< "1) Magic Blade" << endl
									<< "2) Mana Drain" << endl
									<< "3) Focus" << endl
									<< "4) Inferno" << endl
									<< "5) Freeze" << endl
									<< "6) Shock" << endl
									<< "7) Heal" << endl
									<< "8) Barrier" << endl
									<< "9) Exit" << endl;
								select = validNumber("Select an option:");
								switch(select) {
									case 1:
										getSkillInfo(311);
										exit = false;
										break;
									case 2:
										getSkillInfo(312);
										exit = false;
										break;
									case 3:
										getSkillInfo(313);
										exit = false;
										break;
									case 4:
										getSkillInfo(406);
										exit = false;
										break;
									case 5:
										getSkillInfo(407);
										exit = false;
										break;
									case 6:
										getSkillInfo(408);
										exit = false;
										break;
									case 7:
										getSkillInfo(403);
										exit = false;
										break;
									case 8:
										getSkillInfo(409);
										exit = false;
										break;
									case 9:
										exit = true;
										break;
									default:
										exit = false;
										break;
								}
							} while (!exit);
							exit = false;
							break;
						case 4:
							exit = true;
							break;
						default:
							exit = false;
							break;
						}
					} while (!exit);
				exit = false;
				break;
			case 3:
				cout << endl << "==Enemy==" << endl 
					<< "There is only one enemy in this game: a Dummy." << endl
					<< "The dummy has the following stats:" << endl
					<< "HP: 30 (+25/Lvl)" << endl
					<< "Damage: 5-6 (3-4/Lvl)" << endl
					<< "Defense: 0 (+1 Every 2 Levels)" << endl
					<< "Like the player, the dummy gains a level with each fight." << endl
					<< "Dummies also have an Affix that gives it bonus effects to make it tougher." << endl
					<< "Dummies start with 1 random Affix (except the Level 1 Dummy) and 2 Affixes at Level 8." << endl
					<< "You will fight a Boss Dummy every 5 levels, which has 3 Affixes at start and gains another one with each encounter, up to a total of 6." << endl
					<< "Regular Dummies can have 1 Prefix/Suffix each, while Boss Dummies can have up to 3 Prefix/Suffix. each";
				do {
				cout << endl << "Choose a topic to review:" << endl
					<< "1) Prefix" << endl
					<< "2) Suffix" << endl
					<< "3) Back" << endl;
					select = validNumber("Select an option:");
					switch(select) {
						case 1:
							cout << "===Prefixes===" << endl
								<< "- Strong: 25% increased attack damage." << endl
								<< "- Arcane: Attacks deal magic damage." << endl
								<< "- Deadly: Has a 25% chance to deal 1.5x damage." << endl
								<< "- Toxic: Player loses HP equal to 10% max HP at the end of player's turn." << endl
								<< "- Vampiric: Heals equal to 25% of damage dealt." << endl
								<< "- Angry: Gains 1 to 3 Attack after attacking (until battle ends)." << endl
								<< "- Weakening: On attack, 65% chance of reducing player's Defense by 1 (until battle ends)." << endl;
							exit = false;
							break;
						case 2:
							cout << "===Suffixes===" << endl
								<< "- Vitality: 30% more HP." << endl
								<< "- Sturdiness: 40% physical damage reduction." << endl
								<< "- Resistance: 40% magic damage reduction." << endl
								<< "- Regeneration: Heals 5% of its HP at the end of its turn." << endl
								<< "- Spikes: Reflects 20% of damage from hits taken from player." << endl
								<< "- Nullification: Every 3 turns, removes debuffs from self and buffs from player at start of turn." << endl
								<< "- Fury: At 1/3 HP, gains x5 Defense and deals 50% more damage." << endl;
							exit = false;
							break;
						case 3:
							exit = true;
							break;
						default:
							exit = false;
							break;
					}
				} while (!exit);
				exit = false;
				break;
			case 4:
				exit = true;
				break;
			default:
				exit = false;
				break;
		}
	} while(!exit);
}