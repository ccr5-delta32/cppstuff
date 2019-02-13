#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace fs = ::boost::filesystem;

class FilesWithExtInPath {
  
  public:
    FilesWithExtInPath();
    FilesWithExtInPath(const fs::path& path, const std::string& ext);
    std::vector<fs::path> getContent() const;
    int getCnt() const;

  private:
    std::vector<fs::path> content; 
    int cnt;
    void sniffPath(const fs::path& path, const std::string& ext,
                   std::vector<fs::path>& content);

};
