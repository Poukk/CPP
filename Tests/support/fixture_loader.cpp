#include "support/fixture_loader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace test_support {

std::string load_fixture(const std::string &name) {
    const std::string path = std::string(TESTS_FIXTURES_DIR) + "/" + name;
    std::ifstream input(path.c_str());
    std::ostringstream content;

    if (!input.is_open()) {
        throw std::runtime_error("could not open fixture: " + path);
    }

    content << input.rdbuf();
    return content.str();
}

}  // namespace test_support
