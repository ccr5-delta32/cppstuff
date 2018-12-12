#include <fstream>
#include <string>
#include <vector>
#include "delimtxtio.h"

class VCFio {

  // tackling the i in io first now

  public:
    VCFio(const std::string fileName);

    void setAssFile(const std::string fileName);
    void readAssFile();

    // for testing
    void printVec(const std::vector<std::string> &v);
    int printVcf(int n = 0);
    void printHeader();
    void printComments();

  private:
    std::string assFile;
    std::vector<std::string> comments;
    std::string header;
    std::vector<std::vector<std::string>> vcf;
};

