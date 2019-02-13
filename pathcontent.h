#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace fs = ::boost::filesystem;

class FilesWithExtInPath {
  
  public:
    FilesWithExtInPath(const fs::path& path, const std::string& ext);
    std::vector<fs::path> getContent() const;

  private:
    std::vector<fs::path> content; 
    void sniffPath(const fs::path& path, const std::string& ext,
                   std::vector<fs::path>& content);

};
