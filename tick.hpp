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

#ifndef TICK_HPP
#define TICK_HPP

#include <string>
#include <simple.defs.hpp>

namespace plsim {

  class Tick {
  public:
    std::string symbol;
    posixct timestamp;
    double bid;
    double ask;
    Tick(std::string symbol_, posixct timestamp_, double bid_, double ask_):
      symbol(symbol_), timestamp(timestamp_), bid(bid_), ask(ask_) {}
  };

} // namespace plsim
#endif //TICK_HPP
