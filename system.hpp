///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <vector>
#include <simple.defs.hpp>
#include <tick.hpp>
#include <order.hpp>

namespace plsim {

  class System {
    std::vector<Trade> trades;
    std::vector<Order*> orders;
    std::vector<Position> positions;
    Market m;
    void updateMarket(tick) {
      // update price
      mkt[tick.symbol] = tick;
    }
    void processOrders() {
      for(size_t i = 0; i < orders.size(); i++) {
	if(orders[i]->eval(m)) {
	  fillOrder(orders[i],tick->timestamp);
	}
      }
    }
    void placeOrder(Order* o) { orders.push_back(o); }
    void fillOrder(const Order& o, posixt timestamp) {
      double exec_price;
      if(o.quantity > 0) {
	exec_price = m[o.symbol]->ask;
      } else {
	exec_price = m[o.symbol]->bid;
      }
      trades.push_back(Trade(o.symbol, timestamp, o.quantity, exec_price));
    }
    virtual void processTick(const Tick& t) = 0;
  public:
    void run(const std::vector<Ticks>& ticks) {
      for(std::vector<Ticks>::const_iterator tick = ticks.begin(); tick != ticks.end(); tick++) {
	updateMarket(tick);
	processOrders();
	processTick(*tick);
      }
    }
    std::ostream& operator<< (std::ostream& os, const Trade& t) {
      os << positions << std::endl << orders_ << endl;
    }
  };
}  // namespace plsim

#endif //SYSTEM_HPP
