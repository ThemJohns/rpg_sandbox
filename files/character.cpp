#include "general_functions.h"
#include "character.h"
#include "skills.h"
#include "battle_system.h"

using namespace std;

char select;
string input;
bool valid;
bool choice;

Character::Character() {	//Not used
	name = "";
	hp = 0;
	maxhp = 0;
	mindamage = 0;
	maxdamage = 0;
	damagebonus = 0;
	damagebonus2 = 0;
	defense = 0;
	defbonus = 0;
	defbonus2 = 0;
	defmulti = 1;
	hpregen = 0;
	status = new int[9];
	for(int i = 0; i < 9; i++) {
		status[i] = 0;
	}
}

Character::~Character() {
	delete [] status;
}

string Character::getName() {
	return name;
}

int Character::getHp() {
	return hp;
}

int Character::getMaxHp() {
	return maxhp;
}

int Character::getMinDmg() {
	return mindamage + damagebonus + damagebonus2;
}

int Character::getMaxDmg() {
	return maxdamage + damagebonus + damagebonus2;
}

int Character::getDef() {
	int d = (defense + defbonus + defbonus2) * defmulti;
	if(status[6] > 0) d += 5;
	return d;
}

int Character::getHpRegen() {
	return hpregen;
}

//Add damage bonus
void Character::addAttack(int a) {
	damagebonus += a;
}

void Character::setAttack2(int a) {
	damagebonus2 = a;
}

//Add defense bonus
void Character::addDefense(int d) {
	defbonus += d;
}

void Character::setDefense2(int d) {
	defbonus2 = d;
}

void Character::setDefMulti(int d) {
	defmulti = d;
}

//Check number of turns remaining on status effect
int Character::checkStatus(int id) {
	return status[id];
}

//Shows status effects applied
void Character::viewStatus() {
	bool hasStatus = false;
	int turns;

	cout << "Status Effects: " << endl;
	for(int i = 0; i < 10; i++) {
		turns = checkStatus(i);
		if(turns > 0) {
			cout << "- " << getStatusName(i) << " (" << turns << " turns)" << endl;
		}
	}
	if(!hasStatus) cout << "None" << endl;
}

//Returns character's HP percentage
double Character::getHpPercent() {
	double max = static_cast<int>(maxhp);
	double h = static_cast<int>(hp);

	return h / max;
}

//Returns true of character is under 1/3 HP
bool Character::isLowHP() {
	double max = static_cast<int>(maxhp);
	double h = static_cast<int>(hp);
	if ((h / max) < (1.0/3.0)) return true;

	return false;
}

 /* Reduce HP by specified number (Min 1, set HP to 0 if overkilled)
	Type: 0 = None, 1 = Physical, 2 = Magic	*/
int Character::dealDamage(int d, int type) {
	int dmg = d;

	if(type == 1) {		//Physical
		double d = static_cast<double>(defense);
		double r;
		if(d > 0) {
			r = 1.0 - (d / (d + 8.0));		//Damage reduction percentage
		} else {
			r = 1.0 + (d * 0.1);			//Damage increase if negative
		}
		dmg = modifyDamage(dmg,r);
	} else if (type == 2) {		//Magic
		dmg -= defense;
	}

	if (dmg < 0) dmg = 1;			//Set minimum damage

	hp -= dmg;					//Reduce HP
	if(hp < 0) hp = 0;			//Set to 0 to not display "overkill" damage
	cout << name << " takes " << dmg << " damage!" << endl;

	return dmg;
}

//Heal character, but not above max HP
void Character::Heal(int h) {
	hp += h;
	if(hp > maxhp) hp = maxhp;
	cout << name << " healed " << h << " HP!" << endl;
}

//Applies status effect with value
void Character::applyStatus(int id, int x) {
	status[id] = x;
}

//Sets a status effect's timer to 0, effectively removing it
void Character::removeStatus(int id) {
	if(status[id] > 0) {
		cout << getStatusName(id) << " was removed from " << name << "!" << endl;
	}
	status[id] = 0;
}

//Applies status effects and decrements effect timer
void Character::statusTimer() {
	int h;
	for(int i = 0; i < 9; i++) {
		if(status[i] > 0) {
			switch(i) {
			case 3:		//Explosive Arrow
				cout << "The arrow detonates!" << endl;
				this->dealDamage(status[3],0);
				status[3] = 1;
				break;
			case 4:		//Poison Dart
				cout << "The poison takes effect!" << endl;
				h = modifyDamage(hp,0.2);
				this->dealDamage(h,0);
			}
			status[i] -= 1;
		}
	}
}

