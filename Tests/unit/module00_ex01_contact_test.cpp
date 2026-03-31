#include <gtest/gtest.h>

#include <iostream>

#include "Contact.hpp"
#include "support/stream_redirect.hpp"

namespace {

Contact make_contact() {
    Contact contact;

    contact.setFirstName("Ada");
    contact.setLastName("Lovelace");
    contact.setNickname("Enchantress");
    contact.setPhoneNumber("123456");
    contact.setDarkestSecret("Analytical engine fan");
    return contact;
}

}  // namespace

TEST(ContactTest, SettersAndGettersRoundTripValues) {
    Contact contact = make_contact();

    EXPECT_EQ(contact.getFirstName(), "Ada");
    EXPECT_EQ(contact.getLastName(), "Lovelace");
    EXPECT_EQ(contact.getNickname(), "Enchantress");
    EXPECT_EQ(contact.getPhoneNumber(), "123456");
    EXPECT_EQ(contact.getDarkestSecret(), "Analytical engine fan");
}

TEST(ContactTest, CopyOperationsPreserveAllFields) {
    Contact original = make_contact();
    Contact copied(original);
    Contact assigned;

    assigned = original;

    EXPECT_EQ(copied.getFirstName(), original.getFirstName());
    EXPECT_EQ(copied.getLastName(), original.getLastName());
    EXPECT_EQ(copied.getNickname(), original.getNickname());
    EXPECT_EQ(copied.getPhoneNumber(), original.getPhoneNumber());
    EXPECT_EQ(copied.getDarkestSecret(), original.getDarkestSecret());

    EXPECT_EQ(assigned.getFirstName(), original.getFirstName());
    EXPECT_EQ(assigned.getLastName(), original.getLastName());
    EXPECT_EQ(assigned.getNickname(), original.getNickname());
    EXPECT_EQ(assigned.getPhoneNumber(), original.getPhoneNumber());
    EXPECT_EQ(assigned.getDarkestSecret(), original.getDarkestSecret());
}

TEST(ContactTest, DisplayPrintsAllStoredFields) {
    Contact contact = make_contact();
    test_support::scoped_output_capture capture(std::cout);

    contact.display();

    const std::string output = capture.str();
    EXPECT_NE(output.find("First name: Ada"), std::string::npos);
    EXPECT_NE(output.find("Last name: Lovelace"), std::string::npos);
    EXPECT_NE(output.find("Nickname: Enchantress"), std::string::npos);
    EXPECT_NE(output.find("Phone number: 123456"), std::string::npos);
    EXPECT_NE(output.find("Darkest secret: Analytical engine fan"), std::string::npos);
}
