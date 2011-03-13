
void ticks2csv(std::string fname, std::string splitter, vector<Tick>& ticks) {
  ifstream fin;
  string buf;
  vector<string> splitbuf;
  typedef vector< boost::iterator_range<string::iterator> > find_vector_type;
  fin.open(fname.c_str());

  if(!fin.is_open()) {
    return;
  }

  while(getline(fin, buf)) {
    boost::split(splitbuf, buf, boost::is_any_of(splitter));
    ticks.push_back(Tick(splitbuf[2],toposixct(splitbuf[0]+splitbuf[3]),splitbuf[4],splitbuf[5]))
      }
  fin.close();
}
