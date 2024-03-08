/**
    @file Map.h
    @brief Defines a structure that represents a game map, as well as a namespace with functions to load and save maps.
*/

#ifndef MAP_H
#define MAP_H

#include "Utils.h"
#include "MapEntity.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>

/**
    @brief Structure that represents a game map.
*/
struct Map {
    std::string levelName;
    std::pair<unsigned, unsigned> size;
    std::vector<MapEntity> entities;
};

/**
    @brief Namespace containing functions to load and save maps.
*/
namespace LevelLoader {
/**
    @brief Loads a map from a file.
    @param filePath The path to the file to load.
    @return The loaded map.
    @throws std::invalid_argument If the file contains an unknown entity name or an invalid position.
*/
static Map loadLevel(const std::string& filePath) {
    if(!std::filesystem::exists(filePath))
        throw std::invalid_argument("File doesn't exist");

    Map result{filePath};
    std::ifstream file;
    file.open(filePath);
    std::string lineBuffer;
    std::string entityName, x, y;
    std::getline(file, lineBuffer);
    std::stringstream strm(lineBuffer);
    strm >> x; strm >> y;
    try {
        result.size = {std::stoi(y), std::stoi(x)};
        while(file.peek() != EOF) {
            std::getline(file, lineBuffer);
            if(lineBuffer.empty()) continue;
            std::stringstream strm(lineBuffer);
            std::string name, x, y;
            strm >> name; strm >> x; strm >> y;
            result.entities.emplace_back(stringToEntityType.at(name), std::stoi(y), std::stoi(x), &(result.size));
        }
    }
    catch (const std::out_of_range&) { throw std::invalid_argument("Unknown block: "+entityName); }
    catch (const std::invalid_argument&) { throw std::invalid_argument("Invalid position: "+x+' '+y); }
    return result;
}

/**
    @brief Saves a map to a file.
    @param map A Map object to parse and save.
*/
static void saveLevel(const Map& map) {
    const std::time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (!std::filesystem::is_directory("saves") || !std::filesystem::exists("saves"))
        std::filesystem::create_directory("saves");

    std::ofstream outfile{"saves/save_"+std::string(std::ctime(&t_c))+".txt"};
    outfile << map.size.first << ' ' << map.size.second << '\n';
    for(const auto& entity : map.entities) {
        auto position{entity.getPosition()};
        outfile << entityTypeToString.at(entity.getType()) << ' ' << position.second << ' ' << position.first << '\n';
    }
    outfile.close();
}
};

#endif // MAP_H
