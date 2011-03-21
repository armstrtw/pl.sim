#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "tickstream.pb.h"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace plsim;


int64_t string2ptime(std::string& s) {
  const ptime epoch(boost::gregorian::date(1970, 1, 1));
  ptime x(time_from_string(s));
  return  (x - epoch).total_microseconds();
}

void csv2ticks(const std::string fname, const std::string splitter) {
  std::ifstream fin;
  string buf;
  vector<string> splitbuf;
  typedef vector< boost::iterator_range<string::iterator> > find_vector_type;
  fin.open(fname.c_str());

  if(!fin.is_open()) {
    return;
  }

  TickStream ts;
  int64_t i(1);
  while(getline(fin, buf)) {
    if(i++ % 10000000 == 0) { cout << "."; fflush(stdout);}
    boost::split(splitbuf, buf, boost::is_any_of(splitter));
    //if(i > 10000) { break; }
    Tick* t = ts.add_tick();
    t->set_symbol(splitbuf[1]);
    t->set_timestamp(string2ptime(splitbuf[0]));
    t->set_bid(atof(splitbuf[2].c_str()));
    t->set_ask(atof(splitbuf[3].c_str()));
  }
  cout << endl;
  fin.close();
  cout << "number of records " << i << endl;
  {
    // Write the new address book back to disk.
    fstream output("tickstream.ts", ios::out | ios::trunc | ios::binary);
    if (!ts.SerializeToOstream(&output)) {
      cerr << "Failed to write tickstream." << endl;
    }
    output.close();
  }
}

int main() {
  csv2ticks("/var/archive/work/data/barclays.tick.data/tick.stream.csv", ",");
  google::protobuf::ShutdownProtobufLibrary();
}
