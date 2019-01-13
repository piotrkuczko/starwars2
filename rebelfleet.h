#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

#include <iostream>
#include <cassert>
#include "helper.h"


class RebelStarship : public Starship {
    friend SpaceBattle;
protected:
    Speed speed = -1;
    AttackPower power = -1;

    virtual bool hasAttackPower() { return true; };

    explicit RebelStarship(ShieldPoints shield, Speed speed, AttackPower power)
            : Starship(shield), speed(speed), power(power) {}

    explicit RebelStarship(ShieldPoints shield, Speed speed) : Starship(shield), speed(speed) {};

public:
    Speed getSpeed() { return speed; }

    AttackPower getAttackPower() { return power; }
};


class Explorer : public RebelStarship {
private:
protected:
    bool hasAttackPower() override { return false; };
public:
    Explorer(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed) {
        RebelStarship::speed = speed;
        assert(299796 <= speed && speed <= 2997960);
    };

    AttackPower getAttackPower() = delete;
};

std::shared_ptr<Explorer> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

class StarCruiser : public RebelStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower power) : RebelStarship(shield, speed, power) {
        assert(99999 <= speed && speed <= 299795);
    };
};

std::shared_ptr<StarCruiser> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::make_shared<StarCruiser>(shield, speed, power);
}

class XWing : public RebelStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower power) : RebelStarship(shield, speed, power) {
        assert(299796 <= speed && speed <= 2997960);
    };
};

std::shared_ptr<XWing> createXWing(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::make_shared<XWing>(shield, speed, power);
}

#endif //STARWARS2_REBELFLEET_H
