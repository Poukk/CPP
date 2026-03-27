#ifndef HARL_HPP
#define HARL_HPP

#define HARL_DEBUG   "[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
#define HARL_INFO    "[INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"
#define HARL_WARNING "[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."
#define HARL_ERROR   "[ERROR] This is unacceptable! I want to speak to the manager now."

#include <string>

class Harl {
  private:
    typedef void (Harl::*HarlAction)(void);

    void debug(void);
    void info(void);
    void warning(void);
    void error(void);

  public:
    Harl();
    ~Harl();

    void complain(std::string level);
};

#endif
