#ifndef TESTS_SUPPORT_PROCESS_RUNNER_HPP
#define TESTS_SUPPORT_PROCESS_RUNNER_HPP

#include <string>
#include <vector>

namespace test_support {

struct ProcessResult {
    int exit_code;
    std::string stdout_output;
    std::string stderr_output;
};

ProcessResult run_process(const std::string &path,
                          const std::vector<std::string> &args,
                          const std::string &stdin_data = "");

}  // namespace test_support

#endif
