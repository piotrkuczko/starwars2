#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

#include <iostream>
#include "helper.h"
#include "rebelfleet.h"
#include "imperialfleet.h"

using Time = int;

class Clock {
private:
    Time time, maxTime;
public:
    Clock(Time time, Time maxTime) : time(time), maxTime(maxTime) {
        assert(time <= maxTime);
        assert(0 <= time);
        assert(0 < maxTime);
    };

    bool timeToBattle() {
        return (time % 2 == 0 || time % 3 == 0) && (time % 5 != 0);
    }

    void increaseTime(Time timeStep) {
        assert(time >= 0);
        time += timeStep;
        if (time > maxTime) time = time % (maxTime + 1);
    }
};


class SpaceBattle {
protected:
    Clock clock;
    size_t countImperial = 0, countRebel = 0;
    Time startTime, maxTime;
    std::vector<std::shared_ptr<ImperialStarship>> imperial;
    std::vector<std::shared_ptr<RebelStarship>> rebel;

    void attack() {
        for (auto i : imperial) {
            for (auto r : rebel) {
                if (r->getShield() > 0 && i->getShield() > 0) {
                    r->takeDamage(i->getAttackPower());
                    if (r->hasAttackPower())
                        i->takeDamage(r->getAttackPower());
                }
            }
        }
    }

    //function that prints battle result depending on the number of undestroyed ships of each fraction
    void battle_result() {
        if (countImperialFleet() == 0) {
            if (countRebelFleet() == 0)
                //if each fraction is destroyed function prints "DRAW\n"
                std::cout << "DRAW\n";
            else
                //if only imperials are destroyed function prints "REBELLION WON\n"
                std::cout << "REBELLION WON\n";
        } else {
            //if only rebels are destroyed function prints "IMPERIUM WON\n"
            std::cout << "IMPERIUM WON\n";
        }
    }

protected:
    SpaceBattle(std::vector<std::shared_ptr<ImperialStarship>> imperial,
                std::vector<std::shared_ptr<RebelStarship>> rebel,
                Time startTime, Time maxTime, Clock clock)
            : imperial(imperial), rebel(rebel), startTime(startTime), maxTime(maxTime), clock(clock) {

    };
public:
    class Builder;

    //return living ship imperial
    size_t countImperialFleet() {
        countImperial = 0;
        for (auto it : imperial) {
            countImperial += it->getCount();
        }
        return countImperial;
    }

    //return living ship rebeliant
    size_t countRebelFleet() {
        countRebel = 0;
        for (auto it : rebel)
            countRebel += it->getCount();
        return countRebel;
    }

    //function that simulate moment in fight
    void tick(Time timestep) {
        if (countRebelFleet() > 0 && countImperialFleet() > 0) {
            //if there are 1 or more ship of each fraction undestroyed...
            if (clock.timeToBattle()) {
                //... and it is time when attack can occur, then function battle is invoked
                attack();
            }
        } else {
            //if there is 0 ships of any of fractions, then battle is ended, and function battle_result is invoked
            battle_result();
        }
        //battle time is changed by timestep
        clock.increaseTime(timestep);
    }
};

//builder to spacebattle
class SpaceBattle::Builder {
private:
    Time time0, time1;
    std::vector<std::shared_ptr<ImperialStarship>> imperialB;
    std::vector<std::shared_ptr<RebelStarship>> rebelB;
public:
    Builder() {};

    Builder ship(std::shared_ptr<ImperialStarship> ship1) {
        imperialB.emplace_back(ship1);
        return *this;
    }

    Builder ship(std::shared_ptr<RebelStarship> ship1) {
        rebelB.emplace_back(ship1);
        return *this;
    }

    Builder startTime(Time t0) {
        time0 = t0;
        return *this;
    }

    Builder maxTime(Time t1) {
        time1 = t1;
        return *this;
    }

    SpaceBattle build() {
        return SpaceBattle(imperialB, rebelB, time0, time1, Clock(time0, time1));
    }
};


#endif //STARWARS2_BATTLE_H
