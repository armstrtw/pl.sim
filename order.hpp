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

#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <market.hpp>

namespace plsim {

  class Order {
  public:
    const std::string symbol;
    const double quantity;
    bool canceled;
    bool filled;

    Order(const std::string symbol_, const double quantity_): symbol(symbol_), quantity(quantity_), canceled(false) {}
    void cancel() { canceled = true; }
    virtual const bool eval(const Market& m) = 0;
  };

} // namespace plsim
#endif //ORDER_HPP
