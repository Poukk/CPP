#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

#include "PhoneBook.hpp"
#include "support/stream_redirect.hpp"

namespace {

std::string make_contact_script(const std::string &first_name,
                                const std::string &last_name,
                                const std::string &nickname,
                                const std::string &phone_number,
                                const std::string &darkest_secret) {
    std::ostringstream script;

    script << first_name << '\n'
           << last_name << '\n'
           << nickname << '\n'
           << phone_number << '\n'
           << darkest_secret << '\n';
    return script.str();
}

bool add_contact(PhoneBook &phone_book,
                 const std::string &first_name,
                 const std::string &last_name,
                 const std::string &nickname,
                 const std::string &phone_number,
                 const std::string &darkest_secret,
                 std::string *output = 0) {
    test_support::scoped_input_redirect input(
        std::cin, make_contact_script(first_name, last_name, nickname, phone_number, darkest_secret));
    test_support::scoped_output_capture capture(std::cout);
    const bool result = phone_book.addContact();

    if (output != 0) {
        *output = capture.str();
    }
    return result;
}

}  // namespace

TEST(PhoneBookStorageTest, StartsEmpty) {
    PhoneBook phone_book;

    EXPECT_EQ(phone_book.getContactCount(), 0);
    EXPECT_EQ(phone_book.getMaxContacts(), 8);
    EXPECT_EQ(phone_book.getContact(-1), static_cast<const Contact *>(0));
    EXPECT_EQ(phone_book.getContact(0), static_cast<const Contact *>(0));
}

TEST(PhoneBookStorageTest, AddContactStoresDataInInsertionOrder) {
    PhoneBook phone_book;

    ASSERT_TRUE(add_contact(phone_book, "Ada", "Lovelace", "Enchantress", "111", "Math"));
    ASSERT_TRUE(add_contact(phone_book, "Alan", "Turing", "Ace", "222", "Machines"));

    ASSERT_EQ(phone_book.getContactCount(), 2);
    ASSERT_NE(phone_book.getContact(0), static_cast<const Contact *>(0));
    ASSERT_NE(phone_book.getContact(1), static_cast<const Contact *>(0));
    EXPECT_EQ(phone_book.getContact(0)->getFirstName(), "Ada");
    EXPECT_EQ(phone_book.getContact(1)->getFirstName(), "Alan");
}

TEST(PhoneBookStorageTest, AddContactRetriesEmptyFieldsUntilValidInput) {
    PhoneBook phone_book;
    std::string output;
    test_support::scoped_input_redirect input(
        std::cin,
        "\nAda\n\nLovelace\n\nEnchantress\n\n123456\n\nMath secret\n");
    test_support::scoped_output_capture capture(std::cout);

    ASSERT_TRUE(phone_book.addContact());
    output = capture.str();

    EXPECT_EQ(phone_book.getContactCount(), 1);
    EXPECT_NE(output.find("Field cannot be empty."), std::string::npos);
    EXPECT_EQ(phone_book.getContact(0)->getFirstName(), "Ada");
    EXPECT_EQ(phone_book.getContact(0)->getLastName(), "Lovelace");
}

TEST(PhoneBookStorageTest, CircularOverwriteKeepsMostRecentEightContacts) {
    PhoneBook phone_book;

    for (int index = 0; index < 9; ++index) {
        std::ostringstream value;
        value << index;
        ASSERT_TRUE(add_contact(phone_book,
                                "First" + value.str(),
                                "Last" + value.str(),
                                "Nick" + value.str(),
                                "Phone" + value.str(),
                                "Secret" + value.str()));
    }

    ASSERT_EQ(phone_book.getContactCount(), 8);
    EXPECT_EQ(phone_book.getContact(0)->getFirstName(), "First1");
    EXPECT_EQ(phone_book.getContact(7)->getFirstName(), "First8");
}

TEST(PhoneBookStorageTest, SearchReportsEmptyPhoneBook) {
    PhoneBook phone_book;
    test_support::scoped_input_redirect input(std::cin, "");
    test_support::scoped_output_capture capture(std::cout);

    EXPECT_TRUE(phone_book.searchContact());
    EXPECT_NE(capture.str().find("PhoneBook is empty."), std::string::npos);
}

TEST(PhoneBookStorageTest, SearchRejectsInvalidIndex) {
    PhoneBook phone_book;

    ASSERT_TRUE(add_contact(phone_book, "Ada", "Lovelace", "Enchantress", "111", "Math"));

    test_support::scoped_input_redirect input(std::cin, "9\n");
    test_support::scoped_output_capture capture(std::cout);

    EXPECT_TRUE(phone_book.searchContact());
    EXPECT_NE(capture.str().find("Invalid index."), std::string::npos);
}
