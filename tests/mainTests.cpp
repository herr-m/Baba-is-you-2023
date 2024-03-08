#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "../core/MapEntity.h"
#include "../core/Map.h"
#include "../core/Core.h"

TEST_CASE("MapEntity tests") {
    std::pair<unsigned, unsigned> mapSize{10, 10};

    MapEntity ent(BABA, 5, 5, &mapSize);
    // Constructor
    REQUIRE(ent.getPosition().first == 5);
    REQUIRE(ent.getPosition().second == 5);
    REQUIRE(ent.getType() == BABA);
    REQUIRE(ent.getDirection() == NODIR);

    // Entity movement
    ent.move(UP);
    REQUIRE(ent.getPosition().first == 4);
    REQUIRE(ent.getPosition().second == 5);
    REQUIRE(ent.getDirection() == UP);
    
    // Bound check
    REQUIRE(ent.canMove({-10, 0}) == false);

    // Type setter
    ent.setType(WALL);
    REQUIRE(ent.getType() == WALL);
}

TEST_CASE("Map & LevelLoader tests") {
    Map map{LevelLoader::loadLevel("tests/testmap.txt")};

    // Map size
    REQUIRE(map.size.first == 5);
    REQUIRE(map.size.second == 5);

    // Map entities
    REQUIRE(std::find_if(std::begin(map.entities), std::end(map.entities), [](const auto& ent) { return ent.getType() == WALL; }) != std::end(map.entities));
    REQUIRE(std::find_if(std::begin(map.entities), std::end(map.entities), [](const auto& ent) { return ent.getType() == TEXT_WALL; }) != std::end(map.entities));
}

TEST_CASE("Core tests") {
    Core core{"tests/testmap.txt"};
    core.update();

    // Player movement
    core.manageInput(UserInput::DOWN);
    core.update();
    auto wall{std::find_if(std::begin(core.getMap().entities), std::end(core.getMap().entities), [](const auto& ent) { return ent.getType() == WALL; })};
    REQUIRE(wall->getPosition().first == 1);

    // Map bound limit
    core.manageInput(UserInput::UP);
    core.manageInput(UserInput::UP);
    REQUIRE(wall->getPosition().first == 0);
}

int main() {
	Catch::Session().run();
    return 0;
}