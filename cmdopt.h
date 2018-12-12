#include <string>
#include <vector>
#include <map>

class OptArgs;

class CmdOpt {

  public:
    CmdOpt(int& argc, char** argv, std::string optstring);
    bool chkOpt(char opt);
    void print_args();
    const std::string& getArg(char opt, int i) const;
    const std::vector<std::string>& getArg(char opt) const;
    bool chkOptValidity() const;
    char getOptToken(char opt);
    
  private:
    int argc;
    std::vector<std::string> cmdline;
    std::string optstr;
    std::map<char, char> optstringOpts;
    void processOptstring(std::string optstring);
    std::vector<OptArgs> optargbox;
};
