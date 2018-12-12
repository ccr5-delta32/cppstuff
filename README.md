# cppstuff

## optargs, cmdopt

Can play the role of optarg from unistd.h. Include only the optargs.h header and
use as such:

int main(int argc, char** argv) {
  CmdOpt opt(argc, argv, "a-b:c+d\*");
  // get the arguments like this:
  opt.chkOpt('a'); // returns a bool indicating if the opt was present
  opt.getArg('b', n); // where n = int, returns the nth argument as string
  opt.getArg('c'); // returns a reference to a vector of strings containing all
                  // arguments
}

optstring:

(-) - No arguments allowed.
(:) - Exactly 1 argument must be provided
(+) - A minimum of 1 argument and up to the maximum value of int arguments
(*) - A minimum of 0 arguments and up to the maximum value of int arguments

The optstring must follow the pattern of opt,token,opt,token...

## delimtxtio

Can read text files, that maybe gzipped, and this will be automatically
detected. Required boost::iostreams for gzipped files.