Player::Player() {
	name = "";
	level = 1;
	hp = 0;
	mindamage = 0;
	maxdamage = 0;
	defense = 0;
	spellpower = 0;
	hpregen = 0;
	manaregen = 0;
	critmulti = 1.5;
}

Player::Player(string s) {
	name = s;
	level = 1;
	hp = 0;
	mindamage = 0;
	maxdamage = 0;
	defense = 0;
	spellpower = 0;
	hpregen = 0;
	manaregen = 0;
	critmulti = 1.5;
}

//Return value based on class
int Player::getClass() {
	return classType;
}

int Player::getLevel() {
	return level;
}

int Player::getSpellPower() {
	return spellpower;
}

int Player::getMana() {
	return mana;
}

int Player::getMaxMana() {
	return maxmana;
}

int Player::getManaRegen() {
	return manaregen;
}

int Player::getHpPerLvl() {
	return hpperlvl;
}

int Player::getManaPerLvl() {
	return manaperlvl;
}

int Player::getDamagePerLvl() {
	return damageperlvl;
}

double Player::getCritMulti() {
	return critmulti;
}

Skill& Player::getSkill(int i) {
	return skills[i];
}

Skill& Player::getSpell(int i) {
	return magic[i];
}

bool Player::canUseSkill(int i) {
	if(skills[i].getCooldownTime() > 0) {
		cout << "Skill is on cooldown." << endl;
		return false;
	}
	if(mana < skills[i].getManaCost()) {
		cout << "Not enough Mana." << endl;
		return false;
	}
	return true;
}

bool Player::canUseSpell(int i) {
	if(magic[i].getCooldownTime() > 0) {
		cout << "Spell is on cooldown." << endl;
		return false;
	}
	if(mana < magic[i].getManaCost()) {
		cout << "Not enough Mana." << endl;
		return false;
	}
	return true;
}

void Player::getSkillList() {
	int length = skills.size();
	int manacost = 0;
	int cooldown = 0;
	for(int i = 0; i < length; i++) {
		cout << i+1 << ") ";
		skills[i].getSkillStats();
	}
	cout << length+1 << ") Back" << endl;
}

void Player::getSpellList() {
	int length = magic.size();
	int manacost = 0;
	int cooldown = 0;
	for(int i = 0; i < length; i++) {
		cout << i+1 << ") ";
		magic[i].getSkillStats();
	}
	cout << length+1 << ") Back" << endl;
}

int Player::getSkillLength() {
	return skills.size();
}

int Player::getSpellLength() {
	return magic.size();
}

bool Player::checkPassive(int id){
	if (passives[0] == id || passives[1] == id) {
		return true;
	}
	return false;
}

//Return incoming damage multiplier
double Player::returnDamageTaken() {
	double multi = 1.0;
	if(checkPassive(102)) multi += 0.2;		//Reckless
	if(checkStatus(1) > 0) multi -= 0.4;	//Charge Attack
	if(checkStatus(8) > 0) multi -= 0.3;	//Barrier
	return multi;
}

//Modifies damage by crit value if it succeeds
int Player::rollCrit(int d) {
	double dmg = static_cast<double>(d);
	int chance = 20;
	if (this->checkPassive(205)) {		//Lucky
		chance = 35;
	} 
	
	if (randomNumber(1,100) <= chance) {
		cout << "CRITICAL HIT!!!" << endl;
		dmg = dmg * critmulti;
	}
	
	int x = static_cast<int>(dmg);
	return x;
}

//Decrements cooldowns
void Player::cooldownTimer() {
	for(unsigned int i = 0; i < skills.size(); i++) {
		skills[i].reduceCooldown();
	}
	for(unsigned int j = 0; j < magic.size(); j++) {
		magic[j].reduceCooldown();
	}
}

//Regenerates HP and Mana (if applicable)
void Player::Regenerate() {
	if (hpregen > 0) {
		hp += hpregen;
		if (hp > maxhp) hp = maxhp;
		cout << name << " regains " << hpregen << " HP!" << endl;
	}
	if (manaregen < 0) {
		mana += manaregen;
		if (mana > maxmana) mana = maxmana;
		cout << name << " regains " << manaregen << " Mana!" << endl;
	}
}

