#include "battle_system.h"
#include "character.h"
#include "general_functions.h"
#include "skills.h"

//Apply after-attack passives based on type (0=non-attack, 1 = physical, 2 = magic)
void applyPostBonus(Player& atk, int type) {
	if(atk.checkPassive(103) && type == 1) {		//Blood Knight
		int x = (atk.getMaxHp() - atk.getHp()) / 10;
		if(x > 0) atk.Heal(x);
	}
}

//Apply offensive magic passives
int applyMagicBonus(Player& atk, int d) {
	int dmg = d;

	//Add Spell Power
	dmg += atk.getSpellPower() * atk.getLevel();

	if(atk.checkPassive(303)) {
		dmg += atk.getSpellPower() + atk.getLevel();
	}
	if(atk.checkPassive(302)) {		//Overload
		dmg = modifyDamage(dmg,1.5);
	}

	return dmg;
}

//Apply offensive physical passives
int applyPhysBonus(Player& atk, int d) {
	int dmg = d;

	if(atk.checkPassive(202)) {		//Wild Strikes
		dmg += randomNumber(0,(atk.getLevel() * 2));
	}

	if(atk.checkPassive(102)) {		//Reckless
		dmg = modifyDamage(dmg,1.5);
	}
	if(atk.checkPassive(201)) {		//Critical Hit
		dmg = atk.rollCrit(dmg);
	}

	return dmg;
}

//Returns randomized value and applies damage modifiers
int rollDamage(Player& atk, Enemy& def, int id, int dmg_type) {
	int dmg = 0;
	double mult = 0;

	//Roll damage numbers
	if(dmg_type == 1) {				//Physical damage
		dmg = randomNumber(atk.getMinDmg(), atk.getMaxDmg());
		switch(id) {				//Modify damage
		case 111:		//Double Strike
			dmg = modifyDamage(dmg,1.5);
			break;
		case 113:		//Bash
			dmg = modifyDamage(dmg,2.0);
			break;
		case 114:		//Wrath
			dmg = modifyDamage(dmg,3.0);
			break;
		case 192:		//Unleashed Charge Attack
			dmg = modifyDamage(dmg,5.0);
			break;
		case 211:		//Volley
			dmg = modifyDamage(dmg,0.6);
			break;
		case 212:		//Explosive Arrow
			dmg = modifyDamage(dmg,0.5);
			break;
		case 213:		//Lifesteal
			dmg = modifyDamage(dmg,2.0);
			break;
		case 215:		//Coup de Grace
			if(def.isLowHP()) {
				dmg = modifyDamage(dmg,7.0);			
			} else {
				dmg = modifyDamage(dmg,3.5);
			}
			break;
		case 311:		//Magic Blade
			dmg = modifyDamage(dmg,1.5);
			break;
		}
	} else if(dmg_type == 2) {		//Spells
		int lvl = atk.getLevel();
		if(atk.checkStatus(5)) {		//Focus bonus
			lvl *= 2;
		}
		switch(id) {
		case 401:
			dmg = 6 + (3 * lvl);
			break;
		case 402:
			dmg = 8 + (5 * lvl);
			break;
		case 406:
			dmg = 14 + (8 * lvl);
			break;
		}
	}

	//Apply damage bonuses
	if(dmg_type != 0) {
		mult = def.returnDamageTaken(dmg_type);
		dmg = modifyDamage(dmg,mult);
	}
	if(dmg_type == 1) {
		dmg = applyPhysBonus(atk,dmg);
	} else if(dmg_type == 2) {
		dmg = applyMagicBonus(atk,dmg);
	}

	return dmg;
}

