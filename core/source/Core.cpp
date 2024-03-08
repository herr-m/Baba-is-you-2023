#include "../Core.h"
#include "../Utils.h"
#include <algorithm>

void Core::movePlayer(Direction direction) {
    std::for_each(std::begin(_map.entities), std::end(_map.entities), [&](MapEntity& entity) {
        if(entity.getType() == _playerEntity && entity.canMove(direction))
            entity.move(direction);
    });
}

void Core::resetMap() { _map = _initialMap; }

Core::Core(const std::string& filePath) : _gameOver{}, _map{LevelLoader::loadLevel(filePath)}, _initialMap{_map}, _playerEntity{NONE}, _allRules{getAllRules()}, _rules{}, _permanentRules {
    std::make_shared<IsPush>(TEXT_BABA),
    std::make_shared<IsPush>(TEXT_FLAG),
    std::make_shared<IsPush>(TEXT_GRASS),
    std::make_shared<IsPush>(TEXT_LAVA),
    std::make_shared<IsPush>(TEXT_METAL),
    std::make_shared<IsPush>(TEXT_ROCK),
    std::make_shared<IsPush>(TEXT_WATER),
    std::make_shared<IsPush>(TEXT_WALL),
    std::make_shared<IsPush>(YOU),
    std::make_shared<IsPush>(STOP),
    std::make_shared<IsPush>(PUSH),
    std::make_shared<IsPush>(WIN),
    std::make_shared<IsPush>(KILL),
    std::make_shared<IsPush>(SINK),
    std::make_shared<IsPush>(IS),
    std::make_shared<IsPush>(BEST),
} {}

const Map& Core::getMap() const {
    return _map;
}

bool Core::isGameOver() const {
    return _gameOver;
}

void Core::resetEntities() {
    for(MapEntity& entity : _map.entities)
        entity.resetDirection();
}
void Core::updateRules() {
    std::vector<std::pair<EntityType, EntityType>> rulesOnMap{};
    for(const auto& is : _map.entities) {
        if(is.getType() != IS) { continue; }

        auto entBuffer = std::find_if(std::begin(_map.entities), std::end(_map.entities), [&](const MapEntity& entity) {
            return entity.getPosition() == is.getPosition()+LEFT && textEntToRealEnt.contains(entity.getType());
        });
        if(entBuffer != std::end(_map.entities)) {
            EntityType subjectType = textEntToRealEnt.at(entBuffer->getType());
            entBuffer = std::find_if(std::begin(_map.entities), std::end(_map.entities), [&](const MapEntity& entity) {
                return entity.getPosition() == is.getPosition()+RIGHT && textEntToRule.contains(entity.getType());
            });
            if(entBuffer != std::end(_map.entities))
                rulesOnMap.push_back({subjectType, textEntToRule.at(entBuffer->getType())});
        }
        entBuffer = std::find_if(std::begin(_map.entities), std::end(_map.entities), [&](const MapEntity& entity) {
            return entity.getPosition() == is.getPosition()+UP && textEntToRealEnt.contains(entity.getType());
        });
        if(entBuffer != std::end(_map.entities)) {
            EntityType subjectType = textEntToRealEnt.at(entBuffer->getType());
            entBuffer = std::find_if(std::begin(_map.entities), std::end(_map.entities), [&](const MapEntity& entity) {
                return entity.getPosition() == is.getPosition()+DOWN && textEntToRule.contains(entity.getType());
            });
            if(entBuffer != std::end(_map.entities))
                rulesOnMap.push_back({subjectType, textEntToRule.at(entBuffer->getType())});
        }
    }

    _rules.clear();
    for(const auto& rule : rulesOnMap)
        _rules.push_back(_allRules.at(rule));
}

void Core::manageInput(UserInput input) {
    resetEntities();
    switch(input) {
        case UserInput::UP:
            movePlayer(UP); break;
        case UserInput::DOWN:
            movePlayer(DOWN); break;
        case UserInput::LEFT:
            movePlayer(LEFT); break;
        case UserInput::RIGHT:
            movePlayer(RIGHT); break;
        case UserInput::RESET:
            resetMap(); break;
        case UserInput::SAVE:
            LevelLoader::saveLevel(_map); break;
        case UserInput::QUIT:
            _gameOver = true; break;
        default:
            break;
    }
}

void Core::applyPermanentRules() {
    bool changed{};
    do {
        changed = false;
        for(auto& rule : _permanentRules)
            changed = changed || rule->apply(_map.entities);
    } while(changed);
}
void Core::applyRules() {
    bool changed{};
    do {
        changed = false;
        for(auto& rule : _rules)
            changed = changed || rule->apply(_map.entities);
    } while(changed);
}

// Builds all possible rules (executed once)
std::map<std::pair<EntityType, EntityType>, std::shared_ptr<Rule>> Core::getAllRules() {
    std::map<std::pair<EntityType, EntityType>, std::shared_ptr<Rule>> result{};
    std::shared_ptr<Rule> ruleBuffer;
    for(const auto& [_, ent] : textEntToRealEnt)
        for(const auto& [_, rule] : textEntToRule) {
            switch(rule) {
                case YOU: ruleBuffer = std::make_unique<IsYou>(ent, &_playerEntity); break;
                case STOP: ruleBuffer = std::make_unique<IsStop>(ent); break;
                case PUSH: ruleBuffer = std::make_unique<IsPush>(ent); break;
                case WIN: ruleBuffer = std::make_unique<IsWin>(ent, &_playerEntity, &_gameOver); break;
                case KILL: ruleBuffer = std::make_unique<IsKill>(ent); break;
                case SINK: ruleBuffer = std::make_unique<IsSink>(ent); break;
                default: ruleBuffer = std::make_unique<EntityIsEntity>(ent, rule); break;
            }
            result.insert({{ent, rule}, ruleBuffer});
        }
    return result;
}

void Core::update() {
    _playerEntity = NONE;
    applyPermanentRules();
    updateRules();
    applyRules();
    notifyObservers();
}
