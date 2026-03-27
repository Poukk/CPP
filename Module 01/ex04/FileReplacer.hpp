#ifndef FILEREPLACER_HPP
#define FILEREPLACER_HPP

#include <string>

class FileReplacer {
  private:
    std::string inputFileName;
    std::string search;
    std::string replacement;

    std::string replaceAll(const std::string &content) const;

  public:
    FileReplacer(const std::string &inputFileName, const std::string &search,
                 const std::string &replacement);
    ~FileReplacer();

    bool process() const;
};

#endif
