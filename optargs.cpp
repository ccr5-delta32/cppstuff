#include "optargs.h"
#include <limits>
#include <iostream>

OptArgs::OptArgs(char opt, CmdOpt& cmdopt) {
  this->opt = opt;

  switch(cmdopt.getOptToken(opt)) {
    case '-':
      minargs = 0;
      maxargs = 0;
      break;
    case ':':
      minargs = 1;
      maxargs = 1;
      break;
    case '|':
      minargs = 0;
      maxargs = 1;
      break;
    case '+':
      minargs = 1;
      maxargs = std::numeric_limits<int>::max();
      break;
    case '*':
      minargs = 0;
      maxargs = std::numeric_limits<int>::max();
  }
}

const char& OptArgs::getOpt() const {
  return opt;
}

void OptArgs::addArg(const std::string& argh) {
  if (maxargs == 0) {
    std::cout << "Warning! Option -" << opt << " may not have arguments so they will be ignored" << std::endl;
  } else if (nargs == maxargs) {
    std::cout << "Warning! Option -" << opt << " may not have more than " << maxargs <<
                 " arguments. The others will be ignored" << std::endl;
  } else {
    args.push_back(argh);
    nargs++;
  }
}

const std::vector<std::string>& OptArgs::getArg() const{
  return args;
}

const int& OptArgs::nArgs() const {
  return nargs;
}
