#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/split.hpp>
#include <system.hpp>
using namespace std;
using namespace plsim;

class BuyLimit : public Order {
public:
  const double price;
  BuyLimit(const std::string symbol_, const double quantity_, const double price_): Order(symbol_, quantity_), price(price_) {}
  const bool eval(const Market& m) {
    Tick* last_tick = m.find(symbol)->second;
    if(last_tick->bid < price) {
      return true;
    }
    return false;
  }
};

class Hats : public System {
  void processTick(const Tick& t) {
    if(t.symbol == "USDJPY" && orders.size() < 100) {
      placeOrder(new BuyLimit("USDJPY",100, 101.99));
    }
  }
};

void csv2ticks(const std::string fname, const std::string splitter, std::vector<Tick>& ticks) {
  std::ifstream fin;
  string buf;
  vector<string> splitbuf;
  typedef vector< boost::iterator_range<string::iterator> > find_vector_type;
  fin.open(fname.c_str());

  if(!fin.is_open()) {
    return;
  }

  while(getline(fin, buf)) {
    boost::split(splitbuf, buf, boost::is_any_of(splitter));
    ticks.push_back(Tick(splitbuf[1],ptime(time_from_string(splitbuf[0])),atof(splitbuf[2].c_str()),atof(splitbuf[3].c_str())));
  }
  fin.close();
}

int main() {
  std::vector<Tick> tickstream;
  csv2ticks("/var/archive/work/data/barclays.tick.data/tick.stream.csv", ",", tickstream);
  Hats h();
  //h.run(tickstream);
}