//Spends Mana
void Player::deductMana(int m) {
	mana -= m;
	if(mana < 0) mana = 0;
}

//Restores Mana to character, but not above max Mana
void Player::restoreMana(int m) {
	mana += m;
	if(mana > maxmana) mana = maxmana;
	cout << name << " restores " << m << " Mana!" << endl;
}

//Level up, increase stats, heal to full and remove status effects
void Player::levelUp(){
	cout << endl << "LEVEL UP!" << endl;
	level += 1;
	maxhp += hpperlvl;
	maxmana += manaperlvl;
	mindamage += damageperlvl;
	maxdamage += damageperlvl;
	
	cout << "You are now Level " << level << "!" << endl;
	cout << "Max HP increased to " << maxhp << "!" << endl;
	cout << "Max Mana increased to " << maxmana << "!" << endl;
	cout << "Damage increased to " << mindamage << "-" << maxdamage << "!" << endl;
	
	int choice;
	bool valid = false;
	cout << "Choose a level up bonus:" << endl
		<< "1) HP" << endl
		<< "2) Mana" << endl
		<< "3) Attack" << endl
		<< "4) Spell Power" << endl;
	if(level % 3 == 1) cout << "5) Defense" << endl;
	do {
		choice = validNumber("Select a choice:");
		switch(choice) {
			case 1:
				maxhp += hpperlvl;
				cout << "Max HP increased to " << maxhp << "!" << endl;
				valid = true;
				break;
			case 2:
				maxmana += manaperlvl;
				cout << "Max Mana increased to " << maxmana << "!" << endl;
				valid = true;
				break;
			case 3:
				mindamage += damageperlvl;
				maxdamage += damageperlvl;
				cout << "Damage increased to " << mindamage << "-" << maxdamage << "!" << endl;
				valid = true;
				break;
			case 4:
				spellpower += 1;
				cout << "Spell Power increased to " << spellpower << "!" << endl;
				valid = true;
				break;
			case 5:
				if(level % 3 == 1) {
					defense += 1;
					cout << "Defense increased to " << defense << "!" << endl;
					valid = true;
				} else {
					valid = false;
				}
				break;
		}
	} while(!valid);

	//Heal & reset values
	hp = maxhp;
	mana += maxmana / 2;
	if(mana > maxmana) mana = maxmana;
	damagebonus = 0;
	damagebonus2 = 0;
	defbonus = 0;
	defbonus2 = 0;
	for(int i = 0; i < 9; i++) {
		status[i] = 0;
	}
	for(unsigned int x = 0; x < skills.size(); x++) {
		skills[x].refreshCooldown();
	}
	for(unsigned int y = 0; y < magic.size(); y++) {
		magic[y].refreshCooldown();
	}
}

//Apply equipment bonuses based on choices.
void Player::equipItem(int id){
	switch(id){
		//Warrior Equipment
		case 511:	//Steel Axe
			mindamage += 7;
			maxdamage += 8;
			break;
		case 512:	//Flail
			mindamage += 3;
			maxdamage += 14;
			break;
		case 513:	//Cursed Blade
			mindamage += 14;
			maxdamage += 18;
			maxhp -= 30;
			defense -= 4;
			break;
		case 514:	//Platemail
			defense += 4;
			break;
		case 515:	//Rune Plate
			maxhp += 20;
			maxmana += 6;
			spellpower += 2;
			break;
		case 516:	//Loincloth
			maxhp += 30;
			hpregen += 5;
			break;
		//Rogue Equipment
		case 521:	//Dagger
			mindamage += 8;
			maxdamage += 9;
			break;
		case 522:	//Parrying Dagger
			mindamage += 5;
			maxdamage += 7;
			defense += 2;
			break;
		case 523:	//Assassin's Knife
			mindamage += 1;
			maxdamage += 2;
			critmulti = 2.0;
			break;
		case 524:	//Leather Armor
			maxhp += 20;
			defense += 2;
			break;
		case 525:	//Bandit Gear
			maxhp += 10;
			maxmana += 10;
			manaregen += 1;
			break;
		case 526:	//Ninja Outfit
			defense -= 3;
			mindamage += 6;
			maxdamage += 6;
			spellpower += 3;
			break;
		//Mage Equipment
		case 531:	//Staff
			mindamage += 2;
			maxdamage += 3;
			spellpower += 4;
			break;
		case 532:	//Magic Sword
			mindamage += 6;
			maxdamage += 7;
			spellpower += 2;
			defense += 2;
			break;
		case 533:	//Mystic Orb
			spellpower += 6;
			manaregen += 1;
			break;
		case 534:	//Wizard Robe
			maxhp += 20;
			maxmana += 10;
			break;
		case 535:	//Magic Armor
			maxmana += 15;
			defense += 3;
			break;
		case 536:	//Blessed Robe
			hpregen += 7;
			manaregen += 1;
			break;
	}
}

