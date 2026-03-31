#ifndef TESTS_SUPPORT_TEMP_DIR_HPP
#define TESTS_SUPPORT_TEMP_DIR_HPP

#include <string>

namespace test_support {

class scoped_temp_dir {
   public:
    scoped_temp_dir();
    ~scoped_temp_dir();

    std::string path() const;
    std::string file_path(const std::string &name) const;
    void write_file(const std::string &name, const std::string &content) const;
    std::string read_file(const std::string &name) const;

   private:
    std::string path_;
};

}  // namespace test_support

#endif
