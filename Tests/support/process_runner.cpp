#include "support/process_runner.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace test_support {

namespace {

std::string read_all(int fd) {
    std::string result;
    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        result.append(buffer, static_cast<std::size_t>(bytes_read));
    }
    return result;
}

void close_fd(int fd) {
    if (fd >= 0) {
        close(fd);
    }
}

}  // namespace

ProcessResult run_process(const std::string &path,
                          const std::vector<std::string> &args,
                          const std::string &stdin_data) {
    int stdin_pipe[2] = {-1, -1};
    int stdout_pipe[2] = {-1, -1};
    int stderr_pipe[2] = {-1, -1};

    if (pipe(stdin_pipe) != 0 || pipe(stdout_pipe) != 0 || pipe(stderr_pipe) != 0) {
        throw std::runtime_error("failed to create process pipes");
    }

    pid_t pid = fork();
    if (pid < 0) {
        close_fd(stdin_pipe[0]);
        close_fd(stdin_pipe[1]);
        close_fd(stdout_pipe[0]);
        close_fd(stdout_pipe[1]);
        close_fd(stderr_pipe[0]);
        close_fd(stderr_pipe[1]);
        throw std::runtime_error("failed to fork process");
    }

    if (pid == 0) {
        std::vector<char *> argv;

        dup2(stdin_pipe[0], STDIN_FILENO);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stderr_pipe[1], STDERR_FILENO);

        close_fd(stdin_pipe[0]);
        close_fd(stdin_pipe[1]);
        close_fd(stdout_pipe[0]);
        close_fd(stdout_pipe[1]);
        close_fd(stderr_pipe[0]);
        close_fd(stderr_pipe[1]);

        argv.push_back(const_cast<char *>(path.c_str()));
        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
            argv.push_back(const_cast<char *>(it->c_str()));
        }
        argv.push_back(0);

        execv(path.c_str(), argv.data());

        const std::string message = "execv failed: " + std::string(std::strerror(errno)) + "\n";
        write(STDERR_FILENO, message.c_str(), message.size());
        _exit(127);
    }

    close_fd(stdin_pipe[0]);
    close_fd(stdout_pipe[1]);
    close_fd(stderr_pipe[1]);

    if (!stdin_data.empty()) {
        const char *buffer = stdin_data.c_str();
        std::size_t total_written = 0;
        while (total_written < stdin_data.size()) {
            ssize_t bytes_written = write(stdin_pipe[1], buffer + total_written,
                                          stdin_data.size() - total_written);
            if (bytes_written < 0) {
                break;
            }
            total_written += static_cast<std::size_t>(bytes_written);
        }
    }
    close_fd(stdin_pipe[1]);

    ProcessResult result;
    result.stdout_output = read_all(stdout_pipe[0]);
    result.stderr_output = read_all(stderr_pipe[0]);

    close_fd(stdout_pipe[0]);
    close_fd(stderr_pipe[0]);

    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        result.exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        result.exit_code = 128 + WTERMSIG(status);
    } else {
        result.exit_code = -1;
    }

    return result;
}

}  // namespace test_support