//Choose equipment bonuses.
void Player::chooseEquips(int c){
	int choice1;
	int choice2;
	int idmod;

	if(c == 1) {	//Warrior
		idmod = 510;
	} else if (c == 2) {	//Rogue
		idmod = 520;
	} else if (c == 3) {	//Wizard
		idmod = 530;
	}

	do {
		cout << "Choose your weapon:" << endl;
		for(int i = 1; i < 4; i++) {
			cout << i << ") ";
			getSkillInfo((idmod + i));
		}
		while(true) {
			choice1 = validNumber("Select your choice:");
			if(choice1 > 0 && choice1 < 4) break;
		}
		cout << "Choose your armor:" << endl;
		for(int i = 4; i < 7; i++) {
			cout << (i-3) << ") ";
			getSkillInfo((idmod + i));
		}
		while(true) {
			choice2 = validNumber("Select your choice:");
			if(choice2 > 0 && choice1 < 4) break;
		}
		choice1 += idmod;
		choice2 = choice2 + idmod + 3;

		cout << endl << "You have chosen the following equipment:" << endl;
		cout << "- ";
		getSkillInfo(choice1);
		cout << "- ";
		getSkillInfo(choice2);
		choice = yesOrNo("Is this what you want?");
		if(choice) {
			equipItem(choice1);
			equipItem(choice2);
			//Heal to full
			hp = maxhp;
			mana = maxmana;
			valid = true;
		} else if(!choice) {
			valid = false;
		}
	} while(!valid);
}

//Add special skills based on the player's class
void Player::setClassSkills(int c){
	int choice1;
	int choice2;
	int idmod;

	if(c == 1) {	//Warrior
		idmod = 100;
	} else if (c == 2) {	//Rogue
		idmod = 200;
	} else if (c == 3) {	//Wizard
		idmod = 300;
	}

	do {
		cout << endl << "Choose 2 passive skills:" << endl;
		//Print skill descriptions
		for(int i = 1; i < 6; i++) {
			cout << i << ") ";
			getSkillInfo(idmod + i);
		}
		while(true){
			choice1 = validNumber("Choose your skill:");
			if(choice1 > 0 && choice1 < 6) break;
		}
		while(true){
			choice2 = validNumber("Choose another skill:");
			if(choice2 > 0 && choice2 < 6) {
				if(choice2 == choice1){
					cout << "You already chose that skill." << endl;
				} else {
					break;
				}
			}
		}
		choice1 += idmod;
		choice2 += idmod;

		//Print & confirm choices
		cout << endl << "You have chosen the following skills:" << endl;
		cout << "- ";
		getSkillInfo(choice1);
		cout << "- ";
		getSkillInfo(choice2);
		choice = yesOrNo("Are these the skills you want?");
		if(choice) {
			passives.push_back(choice1);
			passives.push_back(choice2);
			chooseEquips(c);
			valid = true;
		} else if(!choice) {
			valid = false;
		}
	} while (!valid);
}

