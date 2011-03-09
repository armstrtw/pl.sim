#include <system.hpp>

class BuyLimit : public Order {
public:
  const double price;
  BuyLimit(const std::string symbol_, const double quantity_, const double price_): Order(symbol_, quantity_), price(price_) {}
  bool eval(const Market& m) {
    if(m[Order::symbol]->bid < price) {
      return true;
    }
    return false;
  }
};

class Hats : public System {
  void processTick(const Tick& t) {
    if(t.symbol == "USDJPY" && orders.size() < 100) {
      placeOrder(BuyLimit("USDJPY",100, 101.99));
    }
  }
}
