#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

#include <iostream>
#include <cassert>

/*
 * TODO: brak funkcji fabrykujących
 * TODO: typy pomocnicze SHieldPoints, Speed, AttackPower
 */


// do poprawy
using ShieldPoints = int;
using Speed = int;
using AttackPower = int;


class RebelStarship {
protected:
    size_t count = 1;
    virtual void checkSpeed(){};
    ShieldPoints shield = -1;
    Speed speed = -1;
    AttackPower power = -1;
    RebelStarship (ShieldPoints shield, Speed speed, AttackPower power)
            : shield(shield), speed(speed), power(power) {
        std::cout << "RebelStarship: " << shield << " " << speed << " " << power << std::endl; checkSpeed();}
    RebelStarship() {};
public:
    size_t getCount () { return count; }
    ShieldPoints getShield() { return shield; } //zwraca wytrzymałość tarczy,
    Speed getSpeed() { return speed; } //zwraca prędkość statku,
    virtual void takeDamage(AttackPower damage) { shield = (damage>=shield)? 0:shield-damage;
        if (shield == 0) count = 0;
    }
    AttackPower getAttackPower() { return power; }
    void show () {
        std::cout << shield << " " << speed << " " << power << "\n";
    }

};


class Explorer : public RebelStarship {
private:
protected:
    void checkSpeed() override { assert(299796<=speed && speed<=2997960); }
public:
    Explorer (ShieldPoints shield, Speed speed) {
        RebelStarship::shield=shield; RebelStarship::speed=speed; checkSpeed(); };
    AttackPower getAttackPower() = delete;
};

Explorer createExplorer (ShieldPoints shield, Speed speed) {
    return Explorer(shield, speed);
}

class StarCruiser : public RebelStarship {
private:
protected:
    void checkSpeed() override { assert(99999<=speed && speed<=299795); }
public:
    StarCruiser (ShieldPoints shield, Speed speed, AttackPower power) : RebelStarship(shield, speed, power) {};
};

StarCruiser createStarCruiser (ShieldPoints shield, Speed speed, AttackPower power) {
    return StarCruiser(shield, speed, power);
}

class XWing : public RebelStarship {
private:
protected:
    void checkSpeed() override { assert(299796<=speed && speed<=2997960); }
public:
    XWing (ShieldPoints shield, Speed speed, AttackPower power) : RebelStarship(shield, speed, power) {};
};

XWing createXWing (ShieldPoints shield, Speed speed, AttackPower power) {
    return XWing(shield, speed, power);
}

#endif //STARWARS2_REBELFLEET_H