//Choose the class and change their base stats to match (& reset character)
void Player::chooseClass() {
	//Reset stats & skills
	mindamage = 0;
	maxdamage = 0;
	defense = 0;
	spellpower = 0;
	hpregen = 0;
	manaregen = 0;
	critmulti = 1.5;
	while(!skills.empty()) {
		skills.pop_back();
	}
	while(!magic.empty()) {
		magic.pop_back();
	}
	while(!passives.empty()) {
		passives.pop_back();
	}

	//Select class
	do {
		cout << endl << "Choose your class:" << endl;
		cout << "1) Warrior" << endl;
		cout << "2) Rogue" << endl;
		cout << "3) Wizard" << endl;
		cin >> select;
		switch(select){
		case '1':
			cout << endl << "WARRIOR" << endl << "________" << endl;
			cout << "Description: Your generic physical class. Good at hitting things and at living." << endl << endl
				<< "Starting Stats:" << endl << "HP: 40 (+15/Lvl)" << endl << "Mana: 12 (+2/Lvl)" << endl << "Damage: 3-4 (+2/Lvl)" << endl << "Defense: 3" << endl
				<< "Battle Skills: Double Strike, Charge Attack, Bash, Wrath, Vigor" << endl
				<< "Spells: Fire, Heal, Shield" << endl;
			choice = yesOrNo("Is this the class you want?");
			if(choice) {
				//Set base stats
				classType = 1;
				maxhp = 40;
				hpperlvl = 15;
				maxmana = 12;
				manaperlvl = 2;
				mindamage = 3;
				maxdamage = 4;
				damageperlvl = 2;
				defense = 3;
				//Add class skills
				skills.push_back(addSkill(111));
				skills.push_back(addSkill(112));
				skills.push_back(addSkill(113));
				skills.push_back(addSkill(114));
				skills.push_back(addSkill(115));
				magic.push_back(addSkill(401));
				magic.push_back(addSkill(403));
				magic.push_back(addSkill(404));

				//Select class-specific skills
				setClassSkills(1);

				valid = true;
			} else if(!choice) {
				valid = false;
			}
			break;
		case '2':
			cout << endl << "ROGUE" << endl << "________" << endl;
			cout << "Description: Your average trickster. Kills its enemies through multiple hits." << endl << endl
				<< "Starting Stats:" << endl << "HP: 30 (+12/Lvl)" << endl << "Mana: 15 (+3/Lvl)"  << endl << "Damage: 5-6 (+3/Lvl)" << endl << "Defense: 1" << endl
				<< "Battle Skills: Volley, Explosive Arrow, Lifesteal, Poison Dart, Coup de Grace" << endl
				<< "Spells: Fire, Weaken, Heal" << endl;
			choice = yesOrNo("Is this the class you want?");
			if(choice) {
				//Set base stats
				classType = 2;
				maxhp = 30;
				hpperlvl = 12;
				maxmana = 15;
				manaperlvl = 3;
				mindamage = 5;
				maxdamage = 6;
				damageperlvl = 3;
				defense = 1;
				//Add class skills
				skills.push_back(addSkill(211));
				skills.push_back(addSkill(212));
				skills.push_back(addSkill(213));
				skills.push_back(addSkill(214));
				skills.push_back(addSkill(215));
				magic.push_back(addSkill(402));
				magic.push_back(addSkill(405));
				magic.push_back(addSkill(403));

				//Select class-specific skills
				setClassSkills(2);

				valid = true;
			} else if(!choice) {
				valid = false;
			}
			break;
		case '3':
			cout << endl << "WIZARD" << endl << "________" << endl;
			cout << "Description: Your typical spellcaster. Has many ways to blow up enemies and protect themselves." << endl << endl
				<< "Starting Stats:" << endl << "HP: 25 (+8/Lvl)" << endl << "Mana: 25 (+5/Lvl)"  << endl << "Damage: 1-2 (+1/Lvl)" << endl << "Defense: 0" << endl
				<< "Battle Skills: Magic Blade, Mana Drain, Focus" << endl
				<< "Spells: Inferno, Freeze, Shock, Weaken, Heal, Barrier" << endl;
			choice = yesOrNo("Is this the class you want?");
			if(choice) {
				//Set base stats
				classType = 3;
				maxhp = 25;
				hpperlvl = 8;
				maxmana = 25;
				manaperlvl = 5;
				mindamage = 1;
				maxdamage = 2;
				damageperlvl = 1;
				defense = 0;
				//Add class skills
				skills.push_back(addSkill(311));
				skills.push_back(addSkill(312));
				skills.push_back(addSkill(313));
				magic.push_back(addSkill(406));
				magic.push_back(addSkill(407));
				magic.push_back(addSkill(408));
				magic.push_back(addSkill(403));
				magic.push_back(addSkill(409));

				//Select class-specific skills
				setClassSkills(3);

				valid = true;
			} else if(!choice) {
				valid = false;
			}
			break;
		default:
			valid = false;
			break;
		}
	} while (!valid);
}

