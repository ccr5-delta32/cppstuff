# cppstuff

## optargs, cmdopt

Can play the role of optarg from unistd.h to some degree.
Include only the optargs.h header and use as such:

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
(|) - A minimum of 0 arguments and a maximum of 1 argument. 
(+) - A minimum of 1 argument and up to the maximum value of int arguments.  
(\*) - A minimum of 0 arguments and up to the maximum value of int arguments.  

Options must be a single character.
The optstring must follow the pattern of opt,token,opt,token...
Tokens that allow 0 arguments are optional options that may be omitted from the commandline.

## delimtxtio

Can read text files, that maybe gzipped, and this will be automatically
detecte. Can also write text files, optionally gzipped.
Requires boost::iostreams for gzipped files.

Use case:
```
#include "delimtxtio.h"
#include <memory>
#include <string>
#include <vector>

...

// reading (default), automatic detection if gzipped or not.
std::unique_ptr<DelimTxtIO> file(new DelimTxtIO("filename"));
// get a line as a string
std::string line;
file->getLine(line);
// get a line and split on a delimiter
std::vector<std::string> linevec;
file->getLine(linevec, '\t');

// writing plain text
std::unique_ptr<DelimTxtIO> file1(new DelimTxtIO("filename", "w"));
// or gzipped text, appending .gz to the filename if it isn't there yet.
std::unique_ptr<DelimTxtIO> file2(new DelimTxtIO("filename", "w", true));
std::string outline = "This is just a test";
file1->putLine(outline);
file2->putLine(outline);
```

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
#include <iostream>

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

## util.hpp
A collection of convenience functions:

```
#include "util.hpp"

Util util;
```

# printVec
outputs an arbitrary number of elements of a vector to std::cout, starting from the first. Default is all elements!

```
util.printVec(somevector, 25); // prints first 25 elements
```

# printMapKeys
outputs an arbitrary number of map (eg. std::map or std::unordered_map) keys to std::cout

```
util.printMapKeys(somemap, 10); // prints first 10 keys (defaul=25). 
```

# has
tests if an element occurs in a vector

```
std::vector<int> chk{1, 2, 3, 4, 5};
util.has(chk, 3); // returns true
util.has(chk, 6); // returns false
```

# getIndx
return the index of the first instance found of some element in a vector

```
std::vector<int> chk{1, 2, 3, 4, 5};
util.getIndx(chk, 3); // returns 2
// returns -1 if the element is not found in the vector
```

# vec2str
Makes a string out of all the elements in a vector separated with an arbitrary delimiter

```
std::vector<int> chk{1, 2, 3, 4, 5};
std::string test = util.vec2str(chk, " "); // returns "1 2 3 4 5"

```
