# cppstuff

## optargs, cmdopt

Can play the role of optarg from unistd.h. Include only the optargs.h header and
use as such:

```
int main(int argc, char** argv) {
  CmdOpt opt(argc, argv, "a-b:c+d*");
  // get the arguments like this:
  opt.chkOpt('a'); // returns a bool indicating if the opt was present
  opt.getArg('b', n); // where n = int, returns the nth argument as string
  opt.getArg('c'); // returns a reference to a vector of strings containing all
                  // arguments
}
```
optstring:

(-) - No arguments allowed. Any argument will be ignored.   
(:) - Exactly 1 argument must be provided. Additional arguments will be ignored.   
(+) - A minimum of 1 argument and up to the maximum value of int arguments.  
(\*) - A minimum of 0 arguments and up to the maximum value of int arguments.  

The optstring must follow the pattern of opt,token,opt,token...

## delimtxtio

Can read text files, that maybe gzipped, and this will be automatically
detected. Required boost::iostreams for gzipped files.

## vcfio

Uses the above to read (yes, only the i out of io so far) a vcf file

```
g++ -std=c++11 -lboost_iostreams delimtxtio.cpp cmdopt.cpp optargs.cpp vcfio.cpp vcfio.test.main.cpp -o vcfio.test
```

And then:

```
vcfio.test -v <vcf.file>
```

## pathcontent
Can be used to get all files with a certain extension in a certain path
Example:

```
#include "cppstuff/pathcontent.h"
#include "cppstuff/optargs.h"

int main(int argc, char** argv) {
  CmdOpt opt(argc, argv, "p:e:");
  FilesWithExtInPath pcont(opt.getArg('p', 0), opt.getArg('e', 0));
  for (const auto& tmp : pcont.getContent()) {
    std::cout << tmp << std::endl;
  }
}
```

compile:

```
g++ -std=c++11 -l boost_system -l boost_filesystem pathcontent.cpp cmdopt.cpp optargs.cpp main.cpp -o testpath
```

And then:

```
testpath -p some_path -e .ext
```
