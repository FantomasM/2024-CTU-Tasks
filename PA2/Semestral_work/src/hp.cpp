//
// Created by fantomasm on 8.5.23.
//

#include "hp.h"

//basic function to take damage
void hp::TakeDamage(int damage) {
    //character cant get more damage than his hp, if damage is bigger than hp, than hp is set to 0
    if (damage > HP) {
        HP = 0;
        return;
    }
    HP -= damage;


}

//Same for healing, character cant have more hp than MaxHp
void hp::Heal(int heal_effect) {

    if (heal_effect + HP > MaxHP) {
        HP = MaxHP;
        return;
    }
    HP += heal_effect;


}

int hp::get_HP() const {

    return HP;

}

int hp::get_MaxHP() const {

    return MaxHP;

}