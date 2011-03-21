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
#include <list>
#include <market.hpp>
#include <positions.hpp>
#include <tick.hpp>
#include <order.hpp>
#include <trade.hpp>

namespace plsim {

  bool filled_or_canceled(Order* o) { return (o->filled || o->canceled) ? true : false; }

  class System {
  protected:
    std::vector<Trade> trades;
    std::list<Order*> orders;
    Positions positions;
    Market market;
    ptime timestamp;

    void updateMarket(const Tick& tick) {
      // update price
      market[tick.symbol] = const_cast<Tick*>(&tick);
      // update time
      timestamp = tick.timestamp;
    }
    void processOrders() {
      //for(size_t i = 0; i < orders.size(); i++) {
      for(std::list<Order*>::iterator o = orders.begin(); o != orders.end(); o++) {
	if((*o)->eval(market)) {
	  fillOrder(*o,timestamp);
	}
      }
      // remove filled/canceled orders
      //remove_if(orders.begin(), orders.end(), filled_or_canceled)
      orders.remove_if(filled_or_canceled);
    }
    void placeOrder(Order* o) { orders.push_back(o); }
    void fillOrder(Order* o, const ptime timestamp) {
      double exec_price;
      if(o->quantity > 0) {
	exec_price = market[o->symbol]->ask;
      } else {
	exec_price = market[o->symbol]->bid;
      }
      o->filled = true;
#ifdef DEBUG
      std::cout << "adding Trade:" <<
	o->symbol << " " << timestamp << " " << " " << o->quantity << " " << exec_price << std::endl;
#endif
      trades.push_back(Trade(o->symbol, timestamp, o->quantity, exec_price));
    }
    virtual void processTick(const Tick& t) = 0;
  public:
    void run(const std::vector<Tick>& ticks) {
      for(std::vector<Tick>::const_iterator tick = ticks.begin(); tick != ticks.end(); tick++) {
	updateMarket(*tick);
	processOrders();
	processTick(*tick);
      }
    }
    friend std::ostream& operator<< (std::ostream& os, const System& s) {
      // os << s.positions << std::endl << s.orders_ << endl;
      os << "not implemented" << std::endl;
      return os;
    }
  };
}  // namespace plsim

#endif //SYSTEM_HPP
