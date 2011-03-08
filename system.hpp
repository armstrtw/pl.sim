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
#include <investment.hpp>

namespace plsim {
  class Tick {
    std::string symbol_;
    posixct timestamp_;
    double bid_;
    double ask_;
  public:
    Tick(std::string symbol, posixct timestamp, double bid, double ask) symbol_(symbol), timestamp_(timestamp), bid_(bid), ask_(ask) {}
  };

  typedef double posixct;
  typedef std::map<std::string,tick*> Market;

  class Order {
  private:
    Instrument& i_;
  public:
    Order(Instrument& i) i_(i) {}
    virtual const bool condition(Market& m);
    virtual bool cancel_condition(Market& m);
    virtual void action();
  };

  class System {
    std::vector<Trade> trades;
    std::vector<Order> orders;
    std::vector<Position> positions;
    Market m;
    public:
    void run(const vector<Ticks>& ticks) {
      for(vector<Ticks>::const_iterator tick = ticks.begin(); tick != ticks.end(); tick++) {
	// update price
	mkt[tick.symbol_;] = &tick;
	for(vector<Order>::iterator order = orders.begin(); order != orders.end(); order++) {
	  if(order.eval(mkt)) {
	    order.action();
	  }
	}
	// fixme: fire each inst tick separately
	// assuming there will be many cases of ties
	processTick(t[i]);
      }
    }
    std::ostream& operator<< (std::ostream& os, const Trade& t) {
      os << positions << std::endl << orders_ << endl;
    }
    virtual void processTick(Tick& t) {}
  };
}  // namespace plsim

#endif //SYSTEM_HPP
