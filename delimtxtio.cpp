#include "delimtxtio.h"
#include <iostream>
#include <boost/iostreams/device/file.hpp>

namespace bio = boost::iostreams;

DelimTxtIO::DelimTxtIO(const std::string &file, std::string mode, bool zipped) {
  // mode: w - write; r - read; wr - write/read
  isZipped = zipped;
  lineCnt = 0;
  filename = file;
  if (mode == "r") {
    std::cout << "Opening " << filename << " for reading" << std::endl;
    fileStream.open(file.c_str(), std::ios::in);
  } else if (mode == "w") {
    if (isZipped) {
      if (filename.substr(filename.size()-3) != ".gz") {
        filename = filename + ".gz";
      }
      std::cout << "Opening " << filename << " for writing gzipped data" << std::endl;
      fileStream.open(filename.c_str(), std::ios::out | std::ios::binary);
      compressor.push(bio::gzip_compressor(bio::gzip_params(bio::gzip::best_compression)));
      compressor.push(bio::file_sink(filename));
    } else {
      std::cout << "Opening " << filename << " for writing plain data" << std::endl;
      fileStream.open(file.c_str(), std::ios::out);
    }
  } else if (mode == "wr") {
    std::cout << "Opening " << file << " for reading/writing" << std::endl;
    fileStream.open(file.c_str(), std::ios::in | std::ios::out);
  } else {
    throw "DelimTxtIO::DelimTxtIO - Attempt to open file in unexpected mode(s)";
  }

  // If reading, look at first two bytes to see if file is gzipped
  if (mode == "r") {
    std::fstream tmp(file.c_str(), std::ios_base::binary | std::ios_base::in);
    char bytes[2];
    tmp.read(bytes, 2);
    tmp.close();

    if (bytes[0] == (char)0x1f && bytes[1] == (char)0x8b) {
      // looks like gzipped file, cout for testing
      std::cout << "detected gzipped file" << std::endl;
      isZipped = true;
      decompressor.push(bio::gzip_decompressor());
      decompressor.push(fileStream);
    } else {
      // assume plain text, cout for testing
      std::cout << "detected uncompressed file" << std::endl;
    }
  }
}

DelimTxtIO::DelimTxtIO(std::fstream &Stream, bool zipped) {
  // Used when providing an externally instantiated fstream
  isZipped = false;
  lineCnt = 0;
  swap(fileStream, Stream);

  if (zipped) {
    isZipped = true;
    decompressor.push(bio::gzip_decompressor());
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
  std::cerr << "Warning: Could not retrieve field " << field << std::endl;
  return false;
}

void DelimTxtIO::putLine(std::string& oline) {
  try {
    if (isZipped) {
      if (oline.back() != '\n') {
        oline += '\n';
      }
      compressor.write(oline.c_str(), oline.size());
    } else {
      fileStream << oline << (oline.back() == '\n' ? : '\n');
    }
  } catch (std::exception& e) {
    throw "An exception occurred while writing " + filename + ": " + e.what();
  }
}

std::string DelimTxtIO::pline() {
  return line;
}

void DelimTxtIO::close() {
  fileStream.close();
}