//Reduce all mana costs if Wisdom was chosen
void Player::WisdomBonus() {
	for(unsigned int i = 0; i < skills.size(); i++) {
		skills[i].reduceManaCost();
	}
	for(unsigned int j = 0; j < magic.size(); j++) {
		magic[j].reduceManaCost();
	}
}

//Print player's stats
void Player::printStatSheet() {
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "Class: ";
	if (getClass() == 1 ) {
		cout << "Warrior";
	} else if (getClass() == 2 ) {
		cout << "Rogue";
	} else if (getClass() == 3 ) {
		cout << "Wizard";
	}
	cout << endl << endl << "HP: " << maxhp << endl;
	cout << "Mana: " << maxmana << endl;
	cout << "Damage: " << mindamage << "-" << maxdamage << endl;
	cout << "Spell Power: " << spellpower << endl; 
	cout << "Defense: " << defense << endl;
	cout << "Other Bonuses:" << endl;
	if(hpregen > 0) cout << "- HP Regen: +" << hpregen << " per turn" << endl;
	if(manaregen > 0) cout << "- Mana Regen: +" << manaregen << " per turn" << endl;
	if(critmulti > 1.5) cout << "- Critical Hits deal " << static_cast<int>(critmulti * 100) << "% damage" << endl;
	cout << endl << "Passives:" << endl;
	for(unsigned int i = 0; i < passives.size(); i++) {
		cout << "- ";
		getSkillInfo(passives[i]);
	}
}

//Character Creation Menu
void createPlayer() {
	cout << endl << endl << endl << "_______________________" << endl << " Create Your Character " << endl << "_______________________" << endl;
	//Create character
	cout << endl << "What is your name? ";
	cin >> input;
	Player p(input);

	//Choose class
	do {
		p.chooseClass();
		p.printStatSheet();
		choice = yesOrNo("Is this the character you want?");
		if(choice) {
			//Apply Wisdom bonus
			if(p.checkPassive(301)) {
				p.WisdomBonus();
			}
			valid = true;
			break;
		} else {
			valid = false;
			break;
		}
	} while (!valid);
	
	startBattle(p);
}

Enemy::Enemy() {
	name = "Training Dummy";
	hp = 30;
	maxhp = 30;
	mindamage = 5;
	maxdamage = 6;
	defense = 0;
	hpregen = 0;
}

Enemy::~Enemy() {
	delete [] prefix;
	delete [] suffix;
}

//Returns damage reduction (1 = physical, 2 = magic)
double Enemy::returnDamageTaken(int type) {
	double multi = 1.0;

	if(type == 1 && this->checkAffix(9)) {
		multi = 0.6;
	} else if (type == 2 && this->checkAffix(10)) {
		multi = 0.6;
	}

	if(checkStatus(8) > 0) multi *= 1.3;	//Weaken

	return multi;
}

//Modifies damage by crit value if it succeeds
int Enemy::rollCrit(int d) {
	double dmg = static_cast<double>(d);
	if (randomNumber(1,100) <= 25) {
		cout << "CRITICAL HIT!!!" << endl;
		dmg = dmg * 1.5;
	}

	int x = static_cast<int>(dmg);
	return x;
}

//Checks if enemy has the affix based on ID
bool Enemy::checkAffix(int id){
	for (int i = 0; i < pref_len; i++) {
		if (id == prefix[i]) return true;
	}
	for (int j = 0; j < suff_len; j++) {
		if (id == suffix[j]) return true;
	}
	return false;
}

//Gets boss affixes for quick menu screen
void Enemy::getBossAffix() {
	if(name == "Boss Dummy") {
		cout << "(";
		for(int i = 0; i < pref_len; i++){
			cout << getAffixName(prefix[i]) << ", ";
		}
		for(int j = 0; j < suff_len; j++){
			cout << getAffixName(suffix[j]);
			if(j != (suff_len-1)) cout << ", ";
		}
		cout << ")";
	}
}

//Prints enemy information
void Enemy::printEnemyStats() {
	cout << endl;
	cout << "Name: " << name << endl;
	cout << endl << "HP: " << maxhp << endl;
	cout << "Damage: " << mindamage << "-" << maxdamage << endl;
	cout << "Defense: " << defense << endl;
	if(name == "Boss Dummy") {
		cout << "Affixes:" << endl;
		cout << "- Prefix: ";
		for (int i = 0; i < pref_len; i++){
				if (i != 0) cout << ", ";
				cout << getAffixName(prefix[i]);
		}	
		cout << endl << "- Suffix: ";
		for (int i = 0; i < suff_len; i++){
				if (i != 0) cout << ", ";
				cout << getAffixName(suffix[i]);
		}
		cout << endl;
	}
}