//Use skill
int useSkill(Player& atk, Enemy& def, int id) {
	int dmg = 0;				//Pre-mitigated damage
	int dmg_post = 0;			//Post-mitigated damage
	int dmg_type = 0;

	//Apply damage scaling type (1 = attack, 2 = spell power)
	switch(id) {
	case 111:		//Double Strike
		dmg_type = 1;
		break;
	case 112:		//Charge Attack
		dmg_type = 1;
		break;
	case 113:		//Bash
		dmg_type = 1;
		break;
	case 114:		//Wrath
		dmg_type = 1;
		break;
	case 192:		//Unleashed Charge Attack
		dmg_type = 1;
		break;
	case 211:		//Volley
		dmg_type = 1;
		break;
	case 212:		//Explosive Arrow
		dmg_type = 1;
		break;
	case 213:		//Lifesteal
		dmg_type = 1;
		break;
	case 215:		//Coup de Grace
		dmg_type = 1;
		break;
	case 311:		//Magic Blade
		dmg_type = 1;
		break;
	case 312:		//Mana Drain
		dmg_type = 1;
		break;
	case 401:		//Fire
		dmg_type = 2;
		break;
	case 402:		//Bolt
		dmg_type = 2;
		break;
	case 406:		//Inferno
		dmg_type = 2;
		break;
	}

	dmg = rollDamage(atk,def,id,dmg_type);

	int hits = randomNumber(2,4);
	int range;
	//Apply effects and such
	switch(id) {
	case 111:		//Double Strike
		dmg_post += def.dealDamage(dmg,1);
		applyPostBonus(atk,1);
		dmg = rollDamage(atk,def,id,dmg_type);
		dmg_post += def.dealDamage(dmg,1);
		applyPostBonus(atk,1);
		break;
	case 112:		//Charge Attack
		cout << atk.getName() << " charges up an attack!" << endl;
		atk.applyStatus(1,2);
		break;
	case 113:		//Bash
		dmg_post += def.dealDamage(dmg,1);
		def.applyStatus(0,1);
		cout << def.getName() << " becomes stunned!" << endl;
		applyPostBonus(atk,1);
		break;
	case 114:		//Wrath
		dmg_post += def.dealDamage(dmg,0);
		applyPostBonus(atk,1);
		break;
	case 115:		//Vigor
		cout << atk.getName() << " is filled with vitality!" << endl;
		atk.applyStatus(2,2);
		break;
	case 192:		//Unleashed Charge Attack
		dmg_post += def.dealDamage(dmg,1);
		applyPostBonus(atk,1);
		break;
	case 211:		//Volley
		dmg_post += def.dealDamage(dmg,1);
		dmg = rollDamage(atk,def,id,dmg_type);
		dmg_post += def.dealDamage(dmg,1);
		dmg = rollDamage(atk,def,id,dmg_type);
		dmg_post += def.dealDamage(dmg,1);
		dmg = rollDamage(atk,def,id,dmg_type);
		dmg_post += def.dealDamage(dmg,1);
		break;
	case 212:		//Explosive Arrow
		dmg = modifyDamage(dmg,0.5);
		dmg_post += def.dealDamage(dmg,1);
		def.applyStatus(3,modifyDamage(dmg_post,5.0));
		break;
	case 213:		//Lifesteal
		dmg_post += def.dealDamage(dmg,1);
		atk.Heal(dmg_post);
		break;
	case 214:		//Poison Dart
		def.dealDamage(1,0);
		cout << def.getName() << " is poisoned!" << endl;
		def.applyStatus(4,3);
		break;
	case 215:		//Coup de Grace
		dmg_post += def.dealDamage(dmg,1);
		break;
	case 311:		//Magic Blade
		dmg_post += def.dealDamage(dmg,1);
		dmg = rollDamage(atk,def,id,dmg_type);
		dmg = applyMagicBonus(atk,dmg);
		dmg_post += def.dealDamage(dmg,2);
		atk.applyStatus(5,2);
		break;
	case 312:		//Mana Drain
		dmg_post += def.dealDamage(dmg,1);
		atk.restoreMana((atk.getLevel()/2));
		break;
	case 313:		//Focus
		cout << atk.getName() << " concentrates!" << endl;
		atk.applyStatus(5,2);
		break;
	case 401:		//Fire
		dmg_post += def.dealDamage(dmg,2);
		applyPostBonus(atk,2);
		break;
	case 402:		//Bolt
		dmg_post += def.dealDamage(dmg,2);
		applyPostBonus(atk,2);
		break;
	case 403:		//Heal
		atk.Heal(14+(6*(atk.getLevel()+atk.getSpellPower())));
		break;
	case 404:		//Shield
		cout << atk.getName() << " gains 5 Defense!" << endl;
		if(atk.checkPassive(301)) {
			atk.applyStatus(6,6);
		} else {
			atk.applyStatus(6,5);
		}
		break;
	case 405:		//Weaken
		cout << def.getName() << " is Weakened!" << endl;
		if(atk.checkPassive(301)) {
			def.applyStatus(7,4);
		} else {
			def.applyStatus(7,3);
		}	
		break;
	case 406:		//Inferno
		dmg_post += def.dealDamage(dmg,2);
		applyPostBonus(atk,2);
		break;
	case 407:		//Freeze
		cout << def.getName() << " is frozen!" << endl;
		if(atk.checkPassive(301)) {
			def.applyStatus(0,3);
		} else {
			def.applyStatus(0,2);
		}
		break;
	case 408:		//Shock
		for(int x = 0; x < hits; x++) {
			range = (atk.getLevel() * 2);
			range = applyMagicBonus(atk,range);
			def.dealDamage(randomNumber(1,range),2);
		}
		applyPostBonus(atk,2);
		break;
	case 409:		//Barrier
		cout << atk.getName() << " is surrounded by a barrier!" << endl;
		if(atk.checkPassive(301)) {
			atk.applyStatus(8,5);
		} else {
			atk.applyStatus(8,4);
		}
		break;
	}

	return dmg_post;
}

