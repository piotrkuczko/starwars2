#include <cassert>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"

int main() {


    auto xwing = createXWing(100, 300000, 50);
    auto explorer = createExplorer(150, 400000);
    auto cruiser = createStarCruiser(1234, 100000, 11);
    auto deathStar = createDeathStar(10000, 75);
    auto fighter = createTIEFighter(50, 9);
    auto destroyer = createImperialDestroyer(150, 20);
    auto squadron = createSquadron({deathStar, fighter});
    std::cout << "squadron: " << squadron->getShield() << "  " << squadron->getAttackPower() << std::endl;
    xwing.show();
    explorer.show();
    cruiser.show();
    auto battle = SpaceBattle::Builder()
            .ship(squadron)
            .startTime(2)
            .maxTime(23)
            .ship(xwing)
            .ship(explorer)
            .build();

    std::cout << "imp: " << battle.countImperialFleet() << " " << battle.countRebelFleet() << std::endl;
    battle.atakuj();

    std::cout << "imp: " << battle.countImperialFleet() << " " << battle.countRebelFleet() << std::endl;
    return 0;
}