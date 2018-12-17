#include <iostream>
#include <sstream>
#include "vcfio.h"

VCFio::VCFio(const std::string fileName) {
  assFile = fileName;
  readAssFile();
}

void VCFio::setAssFile(const std::string fileName) {
  assFile = fileName;
}

void VCFio::readAssFile() {
  DelimTxtIO vcfReader(assFile);
  std::string line;
  while(vcfReader.getLine(line)) {
    if (line.substr(0, 2) == "##") {
      comments.push_back(line);
      continue;
    }
    // Put header line in header
    if (line[0] == '#') {
      header = line;
      break;
    }
  }

  std::vector<std::string> vcfline;
  while(vcfReader.getLine(vcfline)) {
    vcf.push_back(vcfline);
  }

  std::cout << vcfReader.getCnt() << " lines read from the VCF, of which " <<
               vcfReader.getCnt()-comments.size()-1 <<
               " are data" << std::endl;
}

// Below some functions for testing purposes
void VCFio::printVec(const std::vector<std::string> &v) {
  for (const auto &element : v) {
    std::cout << element << '\t';
  }
  std::cout << std::endl;
}

void VCFio::printComments() {
  std::cout << "The comment lines in the VCF:" << std::endl;
  for (int  i = 0; i != (int)comments.size(); i++) {
    std::cout << comments[i] << std::endl;
  }
}

void VCFio::printHeader() {
  std::cout << "The header of the VCF data:\n" << header << std::endl;
}

int VCFio::printVcf(int n/*= 0*/) {
  std::cout << "\nPrinting some VCF data:" << std::endl;
  for (int  i = 0; i != int(vcf.size()); i++) {
    if (n == 0 || i < n ) {
      printVec(vcf[i]);
      continue;
    }
  }
  return 0;
}
