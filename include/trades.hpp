#ifndef TRADES_HPP
#define TRADES_HPP

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);

std::string fetchTrades();

void parse_and_print_trades(const std::string& rawData);

#endif