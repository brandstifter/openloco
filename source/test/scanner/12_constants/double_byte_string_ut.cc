#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "lang/test/scanner/abstract_ut.h"

using parser = openloco::lang::parser;

class double_type_string_test : public abstract_scanner_ut { };

TEST_F(double_type_string_test, match_empty_string) {
    input << "\"\"";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_STREQ("", result.value.as<std::string>().c_str());
}

TEST_F(double_type_string_test, match_string) {
    input << "\"string\"";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_STREQ("string", result.value.as<std::string>().c_str());
}

TEST_F(double_type_string_test, dont_match_single_byte_string) {
    input << "'string'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_NE(parser::token::DOUBLE_BYTE_CHARACTER_STRING, result.token());
}