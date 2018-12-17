#include "delimtxtio.h"
#include <iostream>
#include <sstream>

DelimTxtIO::DelimTxtIO(const std::string &file) {
  isZipped = false;
  lineCnt = 0;
  fileStream.open(file.c_str(), std::ifstream::in);

  // Look at first two bytes to see if file is gzipped
  std::ifstream tmp(file.c_str(), std::ios_base::binary | std::ios_base::in);
  char bytes[2];
  tmp.read(bytes, 2);
  tmp.close();

  if (bytes[0] == (char)0x1f && bytes[1] == (char)0x8b) {
    // looks like gzipped file, cout for testing
    std::cout << "detected gzipped file" << std::endl;
    isZipped = true;
    decompressor.push(boost::iostreams::gzip_decompressor());
    decompressor.push(fileStream);
  } else {
    // assume plain text, cout for testing
    std::cout << "detected uncompressed file" << std::endl;
  }
}

DelimTxtIO::DelimTxtIO(std::ifstream &iStream, bool zipped) {
  // Used when providing an externally instantiated ifstream
  isZipped = false;
  lineCnt = 0;
  swap(fileStream, iStream);

  if (zipped) {
    isZipped = true;
    decompressor.push(boost::iostreams::gzip_decompressor());
    decompressor.push(fileStream);
  }
}

void DelimTxtIO::incCnt() {
  lineCnt++;
}

unsigned int DelimTxtIO::getCnt() {
  return lineCnt;
}

bool DelimTxtIO::getLine(std::string &lineData) {
  line.clear();
  if ((isZipped && std::getline(decompressor, line)) ||
      (std::getline(fileStream, line))) {
    incCnt();
    lineData = line;
    return true;
  }
  return false;
}

void DelimTxtIO::splitLine(std::vector<std::string> &lineData, char delim) {
  std::istringstream istr(line);
  std::string field;
  while (std::getline(istr, field, delim)) {
    lineData.push_back(field);
  }
}

bool DelimTxtIO::getLine(std::vector<std::string> &lineData, char delim) {
  // get a line or return false
  if (!getLine(line)) {
     return false;
  }
  
  // erase the vector passed in to receive the output!
  lineData.clear();

  // split the line on delim
  splitLine(lineData, delim);
  return true;
}

bool DelimTxtIO::getField(std::string &lineData, int field,
                          char delim) {
  lineData.clear();
  // get a line or return false
  if (!getLine(line)) {
     return false;
  }

  // get the requested field from the line or return false with a warning
  int cnt = -1;
  std::istringstream istr(line);
  std::string field_data;
  while (std::getline(istr, field_data, delim)) {
    cnt++;
    if (cnt == field) {
      lineData = field_data;
      return true;
    }
  }
  std::cout << "Warning: Could not retrieve field " << field << std::endl;
  return false;
}
