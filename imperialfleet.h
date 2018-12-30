#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include <vector>
#include "rebelfleet.h"

// https://stackoverflow.com/questions/274626/what-is-object-slicing

/*
 * TODO: brak funkcji fabrykujących
 */

class ImperialStarship {
protected:
    ShieldPoints shield = -1;
    AttackPower power = -1;
    ImperialStarship (ShieldPoints shield, AttackPower power) : shield(shield), power(power) {};
    ImperialStarship() {};

public:
    virtual ShieldPoints getShield() { return shield; }
    virtual AttackPower getAttackPower() { return power; }
    virtual void takeDamage(AttackPower damage) { shield = (damage>=shield)? 0:shield-damage; }
    void show () {
        std::cout << getShield() << " " << getAttackPower() << "\n";
    }
};

class DeathStar : public ImperialStarship {
public:
    DeathStar (ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};
DeathStar createDeathStar (ShieldPoints shield, AttackPower power) {
    return DeathStar(shield, power);
}

class ImperialDestroyer : public ImperialStarship {
public:
    ImperialDestroyer (ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};
ImperialDestroyer createImperialDestroyer (ShieldPoints shield, AttackPower power) {
    return ImperialDestroyer(shield, power);
}
class TIEFighter : public ImperialStarship {
public:
    TIEFighter (ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};
TIEFighter createTIEFighter (ShieldPoints shield, AttackPower power) {
    return TIEFighter(shield, power);
}

class Squadron : public ImperialStarship {
private:
    std::vector<ImperialStarship> v;
public:
    Squadron (std::vector<ImperialStarship> v) : v(v) {};
    Squadron (std::initializer_list<ImperialStarship> l) : v(l) {};
    ShieldPoints getShield() override {
        if (shield == -1) {
            shield = 0;
            for (auto it : v)
                shield += it.getShield();
        }
        return shield;
    }
    AttackPower getAttackPower() override {
        if (power == -1) {
            power = 0;
            for (auto it : v) {
                power += it.getAttackPower();
            }
        }
        return power;
    }
    void takeDamage(AttackPower damage) override {
        shield = 0;
        for (auto it : v) {
            it.takeDamage(damage);
            shield += it.getShield();
        }
    }
};
Squadron createSquadron (std::vector <ImperialStarship> v) {
    return Squadron(v);
}
Squadron createSquadron (std::initializer_list <ImperialStarship> v) {
    return Squadron(v);
}

#endif //STARWARS2_IMPERIALFLEET_H
