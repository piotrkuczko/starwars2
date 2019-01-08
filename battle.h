#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

//do poprawy
using Time = int;


class Clock {
private:
    Time time, maxTime;
public:
    Clock(Time time, Time maxTime) : time(time), maxTime(maxTime) {};
    bool timeToBattle () {
        std::cout << "time:" << time << std::endl;
        return (time % 2 == 0 || time % 3 == 0 ) && (time % 5 != 0);
    }
    void increaseTime(Time timeStep) {
        time += timeStep;
        if(time > maxTime) time = time%(maxTime + 1);
    }
};


class SpaceBattle {
protected:
    Clock clock;
    size_t countImperial = 0, countRebel = 0;
    Time startTime, maxTime;
    std::vector <std::shared_ptr<ImperialStarship>> imperial;
    std::vector <RebelStarship*> rebel;
    void attack () {
        for (auto i : imperial) {
            for (auto r : rebel) {
                std::cout << "atakuja sie:\n";
                r->show();
                i->show();
                r->takeDamage(i->getAttackPower());
                if (dynamic_cast<Explorer*> (r) == NULL) {
                    std::cout << "take Damage\n";
                    i->takeDamage(r->getAttackPower());
                } else std::cout << "Explorer\n";
            }
        }
    }

    //function that prints battle result depending on the number of undestroyed ships of each fraction
    void battle_result(){
        if(countImperialFleet() == 0){
            if(countRebelFleet() == 0)
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
    SpaceBattle(std::vector<std::shared_ptr<ImperialStarship>> imperial, std::vector<RebelStarship *> rebel,
                    Time startTime, Time maxTime, Clock clock)
            : imperial(imperial), rebel(rebel), startTime(startTime), maxTime(maxTime), clock(clock) {
    };
public:
    class Builder;
    size_t countImperialFleet() {
        countImperial = 0;
        for (auto it : imperial) {
            std::cout << "zliczam: " << it->getCount() << std::endl;
            countImperial += it->getCount();
        }
        return countImperial;
    } //– zwraca liczbę niezniszczonych statków Imperium,
    size_t countRebelFleet() {
        countRebel = 0;
        for (auto it : rebel)
            countRebel += it->getCount();
        return countRebel;
    } //– zwraca liczbę niezniszczonych statków Rebelii,
    //function that simulate moment in fight
    void tick(Time timestep){
        std::cout << "tick\n";
        if(countRebelFleet() > 0 && countImperialFleet() > 0){
            std::cout << "Exists: " << countRebelFleet() << " " << countImperialFleet() << std::endl;
            //if there are 1 or more ship of each fraction undestroyed...
            if(clock.timeToBattle()) {
                //... and it is time when attack can occur, then function battle is invoked
                std::cout << "timeToBattle\n";
                attack();
            }
        } else {
            //if there is 0 ships of any of fractions, then battle is ended, and function battle_result is invoked
            battle_result();
        }

        //after the battle time is changed by timestep, and if it goes beyond t1,
        //then it loops and start counting from 0
        clock.increaseTime(timestep);
    }
    void atakuj () {
        attack();
    }
};

class SpaceBattle::Builder {
private:
    Time time0, time1;
    std::vector <std::shared_ptr<ImperialStarship>> imperialB;
    std::vector <RebelStarship*> rebelB;
public:
    Builder() {};
    Builder ship (std::shared_ptr<ImperialStarship> ship1) {
        imperialB.emplace_back(ship1);
        return *this;
    }
    Builder ship (Explorer ship1) {
        rebelB.emplace_back(&ship1);
        return *this;
    }
    Builder ship (RebelStarship ship1) {
        rebelB.emplace_back(&ship1);
        return *this;
    }
    Builder startTime (Time t0) {
        time0 = t0;
        return *this;
    }
    Builder maxTime (Time t1) {
        time1 = t1;
        return *this;
    }
    SpaceBattle build() {
        return SpaceBattle(imperialB, rebelB, time0, time1, Clock(time0, time1));
    }
};


#endif //STARWARS2_BATTLE_H
