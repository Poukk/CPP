#ifndef TESTS_SUPPORT_STREAM_REDIRECT_HPP
#define TESTS_SUPPORT_STREAM_REDIRECT_HPP

#include <iosfwd>
#include <sstream>
#include <string>

namespace test_support {

class scoped_input_redirect {
   public:
    scoped_input_redirect(std::istream &stream, const std::string &content);
    ~scoped_input_redirect();

   private:
    std::istream &stream_;
    std::istringstream buffer_;
    std::streambuf *original_;
};

class scoped_output_capture {
   public:
    explicit scoped_output_capture(std::ostream &stream);
    ~scoped_output_capture();

    std::string str() const;

   private:
    std::ostream &stream_;
    std::ostringstream buffer_;
    std::streambuf *original_;
};

}  // namespace test_support

#endif
