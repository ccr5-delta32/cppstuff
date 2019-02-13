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
  int cnt = 0;

  while (it != end) {
    const fs::directory_entry de = *it;
    if(fs::is_regular_file(de) &&
       de.path().string().substr(de.path().string().length()-ext.length()) == ext) {
      content.push_back(*it);
      cnt++;
    }
    ++it;
  }
  std::cout << cnt << " files with extension " << ext <<
               " were found in " << path << std::endl;
}

std::vector<fs::path>& FilesWithExtInPath::getContent() {
  return content;
}
