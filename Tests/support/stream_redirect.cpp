#include "support/stream_redirect.hpp"

#include <istream>
#include <ostream>

namespace test_support {

scoped_input_redirect::scoped_input_redirect(std::istream &stream, const std::string &content)
    : stream_(stream), buffer_(content), original_(stream.rdbuf(buffer_.rdbuf())) {}

scoped_input_redirect::~scoped_input_redirect() { stream_.rdbuf(original_); }

scoped_output_capture::scoped_output_capture(std::ostream &stream)
    : stream_(stream), original_(stream.rdbuf(buffer_.rdbuf())) {}

scoped_output_capture::~scoped_output_capture() { stream_.rdbuf(original_); }

std::string scoped_output_capture::str() const { return buffer_.str(); }

}  // namespace test_support