//Attacks the enemy with a basic attack
int attackEnemy(Player& atk, Enemy& def) {
	int dmg;			//Pre-mitigated damage
	double mult;
	int dmg_post;			//Post-mitigated damage

	cout << atk.getName() << " attacks!" << endl;
	dmg = randomNumber(atk.getMinDmg(), atk.getMaxDmg());
	mult = def.returnDamageTaken(1);
	dmg = modifyDamage(dmg,mult);

	dmg = applyPhysBonus(atk,dmg);

	//Deal physical damage
	dmg_post = def.dealDamage(dmg,1);
	
	applyPostBonus(atk,1);

	return dmg_post;
}

//Enemy attacks player
int attackPlayer(Enemy& atk, Player& def) {
	int dmg;			//Pre-mitigated damage
	double mult;
	int dmg_post;			//Post-mitigated damage

	cout << atk.getName() << " attacks!" << endl;
	dmg = randomNumber(atk.getMinDmg(), atk.getMaxDmg());

	//Apply damage multipliers
	mult = def.returnDamageTaken();
	if(def.checkStatus(7)) {		//Weaken
		mult -= 0.3;
	}
	dmg = modifyDamage(dmg,mult);

	//Apply "Endurance" affix
	if(atk.checkAffix(14) && atk.isLowHP()) {
		dmg = modifyDamage(dmg,1.5);
	}

	//Apply "Deadly" affix (roll for crit)
	if(atk.checkAffix(3)) {
		dmg = atk.rollCrit(dmg);
	}

	//Apply "Arcane" affix
	if(atk.checkAffix(2)) {
		dmg_post = def.dealDamage(dmg,2);
	} else {
		dmg_post = def.dealDamage(dmg,1);
	}

	//Apply "Vampiric" affix
	if(atk.checkAffix(5)) {
		int h = modifyDamage(dmg_post,0.25);
		if(h < 1) h = 1;
		atk.Heal(h);
	}
	//Apply "Weakening" affix
	if (atk.checkAffix(7)) {
		if(randomNumber(1,100) <= 65) {
			cout << def.getName() << "'s Defense was reduced by 1!" << endl;
			def.addDefense(-1);
		}
	}

	return dmg_post;
}

void startPlayerTurn(Player& p, int turn) {
	int x;
	if(p.checkPassive(101)) {		//Berserker
		x = static_cast<int>((1.0 - p.getHpPercent()) * 10.0);
		p.setAttack2(x * 2);
	}
	if(p.checkPassive(305)) {		//Mana Shield
		x = (p.getMana() / 25);
		p.setDefense2(x);
	}
	if(p.checkPassive(105)) {		//Last Stand
		if(p.isLowHP()) {
			p.setDefense2(20);
		} else {
			p.setDefense2(0);
		}
	}
}

void endPlayerTurn(Player& p, int turn) {
	int x;
	if(p.checkPassive(305)) {		//Mana Shield
		x = (p.getMana() / 25);
		p.setDefense2(x);
	}
	if(p.checkPassive(105)) {		//Last Stand
		if(p.isLowHP()) {
			p.setDefense2(20);
		} else {
			p.setDefense2(0);
		}
	}
	p.cooldownTimer();
	if(p.checkPassive(203)) p.cooldownTimer();
	p.statusTimer();
}

void startEnemyTurn(Enemy& e, int turn) {
	//Apply "Endurance" affix
	if (e.checkAffix(14)) {
		if(e.isLowHP()) {
			e.setDefMulti(5);
		} else {
			e.setDefMulti(1);
		}
	}
}

void endEnemyTurn(Enemy& e, int turn) {
	//Apply "Endurance" affix
	if (e.checkAffix(14)) {
		if(e.isLowHP()) {
			e.setDefMulti(5);
		} else {
			e.setDefMulti(1);
		}
	}
	e.statusTimer();
}

