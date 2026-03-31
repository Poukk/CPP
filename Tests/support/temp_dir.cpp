#include "support/temp_dir.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include <cstdlib>

namespace test_support {

scoped_temp_dir::scoped_temp_dir() {
    char pattern[] = "/tmp/cpp-tests-XXXXXX";
    char *created = mkdtemp(pattern);

    if (created == 0) {
        throw std::runtime_error("failed to create temporary directory");
    }
    path_ = created;
}

scoped_temp_dir::~scoped_temp_dir() {
    std::error_code error;
    std::filesystem::remove_all(path_, error);
}

std::string scoped_temp_dir::path() const { return path_; }

std::string scoped_temp_dir::file_path(const std::string &name) const {
    return path_ + "/" + name;
}

void scoped_temp_dir::write_file(const std::string &name, const std::string &content) const {
    std::ofstream output(file_path(name).c_str());

    if (!output.is_open()) {
        throw std::runtime_error("failed to open temporary file for writing");
    }
    output << content;
    if (!output) {
        throw std::runtime_error("failed to write temporary file");
    }
}

std::string scoped_temp_dir::read_file(const std::string &name) const {
    std::ifstream input(file_path(name).c_str());
    std::string content;
    char ch;

    if (!input.is_open()) {
        throw std::runtime_error("failed to open temporary file for reading");
    }

    while (input.get(ch)) {
        content += ch;
    }
    return content;
}

}  // namespace test_support
