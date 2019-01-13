#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include <vector>
#include <memory>
#include <iostream>
#include "helper.h"

class ImperialStarship : public Starship {
    friend SpaceBattle;
protected:
    AttackPower power = -1;

    ImperialStarship(ShieldPoints shield, AttackPower power) : Starship(shield), power(power) {};

    ImperialStarship() : Starship() {};

public:

    virtual AttackPower getAttackPower() { return power; }
};

class DeathStar : public ImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shield, AttackPower power) {
    return std::make_shared<DeathStar>(shield, power);
}

class ImperialDestroyer : public ImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shield, AttackPower power) {
    return std::make_shared<ImperialDestroyer>(shield, power);
}

class TIEFighter : public ImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower power) : ImperialStarship(shield, power) {};
};

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shield, AttackPower power) {
    return std::make_shared<TIEFighter>(shield, power);
}

class Squadron : public ImperialStarship {
private:
    std::vector<std::shared_ptr<ImperialStarship>> v;
public:
    explicit Squadron(std::vector<std::shared_ptr<ImperialStarship>> v) : v(v) { takeDamage(0); };

    Squadron(std::initializer_list<std::shared_ptr<ImperialStarship>> l) : v(l) { takeDamage(0); };

    ShieldPoints getShield() override {
        if (shield == -1) {
            shield = 0;
            for (auto it : v) {
                shield += it->getShield();
            }
        }
        return shield;
    }

    AttackPower getAttackPower() override {
        if (power == -1) {
            power = 0;
            for (auto it : v) {
                if (it->getShield() > 0)
                    power += it->getAttackPower();
            }
        }
        return power;
    }

    void takeDamage(AttackPower damage) override {
        shield = 0;
        count = 0;
        power = 0;
        for (auto it : v) {
            it->takeDamage(damage);
            shield += it->getShield();
            if (it->getShield() > 0)
                power += it->getAttackPower();
            count += it->getCount();
        }
    }
};

std::shared_ptr<Squadron> createSquadron(std::vector<std::shared_ptr<ImperialStarship>> v) {
    return std::make_shared<Squadron>(v);
}

std::shared_ptr<Squadron> createSquadron(std::initializer_list<std::shared_ptr<ImperialStarship>> v) {
    return std::make_shared<Squadron>(v);
}

#endif //STARWARS2_IMPERIALFLEET_H
