#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
   private:
    static const int maxContacts = 8;

    Contact contacts[maxContacts];
    int nextIndex;
    int contactCount;

   public:
    PhoneBook();
    PhoneBook(const PhoneBook &other);
    ~PhoneBook();
    PhoneBook &operator=(const PhoneBook &other);

    bool addContact();
    bool searchContact() const;
    const Contact *getContact(int index) const;
    int getContactCount() const;
    int getMaxContacts() const;
};

#endif
