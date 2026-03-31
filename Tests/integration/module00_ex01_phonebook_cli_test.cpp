#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/fixture_loader.hpp"
#include "support/process_runner.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(PhoneBookCliIntegrationTest, AddSearchAndExitFlowPrintsStoredContact) {
    const test_support::ProcessResult result = test_support::run_process(
        MODULE00_EX01_APP_PATH,
        std::vector<std::string>(),
        test_support::load_fixture("module00_ex01_add_search_exit.txt"));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "Enter command (ADD, SEARCH, EXIT): ");
    expect_contains(result.stdout_output, "First name: ");
    expect_contains(result.stdout_output, "Index");
    expect_contains(result.stdout_output, "Ada");
    expect_contains(result.stdout_output, "First name: Ada");
    expect_contains(result.stdout_output, "Darkest secret: Math secret");
}

TEST(PhoneBookCliIntegrationTest, SearchOnEmptyPhoneBookExplainsState) {
    const test_support::ProcessResult result = test_support::run_process(
        MODULE00_EX01_APP_PATH,
        std::vector<std::string>(),
        test_support::load_fixture("module00_ex01_empty_search.txt"));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "PhoneBook is empty.");
}

TEST(PhoneBookCliIntegrationTest, InvalidIndexIsRejected) {
    const test_support::ProcessResult result = test_support::run_process(
        MODULE00_EX01_APP_PATH,
        std::vector<std::string>(),
        test_support::load_fixture("module00_ex01_invalid_index.txt"));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "Invalid index.");
}
