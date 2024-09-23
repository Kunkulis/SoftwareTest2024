// config_loader.hpp
#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json loadConfig() {
    std::ifstream configFile("config.json");
    if (configFile.is_open()) {
        json config;
        configFile >> config;
        return config;
    } else {
        std::cerr << "Could not open config file." << std::endl;
        return json(); // Return an empty json object
    }
}

#endif