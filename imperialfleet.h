#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include <vector>
#include <memory>
#include "rebelfleet.h"

class ImperialStarship {
protected:
    size_t count = 1;
    ShieldPoints shield = -1;
    AttackPower power = -1;

    ImperialStarship(ShieldPoints shield, AttackPower power) : shield(shield), power(power) {};

    ImperialStarship() {};

public:
    size_t getCount() { return count; }

    virtual ShieldPoints getShield() { return shield; };

    virtual AttackPower getAttackPower() { return power; }

    virtual void takeDamage(AttackPower damage) {
        shield = (damage >= shield) ? 0 : shield - damage;
        if (shield == 0) count = 0;
    }
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
    Squadron(std::vector<std::shared_ptr<ImperialStarship>> v) : v(v) { getShield(); };

    Squadron(std::initializer_list<std::shared_ptr<ImperialStarship>> l) : v(l) { getShield(); };

    ShieldPoints getShield() override {
        if (shield == -1) {
            shield = 0;
            count = 0;
            for (auto it : v) {
                shield += it->getShield();
                count += it->getCount();
            }
        }
        return shield;
    }

    AttackPower getAttackPower() override {
        if (power == -1) {
            power = 0;
            for (auto it : v) {
                power += it->getAttackPower();
            }
        }
        return power;
    }

    void takeDamage(AttackPower damage) override {
        shield = 0;
        count = 0;
        for (auto it : v) {
            it->takeDamage(damage);
            shield += it->getShield();
            count += it->getCount();
        }
    }
};

std::shared_ptr<Squadron> createSquadron(std::vector<std::shared_ptr<ImperialStarship>> &v) {
    return std::make_shared<Squadron>(v);
}

std::shared_ptr<Squadron> createSquadron(std::initializer_list<std::shared_ptr<ImperialStarship>> v) {
    return std::make_shared<Squadron>(v);
}

#endif //STARWARS2_IMPERIALFLEET_H
