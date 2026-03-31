#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "FileReplacer.hpp"
#include "support/stream_redirect.hpp"
#include "support/temp_dir.hpp"

TEST(Module01Ex04FileReplacerTest, ProcessCreatesReplaceFileWithUpdatedContent) {
    test_support::scoped_temp_dir temp_dir;
    const std::string input_name = "input.txt";
    const std::string input_path = temp_dir.file_path(input_name);
    FileReplacer replacer(input_path, "fish", "cat");

    temp_dir.write_file(input_name, "one fish two fish red fish blue fish\n");

    ASSERT_TRUE(replacer.process());
    EXPECT_EQ(temp_dir.read_file(input_name + ".replace"),
              "one cat two cat red cat blue cat\n");
}

TEST(Module01Ex04FileReplacerTest, ProcessRejectsEmptySearchString) {
    test_support::scoped_temp_dir temp_dir;
    const std::string input_name = "input.txt";
    const std::string input_path = temp_dir.file_path(input_name);
    FileReplacer replacer(input_path, "", "cat");
    test_support::scoped_output_capture capture(std::cerr);

    temp_dir.write_file(input_name, "content\n");

    EXPECT_FALSE(replacer.process());
    EXPECT_EQ(capture.str(), "Error: s1 must not be empty.\n");
}

TEST(Module01Ex04FileReplacerTest, ProcessRejectsMissingInputFile) {
    test_support::scoped_temp_dir temp_dir;
    FileReplacer replacer(temp_dir.file_path("missing.txt"), "fish", "cat");
    test_support::scoped_output_capture capture(std::cerr);

    EXPECT_FALSE(replacer.process());
    EXPECT_EQ(capture.str(), "Error: could not open input file.\n");
}
