#include <iostream>
#include <string>
#include "trades.hpp"
#include "part2.hpp"

using namespace std;

void part2() {
    cerr << "Part2 was called" << endl;
    string tradeData = fetchTrades();    
    parse_and_print_trades(tradeData);
}