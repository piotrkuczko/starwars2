#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

//do poprawy
using Time = int;


class SpaceBattle {
protected:
    size_t countImperial = 0, countRebel = 0;
    Time startTime, maxTime;
    std::vector <ImperialStarship*> imperial;
    std::vector <RebelStarship*> rebel;
    void attack () {
        for (auto i : imperial) {
            for (auto r : rebel) {
                std::cout << "atakuja sie:\n";
                r->show();
                //i->show();
                std::cout << i->getAttackPower() << " " << i->getShield() << std::endl;
                r->takeDamage(i->getAttackPower());
                if (dynamic_cast<Explorer*> (r) == NULL) {
                    i->takeDamage(r->getAttackPower());
                }
            }
        }
    }
protected:
    SpaceBattle(std::vector <ImperialStarship*> imperial, std::vector<RebelStarship*> rebel, Time startTime, Time maxTime)
            : imperial(imperial), rebel(rebel), startTime(startTime), maxTime(maxTime) {};
public:
    class Builder;
    size_t countImperialFleet() { return countImperial; } //– zwraca liczbę niezniszczonych statków Imperium,
    size_t countRebelFleet() { return countRebel; } //– zwraca liczbę niezniszczonych statków Rebelii,
    void tick(Time timeStep) {
    }
    void atakuj () {
        attack();
    }
};

class SpaceBattle::Builder {
private:
    Time time0, time1;
    std::vector <ImperialStarship*> imperialB;
    std::vector <RebelStarship*> rebelB;
public:
    Builder() {};
    Builder ship (ImperialStarship ship1) {
        imperialB.emplace_back(&ship1);
        return *this;
    }
    Builder ship (Explorer ship1) {
        std::cout << "mam explorera\n";
        rebelB.emplace_back(&ship1);
        return *this;
    }
    Builder ship (RebelStarship ship1) {
        std::cout << "mam Rebelianta: "; ship1.show();
        Explorer *e = dynamic_cast <Explorer*> (&ship1);
        if (e == NULL) {
            std::cout << "NULL\n";
        } else
            std::cout << "cos innego\n";
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