//Print Player & Enemy Stats
void displayUI(Player& player, Enemy& enemy) {
	cout << "______________________________________________________" << endl;
	cout << player.getName() << endl <<"HP: " << player.getHp() << "/" << player.getMaxHp() << "    Mana: " << player.getMana() << "/" << player.getMaxMana() 
		<< "   ATK: " << player.getMinDmg() << "-" << player.getMaxDmg() << " (" << player.getSpellPower() << ")    DEF: " << player.getDef() << endl;
	cout << enemy.getName() << "    ";
	enemy.getBossAffix();
	cout << endl;
	cout << "HP: " << enemy.getHp() << "/" << enemy.getMaxHp() << "                  ATK: " << enemy.getMinDmg() << "-" << enemy.getMaxDmg() << "      DEF: " << enemy.getDef() << endl; 
	cout << "______________________________________________________" << endl;
}

bool Fight(Player& player, Enemy& enemy) {
	int s;
	string r;
	bool valid = false;
	bool had_turn = false;
	bool death = false;
	int dmg_pre = 0;
	int dmg_post = 0;
	int dmg_dealt = 0;
	int turn = 0;
	do {
		turn++;
		//Player Turn
		startPlayerTurn(player,turn);
		displayUI(player,enemy);
		if(player.checkStatus(1) > 0) {
			cout << player.getName() << " unleashed a Charged Attack!" << endl;
			useSkill(player,enemy,192);
		} else {
			do {
				cout << "1) Attack" << endl;
				cout << "2) Skills" << endl;
				cout << "3) Spells" << endl;
				cout << "4) Analyze" << endl;
				s = validNumber("Choose an action:");
				switch(s){
					case 1:
						dmg_dealt = attackEnemy(player,enemy);
						had_turn = true;
						break;
					case 2:
						cout << "Choose a skill to use:" << endl;
						player.getSkillList();
						do {
							s = validNumber("Choose an option:");
							s--;
							if(s == player.getSkillLength()) {
								valid = true;
								had_turn = false;
							} else if (s <= player.getSkillLength()) {
								if(player.canUseSkill(s)) {
									//Use skill
									cout << player.getName() << " used " << player.getSkill(s).getName() << "!" << endl;
									dmg_dealt = useSkill(player,enemy,player.getSkill(s).getID());
									int m = player.getSkill(s).getManaCost();
									player.deductMana(m);
									player.getSkill(s).setCooldown();
									if(player.checkPassive(304)) {		//Recycle Mana
										if (m > 0) player.Heal(m * 2);
									}
									if(player.checkPassive(302)) {		//Overload
										cout << player.getName() << " lost " << -(m/2) << " Defense!" << endl;
										player.addDefense(-(m/2));
									}
									valid = true;
									had_turn = true;
								} else {
									valid = false;
									had_turn = false;
								}
							}
						} while (!valid);
						if(!had_turn) displayUI(player,enemy);
						break;
					case 3:
						cout << "Choose a spell to use:" << endl;
						player.getSpellList();
						do {
							s = validNumber("Choose an option:");
							s--;
							if(s == player.getSpellLength()) {
								valid = true;
								had_turn = false;
							} else if (s <= player.getSpellLength()) {
								if(player.canUseSpell(s)) {
									//Use spell
									cout << player.getName() << " used " << player.getSpell(s).getName() << "!" << endl;
									dmg_dealt = useSkill(player,enemy,player.getSpell(s).getID());
									int m = player.getSpell(s).getManaCost();
									player.deductMana(m);
									player.getSpell(s).setCooldown();
									if(player.checkPassive(304)) {		//Recycle Mana
										if (m > 0) player.Heal(m * 2);
									}
									if(player.checkPassive(302)) {		//Overload
										cout << player.getName() << " lost " << (m/2) << " Defense!" << endl;
										player.addDefense(-(m/2));
									}
									valid = true;
									had_turn = true;
								} else {
									valid = false;
									had_turn = false;
								}
							}
						} while (!valid);
						if(!had_turn) displayUI(player,enemy);
						break;
					case 4:
						do {
							cout << "Whose stats do you want to check?" << endl
								<< "1) Player" << endl
								<< "2) Enemy" << endl
								<< "3) Back" << endl;
							s = validNumber("Choose an option:");
							switch(s) {
								case 1:
									player.printStatSheet();
									player.viewStatus();
									cout << endl;
									valid = false;
									break;
								case 2:
									enemy.printEnemyStats();
									enemy.viewStatus();
									cout << endl;
									valid = false;
									break;
								case 3:
									valid = true;
									break;
								default:
									valid = false;
									break;
							}
						} while (!valid);
						displayUI(player,enemy);
						had_turn = false;
						break;
					default:
						had_turn = false;
						break;
				}
			} while(!had_turn);
			//Apply "Spikes" affix
			if (enemy.checkAffix(12) && dmg_dealt > 0) {
				cout << enemy.getName() << " reflects damage!" << endl;
				player.dealDamage(modifyDamage(dmg_dealt,0.2),0);
			}
		}
		if(enemy.getHp() < 1 || player.getHp() < 1) death = true;

		if(!death) {
			if(player.checkPassive(104)){		//Fortify
				if(turn % 2 == 1) {		
					cout << player.getName() << " gains 2 Attack!" << endl;
					player.addAttack(2);
				} else {		
					cout << player.getName() << " gains 1 Defense!" << endl;
					player.addDefense(1);
				}
			}
			endPlayerTurn(player,turn);
			//Apply "Toxic" affix
			if (enemy.checkAffix(4)) {
				cout << enemy.getName() << " releases toxic gas!" << endl;
				player.dealDamage(modifyDamage(player.getMaxHp(),0.1),0);
			}
		}

		if(enemy.getHp() < 1 || player.getHp() < 1) death = true;
		if(!death) {		//Enemy Turn
			//Apply "Immunity" affix
			if (enemy.checkAffix(13) && turn % 3 == 0) {
				cout << enemy.getName() << " releases a flash of light!" << endl;
				player.removeStatus(2);
				player.removeStatus(5);
				player.removeStatus(6);
				player.removeStatus(8);
				enemy.removeStatus(0);
				enemy.removeStatus(4);
				enemy.removeStatus(7);
			}
			startEnemyTurn(enemy,turn);
			if(enemy.checkStatus(0) > 0){		//Check for Stun
				cout << enemy.getName() << " is stunned!" << endl;		//Skips "on attack" effects
			} else {
				bool dodge = false;
				if (player.checkPassive(204)) {			//Roll for dodge
					if (player.checkPassive(205)) {		//w/ Lucky
						if (randomNumber(1,100) <= 25) dodge = true;
					} else {
						if (randomNumber(1,100) <= 15) dodge = true;
					}
				}
				if(dodge) {		//Activate dodge
					cout << enemy.getName() << " attacks!" << endl;
					cout << player.getName() << " dodged the attack!" << endl;
					dmg_dealt = attackEnemy(player,enemy);
					//Apply "Spikes" affix
					if (enemy.checkAffix(12) && dmg_dealt > 0) {
						cout << enemy.getName() << " reflects damage!" << endl;
						player.dealDamage(modifyDamage(dmg_dealt,0.2),0);
					}
					dodge = false;
				} else {
					dmg_post = attackPlayer(enemy,player);
				}
				//Apply "Angry" affix
				if (enemy.checkAffix(6)) {
					cout << enemy.getName() << " grows angrier!" << endl;
					int a = randomNumber(1,3);
					cout << enemy.getName() << " gains " << a << " Attack!" << endl;
					enemy.addAttack(a);				
				}
			}
			endEnemyTurn(enemy,turn);
		}
		if(enemy.getHp() < 1 || player.getHp() < 1) death = true;
		
		if(player.checkStatus(2)) {		//Vigor
			player.Heal(dmg_post*5);
		}

		if(!death) {
			player.Regenerate();
			//Apply "Regeneration" affix
			if (enemy.checkAffix(11)) {
				enemy.Heal(modifyDamage(enemy.getMaxHp(),0.05));
			}
		}

		//Go to next turn
		dmg_pre = 0;
		dmg_post = 0;
		valid = false;
		had_turn = false;
	} while (!death);

	//Check game over condition
	displayUI(player,enemy);
	if(player.getHp() < 1) {
		cout << player.getName() << " is defeated..." << endl;		//Player loses if both characters are dead
		return true;
	} else {
		cout << enemy.getName() << " is defeated!" << endl;
		return false;
	}
}

//Sets up the battle
void startBattle (Player p){
	bool choice;

	/*cout << "Welcome, " << p.getName() << "!" << endl
		<< "Now, let's see how long you can last against..." << endl
		<< "A training dummy!" << endl << endl;
	choice = yesOrNo("Would you like to review the manual first?");
	if(choice) viewManual();*/

	//Initialize Battle
	bool gameover = false;
	int level = 1;
	do {
		Enemy e;
		e.generateEnemy(level);
		cout << "________________" << endl << "     BATTLE " << level << "     " << endl << "________________" << endl;
		cout << "FIGHT!" << endl;
		gameover = Fight(p,e);
		if (!gameover) {
			p.levelUp();
			level++;
		}
	} while (!gameover);

	//Game Over
	cout << "Game Over..." << endl;
	choice = yesOrNo("Return to the main menu?");
	if(!choice) {
		exit(EXIT_SUCCESS);
	}
}