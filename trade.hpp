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

#ifndef TRADE_HPP
#define TRADE_HPP

#include <iostream>
#include <investment.hpp>

namespace plsim {

  class Trade {
  public:
    string symbol;
    posixct timestamp;
    double quantity;
    double price;
    Trade(string symbol_,double timestamp_,double quantity_,double price_): symbol(symbol_), timestamp(timestamp_), quantity(quantity_), price(price_) {}
    std::ostream& operator<< (std::ostream& os, const Trade& t) {
      os << symbol << "|" << timestamp << "|" << quantity << "|" << price << std::endl;
    }
  };
}  // namespace plsim

#endif //TRADE_HPP
