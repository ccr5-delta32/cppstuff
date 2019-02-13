#include "pathcontent.h"
#include <iostream>

FilesWithExtInPath::FilesWithExtInPath(const fs::path& path,
                                       const std::string& ext) {
  sniffPath(path, ext, content);
}

void FilesWithExtInPath::sniffPath(const fs::path& path, const std::string& ext,
                                   std::vector<fs::path>& content) {
  if(!fs::exists(path)) {
    std::cout << "The path " << path << " does not exist!" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(!fs::is_directory(path)) {
    std::cout << "The path " << path << " is empty!" << std::endl;
    exit(EXIT_FAILURE);
  }

  fs::directory_iterator end;
  fs::directory_iterator it(path);

  while (it != end) {
    const fs::directory_entry de = *it;
    if(fs::is_regular_file(de) &&
       de.path().string().substr(de.path().string().length()-ext.length()) == ext) {
      std::cout << *it << " has extension: " << it->path().extension() <<
                   " but I captured " <<
                   de.path().string().substr(de.path().string().length()-ext.length()) <<
                   std::endl;
      content.push_back(*it);
    }
    ++it;
  }
}

std::vector<fs::path>& FilesWithExtInPath::getContent() {
  return content;
}
