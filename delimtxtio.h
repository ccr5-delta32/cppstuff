/* (1) getLine(std::string &lineData) 
 *     iclears this->line, reads a line to this->line and then assigns
 *     to lineData
 * (2) getLine(std::vector<std::string> &lineData, char delim = '\t')
 *     calls (1), clears lineData!, splits this->line into lineData by
 *     calling (3)
 * (3) splitLine(std::vector<std::string> &lineData, char delim) splits whatever
 *     is in this->line on delim into lineData
 * (4) getField(std::string &lineData, int field, char delim='\t')
 *     Clears linedata!, calls (1), splits the string field times and then
 *     assigns the data to lineData */

#include <string>
#include <vector>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

class DelimTxtIO {

  public:
    DelimTxtIO(const std::string &file);
    DelimTxtIO(std::ifstream &iStream, bool zipped=false);
    bool getLine(/*out*/std::string &lineData);
    bool getLine(/*out*/std::vector<std::string> &lineData,
                 /*in*/char delim = '\t');
    bool getField(/*out*/std::string &lineData, /*in*/int field,
                 char delim='\t');
    void splitLine(std::vector<std::string> &lineData, char delim='\t');
    void incCnt();
    unsigned int getCnt();

  private:
    boost::iostreams::filtering_stream<boost::iostreams::input> decompressor;
    std::ifstream fileStream;
    std::ifstream* pfileStream = &fileStream;
    bool isZipped;
    unsigned int lineCnt = 0;
    std::string line;
};
