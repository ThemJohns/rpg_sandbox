#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <iostream>

#include "character.h"

bool Fight(Player&,Enemy&);
void startBattle(Player);
void displayUI(Player&,Enemy&);
int applyPhysBonus(Player&,int);
int applyMagicBonus(Player&,int);
void applyPostBonus(Player&,int);
int rollDamage(Player&,Enemy&,int,int);
//Commands
int useSkill(Player&,Enemy&,int);		//Returns damage dealt
int attackEnemy(Player&,Enemy&);		//Returns damage dealt
int attackPlayer(Enemy&,Player&);		//Returns damage dealt
void startPlayerTurn(Player&,int);
void endPlayerTurn(Player&,int);
void startEnemyTurn(Enemy&,int);
void endEnemyTurn(Enemy&,int);

#endif