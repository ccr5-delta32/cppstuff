#include <string>
#include <vector>
#include "cmdopt.h"

class OptArgs {

  public:
    OptArgs(char opt, CmdOpt& cmdopt);
    const char& getOpt() const;
    void addArg(const std::string& argh);
    const std::vector<std::string>& getArg() const;
    const int& nArgs() const;
    friend bool CmdOpt::chkOptValidity() const;

  private:
    int nargs = 0;
    char opt;
    std::vector<std::string> args;
    int minargs = 0;
    int maxargs = 0;
};

