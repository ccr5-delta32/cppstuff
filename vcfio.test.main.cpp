#include <iostream>
#include "vcfio.h"
#include "optargs.h"

int main(int argc, char** argv) {
  CmdOpt opt(argc, argv, "v:");
  VCFio vcf(opt.getArg('v', 0));
  vcf.printComments();
  vcf.printHeader();
  vcf.printVcf(10);
}
