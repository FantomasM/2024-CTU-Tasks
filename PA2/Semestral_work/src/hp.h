//
// Created by fantomasm on 8.5.23.
//

#ifndef SEMESTRAL_WORK_HP_H
#define SEMESTRAL_WORK_HP_H


class hp {
public:
    inline hp() : HP(10), MaxHP(10) {}

    //Basic hp constructor, in case of hp bigger than MaxHP, MaxHP is set to HP
    inline hp(int Hp, int Hpmax) : HP(Hp), MaxHP(Hpmax) {
        if (HP > MaxHP) {
            HP = MaxHP;
        }
    }

    virtual void TakeDamage(int damage);

    void Heal(int heal_effect);

    int get_HP() const;

    int get_MaxHP() const;

protected:
    int HP;
    int MaxHP;
};

#endif //SEMESTRAL_WORK_HP_H