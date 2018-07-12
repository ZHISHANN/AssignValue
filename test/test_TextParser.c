#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <ctype.h>
#include "unity.h"
#include "Error.h"
#include "TextParser.h"
#include "Exception.h"
#include "CException.h"

void setUp(void) {}

void tearDown(void) {}

void test_parseAndCompare_given_assign_with_spaces_and_assign_expect_return_true(void)
{
  char *line = "    assign  melon = 4";

  TEST_ASSERT_TRUE(parseAndCompare(&line,"assign"));
}

void test_compare_mango_return_true(void)
{
  char *line = "mango";

  TEST_ASSERT_TRUE(parseAndCompare(&line,"mango"));
}

void test_compare_space_mANgo_return_true(void)
{
  char *line = "   mANgo";

  TEST_ASSERT_TRUE(parseAndCompare(&line,"mANgo"));
}

void test_compare_mANgo_space_return_true(void)
{
  char *line = "mANgo    ";

  TEST_ASSERT_TRUE(parseAndCompare(&line,"mANgo"));
}

void test_compare_happy_return_false(void)
{
  char *line = "happy";

  TEST_ASSERT_FALSE(parseAndCompare(&line,"mANgo"));
}

void test_parseAndCompare_given_assign_with_extra_trailing_space_should_return_true(void)
{
  char *line ="assign";
  char *originalLine = line;

  TEST_ASSERT_TRUE (parseAndCompare(&line,"assign"));
  TEST_ASSERT_EQUAL_PTR (originalLine + 6, line);
}

void test_parseAndCompare_given_assign_with_should_return_false(void)
{
  char *line = "assn";
  char *originalLine = line;

  TEST_ASSERT_FALSE (parseAndCompare(&line,"assign"));
  TEST_ASSERT_EQUAL_PTR (originalLine, line);
}

void test_parseAndConvertToNum_given_string_456_with_trailing_space_expect_return_number_456 (void){
  char *line = " 456 ";
  char *originalLine = line;

  int v = parseAndConvertToNum (&line);
  TEST_ASSERT_EQUAL (456,v);
  TEST_ASSERT_EQUAL_PTR (originalLine + 5, line);
}

void test_parseAndConvertToNum_given_string_grape_with_trailing_space_expect_return_number_456 (void){
  char *line = " grape ";
  char *originalLine = line;

  TEST_ASSERT_FALSE (parseAndConvertToNum (&line));
}

// assign orange  = 21346 apple = 1 lemon=10
/*void test_parseTextAndAssignValues_given_orange_21346_apple_1_lemon_10_should_assigned_correctly(void) {
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"apple", &apple},
    {"orange", &orange},
    {"lemon", &lemon},
    {NULL, NULL},
  };
  char *line = "assign orange  = 21346 apple = 1 lemon=10";

  Try {
    parseTextAndAssignValues(line, varTableMapping);

    TEST_ASSERT_EQUAL(21346, orange);
    TEST_ASSERT_EQUAL(1, apple);
    TEST_ASSERT_EQUAL(10, lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_table_mapping_should_throw_ERR_TABLE_IS_MISSING(void)
{
  CEXCEPTION_T e;
  char *line = " assign mango = 589 ";

  Try {
    parseTextAndAssignValues(line, NULL);
    TEST_FAIL_MESSAGE("Expect ERR_TABLE_IS_MISSING. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_command_should_do_nothing(void) {
  CEXCEPTION_T e;
  int tomato = 0;
  VariableMapping varTableMapping[] = {
    {"tomato", &tomato},
    {NULL, NULL},
  };
  char *line = NULL;

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_input_command_is_NULL_should_do_nothing(void) {
  CEXCEPTION_T e;
  int kiwi = 0;
  VariableMapping varTableMapping[] = {
    {"kiwi", &kiwi},
    {NULL, NULL},
  };
  char *line = "  ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}*/

void test_parseTextAndAssignValues_given_melon_and_value_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon", &melon},
    {NULL, NULL},
  };
  char *line = "assignmelon=89";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_melon_and_value_with_space_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon", &melon},
    {NULL, NULL},
  };
  char *line = "assign melon = 89";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

/*void test_parseTextAndAssignValues_given_text_without_assign_should_throw_ERR_UNKNOWN_COMMAND(void) {
  CEXCEPTION_T e;
  int papaya = 0;
  VariableMapping varTableMapping[] = {
    {"papaya", &papaya},
    {NULL, NULL},
  };
  char *line = "  papaya = 345 ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_COMMAND. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_COMMAND, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_guava_23_cucumber_92_should_throw_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int guava = 0;
  VariableMapping varTableMapping[] = {
    {"guava", &guava},
    {NULL, NULL},
  };
  char *line = "assign guava=23 cucumber=92";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    TEST_ASSERT_EQUAL(23, guava);
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_pineapple_without_equal_sign_should_throw_ERR_MALFORM_ASSIGN(void) {
  CEXCEPTION_T e;
  int pineapple = 0;
  VariableMapping varTableMapping[] = {
    {"pineapple", &pineapple},
    {NULL, NULL},
  };
  char *line = "assign pineapple 23 ";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORM_ASSIGN. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_MALFORM_ASSIGN, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_ciku_without_number_should_throw_ERR_NOT_A_NUMBER(void) {
  CEXCEPTION_T e;
  int ciku = 0;
  VariableMapping varTableMapping[] = {
    {"ciku", &ciku},
    {NULL, NULL},
  };
  char *line = "assign ciku =  durian = 6";

  Try {
    parseTextAndAssignValues(line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}*/
