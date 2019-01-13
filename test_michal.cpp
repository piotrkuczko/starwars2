#include <cassert>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"

int main() {
    auto xwing = createXWing(1, 300000, 50);
    auto explorer = createExplorer(100, 400000);
    auto cruiser = createStarCruiser(1234, 100000, 11);
    auto const explorer2 = createExplorer(150, 400000);
    auto deathStar = createDeathStar(10, 70);
    auto fighter = createTIEFighter(50000, 90);
    auto destroyer = createImperialDestroyer(150, 20);
    auto deathStar2 = createDeathStar(10,70);
    const std::initializer_list<std::shared_ptr<ImperialStarship>> v = {deathStar, deathStar2};
    auto squaron = createSquadron(v);     //jadowity test z constami!!!!
    //auto squadron = createSquadron({deathStar, fighter});
    //auto squadron =  Squadron({deathStar, fighter});

    auto battle = SpaceBattle::Builder()
            .startTime(2)
            .maxTime(23)
            .ship(deathStar)
            .ship(fighter)
            .ship(xwing)
            .ship(explorer)
            .build();
    //Clock c1(10,2);   //nie kompiluje się i dobrze
    /*
    auto battle = SpaceBattle::Builder()
        .ship(squadron)
        .startTime(2)
        .maxTime(23)
        .ship(xwing)
        .ship(explorer)
        .build();
    */
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(3); //deathstar i xwing zabijają się nawzajem
    printf("%d %d\n", (int)battle.countRebelFleet(), (int)battle.countImperialFleet());
    assert(battle.countRebelFleet() == 1);
    assert(battle.countImperialFleet() == 1);
    battle.tick(3); //z 5 na 8, nic sie nie dzieje
    battle.tick(3); //z 8 na 11, dobijam explorera
    printf("%d %d\n", (int)battle.countRebelFleet(), (int)battle.countImperialFleet());
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);
    /*battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);*/

    battle.tick(1); // Wypisuje "IMPERIUM WON\n".*/
}