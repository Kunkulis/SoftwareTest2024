#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "trades.hpp"

using namespace std;
using json = nlohmann::json;

// Function to handle incoming data from curl (stores the data into a std::string)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

string fetchTrades() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT&limit=5");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}

// Function to parse and print trades
void parse_and_print_trades(const std::string& rawData) {
    auto start = std::chrono::high_resolution_clock::now();  // Start time for parsing measurement

    // Parse JSON
    json trades = json::parse(rawData);

    // Iterate over each trade and print it in the required format
    for (const auto& trade : trades) {
        std::cout << "[" << std::endl;
        std::cout << "  {" << std::endl;
        std::cout << "    \"a\": " << trade["a"] << "," << std::endl;  // Aggregate tradeId
        std::cout << "    \"p\": \"" << trade["p"] << "\"," << std::endl;  // Price
        std::cout << "    \"q\": \"" << trade["q"] << "\"," << std::endl;  // Quantity
        std::cout << "    \"f\": " << trade["f"] << "," << std::endl;  // First tradeId
        std::cout << "    \"l\": " << trade["l"] << "," << std::endl;  // Last tradeId
        std::cout << "    \"T\": " << trade["T"] << "," << std::endl;  // Timestamp
        std::cout << "    \"m\": " << (trade["m"] ? "true" : "false") << std::endl;  // Was the buyer the maker?
        std::cout << "  }," << std::endl;
        std::cout << "]" << std::endl;
    }

    // End time and performance calculation
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Parsing took " << duration.count() << " microseconds." << std::endl;
}