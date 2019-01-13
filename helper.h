#ifndef STARWARS2_HELPER_H
#define STARWARS2_HELPER_H

#include <cstdlib>
#include <cassert>

using ShieldPoints = int;
using Speed = int;
using AttackPower = int;

class SpaceBattle;

class Starship {
    friend SpaceBattle;
protected:
    size_t count = 1;
    ShieldPoints shield = -1;
public:
    size_t getCount() { return count; }

    explicit Starship(ShieldPoints shield) : shield(shield) {
        assert(shield >= 0);
    }

    explicit Starship() {};

    virtual ShieldPoints getShield() {
        return shield;
    }

    virtual void takeDamage(AttackPower damage) {
        if (shield <= damage) {
            count = 0;
            shield = 0;
        } else shield -= damage;
    }

};


#endif //STARWARS2_HELPER_H
