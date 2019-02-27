#include "optargs.h"
#include <iostream>
#include <utility>

CmdOpt::CmdOpt(int &argc, char** argv, std::string optstring) {
  processOptstring(optstring);
  cmdline = std::vector<std::string>(argv, argv + argc);
  this->argc = argc;

  bool wasopt = false;
  for (int i = 1; i < (int)cmdline.size(); i++) {
    if (argv[i][0] == '-') {
      if (!chkOptstringOpts(argv[i][1])) {
        std::cout << "Unexpected option " << argv[i] << " and its args will be ignored!" << std::endl;
        wasopt = false;
        continue;
      }
      optargbox.push_back(OptArgs(argv[i][1], *this));
      wasopt = true;
    }
    if (argv[i][0] != '-' && wasopt) {
      optargbox.back().addArg(argv[i]);
    }
  }
}

void CmdOpt::processOptstring(std::string optstring) {
  // check if length dividable by 2 because every option needs a classifier
  if (optstring.size() % 2 != 0) {
    std::cout << "optstring length not a multiple of 2! \"" << optstring << "\"" << std::endl;
    exit(EXIT_FAILURE);
  }

  // This would be risky if optstring length is not a multiple of 2!
  for (std::string::iterator it=optstring.begin(); it!=optstring.end(); it++) {
    std::pair<std::map<char, char>::iterator, bool> insertChk =
      optstringOpts.insert(std::pair<char, char>(*it, *std::next(it, 1)));
    it++;
    if (!(insertChk.second)) {
      std::cout << "Failed to add opt-arg pair to the map" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

char CmdOpt::getOptToken(char opt) {
  for (const std::pair<char, char>& tmp : optstringOpts) {
    if (tmp.first == opt) {
      return tmp.second;
    }
  }
  std::cerr << "getOptToken: no option -" << opt << " provided in optstring" << std::endl;
  exit(EXIT_FAILURE);
}

bool CmdOpt::chkOptstringOpts(char opt) {
  for (const std::pair<char, char>& tmp : optstringOpts) {
    if (tmp.first == opt) {
      return true;
    }
  }
  return false;
}

bool CmdOpt::chkOpt(char opt) const {
  for (const OptArgs& tmp : optargbox) {
    if (tmp.getOpt() == opt) {
      return true;
    }
  }
  return false;
}

bool CmdOpt::chkOptValidity() const {
  bool nogood = false;
  for (const OptArgs &tmp : optargbox) {
    if (tmp.nargs < tmp.minargs) {
      std::cerr << "Error! Option -" << tmp.opt << " must have at least " << tmp.minargs <<
                   " arguments but it has only " << tmp.nargs << std::endl;
      nogood = true;
    }
    if (!nogood) {
      return true;
    } else {
      exit(EXIT_FAILURE);
    }
  }
  return false;
}

const std::vector<std::string>& CmdOpt::getArg(char opt) const {
  // first call to getArg will check if all OptArgs minargs are valid, and will do this only once
  static bool once = [this]() {
    return chkOptValidity();
  } ();

  for (const OptArgs& tmp : optargbox) {
    if (tmp.getOpt() == opt) {
      if (tmp.nArgs() == 0) {
        std::cerr << "Warning! Attempt to get args from opt -" << opt << ", which has no args" << std::endl;
      }
      return tmp.getArg();
    }
  }
  std::cerr << "Error! Option " << opt << " not found in the commandline" << std::endl;
  exit(EXIT_FAILURE);
}

const std::string& CmdOpt::getArg(char opt, int i) const {
  const std::vector<std::string>& optarg = getArg(opt);
  if (i < (int)optarg.size()) {
    return optarg[i];
  }
  std::cerr << "Error! Attempt to get argument " << i << " from option -" << opt <<
               " but this only has " << (int)optarg.size() << " arguments" << std::endl;
  exit(EXIT_FAILURE);
}

// function for testing
void CmdOpt::print_args() {
  std::cout <<  optargbox.size() << " options and arguments" << std::endl;

  std::cout << "\ninvokation:" << std::endl;
  for (auto str : cmdline) {
    std::cout << str << ' ';
  }; std::cout << std::endl;
  std::cout << "\nopts and args:" << std::endl;
  for (auto& optarg : optstringOpts) {
    std::cout << optarg.first << ": ";
    for (auto& argstr : getArg(optarg.first)) {
      std::cout << argstr << ' ';
    }; std::cout << std::endl;
  }; std::cout << std::endl;
}
