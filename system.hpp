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

  typedef double posixct;

  class Order {
  private:
    Instrument& i_;
  public:
    Order(Instrument& i) i_(i) {}
    virtual void condition();
    virtual void cancel_condition();
    virtual void action();
  };

  class System {
    Trades trades;
    Orders orders;
    Positions positions;

    Ticks collectTicks(vector<instrument>& instruments) {
      // merge all instruments into one table
      // of all ticks
    }
    public:
    void run(vector<instrument> instruments, posixct start, posixct end) {
      vector<posixct> ticks(collectTicks(instruments));
      for(i = 0; i < ticks.size(); i++) {
	for(j = 0; j < orders.size(); j++) {
	  evalOrder(instruments,ticks[i],orders[j]);
	}
	// fixme: fire each inst tick separately
	// assuming there will be many cases of ties
	processTick(t[i])
      }
    }

    std::ostream& operator<< (std::ostream& os, const Trade& t) {
      os << positions << std::endl << orders_ << endl;
    }
    virtual void processTick(Tick& t) {}
  };
}  // namespace plsim

#endif //SYSTEM_HPP
