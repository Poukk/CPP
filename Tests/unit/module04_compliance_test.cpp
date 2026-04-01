#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "support/process_runner.hpp"
#include "support/temp_dir.hpp"

namespace {

std::string shell_quote(const std::string &value) {
    return "'" + value + "'";
}

std::string read_file(const std::filesystem::path &path) {
    std::ifstream input(path.c_str());
    std::string content;
    char ch;

    EXPECT_TRUE(input.is_open()) << path.string();
    while (input.get(ch)) {
        content += ch;
    }
    return content;
}

std::vector<std::string> module_dirs() {
    return std::vector<std::string>{MODULE04_EX00_DIR, MODULE04_EX01_DIR, MODULE04_EX02_DIR};
}

std::vector<std::string> forbidden_tokens() {
    return std::vector<std::string>{
        "using namespace ",
        " friend ",
        "printf(",
        "malloc(",
        "calloc(",
        "realloc(",
        "free(",
        "<vector>",
        "<map>",
        "<list>",
        "<algorithm>",
        "std::vector",
        "std::map",
        "std::list"};
}

}  // namespace

TEST(Module04ComplianceTest, MakefilesUseRequiredCompilerAndFlags) {
    const std::vector<std::string> module_paths = module_dirs();

    for (std::vector<std::string>::const_iterator it = module_paths.begin();
         it != module_paths.end(); ++it) {
        const std::filesystem::path makefile = std::filesystem::path(*it) / "Makefile";
        const std::string content = read_file(makefile);

        EXPECT_NE(content.find("CXX = c++"), std::string::npos) << makefile.string();
        EXPECT_NE(content.find("-Wall -Wextra -Werror -std=c++98"), std::string::npos)
            << makefile.string();
    }
}

TEST(Module04ComplianceTest, SourcesAvoidForbiddenTokensCalledOutByTheCorrectionPage) {
    const std::vector<std::string> module_paths = module_dirs();
    const std::vector<std::string> tokens = forbidden_tokens();

    for (std::vector<std::string>::const_iterator dir = module_paths.begin();
         dir != module_paths.end(); ++dir) {
        for (std::filesystem::directory_iterator it(*dir), end; it != end; ++it) {
            const std::filesystem::path path = it->path();
            const std::string extension = path.extension().string();

            if (extension != ".cpp" && extension != ".hpp" && path.filename() != "Makefile") {
                continue;
            }

            const std::string content = read_file(path);
            for (std::vector<std::string>::const_iterator token = tokens.begin();
                 token != tokens.end(); ++token) {
                EXPECT_EQ(content.find(*token), std::string::npos)
                    << path.string() << " contains forbidden token " << *token;
            }
        }
    }
}

TEST(Module04ComplianceTest, HeadersCompileIndependentlyWithCpp98Flags) {
    const std::vector<std::string> module_paths = module_dirs();

    for (std::vector<std::string>::const_iterator dir = module_paths.begin();
         dir != module_paths.end(); ++dir) {
        for (std::filesystem::directory_iterator it(*dir), end; it != end; ++it) {
            const std::filesystem::path header = it->path();

            if (header.extension() != ".hpp") {
                continue;
            }

            test_support::scoped_temp_dir temp_dir;
            const std::string source_name = header.stem().string() + "_header_check.cpp";
            const std::string source_path = temp_dir.file_path(source_name);
            const std::string object_path = temp_dir.file_path(header.stem().string() + ".o");
            const std::string source =
                "#include \"" + header.filename().string() + "\"\n"
                "int main() { return 0; }\n";
            const std::string command =
                "c++ -std=c++98 -Wall -Wextra -Werror -I" + shell_quote(*dir) +
                " -c " + shell_quote(source_path) +
                " -o " + shell_quote(object_path);

            temp_dir.write_file(source_name, source);
            const test_support::ProcessResult result =
                test_support::run_process("/bin/sh", std::vector<std::string>{"-c", command});

            EXPECT_EQ(result.exit_code, 0)
                << "failed for " << header.string() << "\n" << result.stderr_output;
            EXPECT_EQ(result.stderr_output, "");
        }
    }
}
