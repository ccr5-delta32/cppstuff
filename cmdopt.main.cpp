#include "optargs.h"

int main(int argc, char** argv) {
  CmdOpt opt(argc, argv, "a:b*c-d+");
  opt.print_args();
}