//Returns monster affix name based on ID.
string getAffixName(int id) {
	string s;
	switch(id){
	case 1: 
		s = "Strong";
		break;
	case 2: 
		s = "Arcane";
		break;
	case 3: 
		s = "Deadly";
		break;
	case 4: 
		s = "Toxic";
		break;
	case 5: 
		s = "Vampiric";
		break;
	case 6: 
		s = "Angry";
		break;
	case 7: 
		s = "Weakening";
		break;
	case 8: 
		s = "Vitality";
		break;
	case 9: 
		s = "Sturdiness";
		break;
	case 10: 
		s = "Resistance";
		break;
	case 11: 
		s = "Regeneration";
		break;
	case 12: 
		s = "Spikes";
		break;
	case 13: 
		s = "Nullification";
		break;
	case 14: 
		s = "Fury";
		break;
	default:
		s = "ERROR";
		break;
	}
	return s;
}

void Enemy::generateEnemy(int lvl) {
	int aff = 0;
	int pref = 0;
	int suff = 0;

	//Set stats
	maxhp = 30 + (25 * (lvl - 1));
	hp = maxhp;
	mindamage = 5 + (3 * (lvl - 1));
	maxdamage = 6 + (4 * (lvl - 1));
	defense = (lvl - 1) / 2;

	//Get number of affixes
	if(lvl % 5 == 0) {	//Boss Dummy
		name = "Boss Dummy";
		if (lvl >= 20) {
			aff = 6;
		} else if (lvl >= 15) {
			aff = 5;
		} else if (lvl >= 10) {
			aff = 4;
		} else {
			aff = 3;
		} 
	} else {
		if (lvl >= 8) {
			aff = 2;
		} else if (lvl > 1) {
			aff =  1;
		} else {
			aff = 0;
		}
	}

	//Distribute affixes so that you can have more than 3 prefix/suffix
	if (aff == 6) {
		pref = 3;
		suff = 3;
	} else if (aff == 5) {
		pref = randomNumber(2,3);
		suff = aff - pref;
	} else if (aff == 4) {
		pref = randomNumber(1,3);
		suff = aff - pref;
	} else if (aff == 3) {
		pref = randomNumber(1,2);
		suff = aff - pref;
	} else if (aff == 2) {
		pref = 1;
		suff = 1;
	} else if (aff == 1) {
		pref = randomNumber(0,1);
		suff = aff - pref;
	}

	//Randomly generate affixes
	prefix = new int[pref];
	pref_len = pref;
	suffix = new int[suff];
	suff_len = suff;
	for (int i = 0; i < pref; i++) {
		bool check;
		int rand;
		do {
			rand = randomNumber(1,7);
			check = true;
			for (int j = 0; j < i; j++) {
				if(rand == prefix[j]) {
					check = false;
					break;
				}
			}
		} while (!check);
		prefix[i] = rand;
	}
	for (int i = 0; i < suff; i++) {
		bool check;
		int rand;
		do {
			rand = randomNumber(8,14);
			check = true;
			for (int j = 0; j < i; j++) {
				if(rand == suffix[j]) {
					check = false;
					break;
				}
			}
		} while (!check);
		suffix[i] = rand;
	}

	//Generate non-boss Dummy name
	if(lvl % 5 != 0) {
		string n;
		if(pref > 0) {
			n = getAffixName(prefix[0]);
			n.append(" ");
		}
		n.append("Training Dummy");
		if(suff > 0) {
			n.append(" of ");
			n.append(getAffixName(suffix[0]));
		}
		name = n;
	}
	
	//Apply stat affixes (i.e. Strong, Vitality)
	for(int i = 0; i < pref; i++){
		if(prefix[i] == 1) {
			mindamage = static_cast<int>(static_cast<double>(mindamage) * 1.25);
			maxdamage = static_cast<int>(static_cast<double>(maxdamage) * 1.25);
		}
	}
	for(int i = 0; i < suff; i++){
		if(suffix[i] == 8) {
			maxhp = static_cast<int>(static_cast<double>(maxhp) * 1.3);
			hp = maxhp;
		}
	}
}

