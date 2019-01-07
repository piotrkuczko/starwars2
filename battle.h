#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

//do poprawy
using Time = int;


class SpaceBattle {
protected:
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
                /*if (dynamic_cast<std::shared_ptr<Squadron>> (i) == NULL) {
                    std::cout << "cos innego niz squad\n";
                } else std::cout << "squadron\n";*/
                r->takeDamage(i->getAttackPower());
                if (dynamic_cast<Explorer*> (r) == NULL) {
                    std::cout << "take Damage\n";
                    i->takeDamage(r->getAttackPower());
                } else std::cout << "Explorer\n";
            }
        }
    }
protected:
    SpaceBattle(std::vector <std::shared_ptr<ImperialStarship>> imperial, std::vector<RebelStarship*> rebel, Time startTime, Time maxTime)
            : imperial(imperial), rebel(rebel), startTime(startTime), maxTime(maxTime) {};
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
    void tick(Time timeStep) {
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
    /*Builder ship (Squadron ship1) {
        imperialB.emplace_back(&ship1);
        return *this;
    }*/
    Builder ship (std::shared_ptr<ImperialStarship> ship1) {
        imperialB.emplace_back(ship1);
        return *this;
    }
    /*Builder ship (Explorer ship1) {
        rebelB.emplace_back(&ship1);
        return *this;
    }*/
    Builder ship (RebelStarship ship1) {
        rebelB.emplace_back(&ship1);
        return *this;
    }
    Builder startTime (Time t0) {
        time0 = t0;
        return *this;
    }
    Builder maxTime (Time t0) {
        time0 = t0;
        return *this;
    }
    SpaceBattle build() {
        return SpaceBattle(imperialB, rebelB, time0, time1);
    }
};


#endif //STARWARS2_BATTLE_H
