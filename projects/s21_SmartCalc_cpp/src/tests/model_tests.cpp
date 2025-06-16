#include <gtest/gtest.h>

#include "../sources/Controller/headers/controller.h"
#include "../sources/Model/headers/backend.h"
using namespace std;

// Точность сравнения значений
const double epsilon = 0.0000001;

TEST(ControllerTests, t) {
  std::string input = "2+3";
  std::string expected_output = "5";
  //  cout << s21::MVC_Controller::FromViewToModelTransceiver(input) << "\n";
  EXPECT_EQ(s21::MVC_Controller::FromViewToModelTransceiver(input),
            expected_output);
}

TEST(ModelTests, Addition_PositiveNumbers) {
  std::string input = "2+3";
  std::string expected_output = "5";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Subtraction_NegativeNumbers) {
  std::string input = "-5-(-10)";
  std::string expected_output = "5";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Multiplication_PositiveDecimals) {
  std::string input = "0.1*0.2";
  std::string expected_output = "0.02";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Division_PositiveIntegers) {
  std::string input = "10/5";
  std::string expected_output = "2";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_PositiveExponent) {
  std::string input = "2^8";
  std::string expected_output = "256";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_NegativeExponent) {
  std::string input = "2^-4";
  std::string expected_output = "0.0625";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Multiplication_ByZero) {
  std::string input = "5*0";
  std::string expected_output = "0";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Addition_DecimalAndInteger) {
  std::string input = "2.5+3";
  std::string expected_output = "5.5";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Subtraction_DecimalAndInteger) {
  std::string input = "5-2.5";
  std::string expected_output = "2.5";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Subtraction_NegativeDecimalAndPositiveInteger) {
  std::string input = "3-(-0.5)";
  std::string expected_output = "3.5";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Multiplication_NegativeDecimalAndPositiveInteger) {
  std::string input = "-0.5*4";
  std::string expected_output = "-2";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Division_NegativeDecimalAndPositiveInteger) {
  std::string input = "-1/4";
  std::string expected_output = "-0.25";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_ZeroExponent) {
  std::string input = "2^0";
  std::string expected_output = "1";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Division_PositiveIntegerByNegativeInteger) {
  std::string input = "10/-3";
  std::string expected_output = "-3.3333333";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_NegativeBaseEvenExponent) {
  std::string input = "-2^4";
  std::string expected_output = "16";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_NegativeBaseOddExponent) {
  std::string input = "-2^3";
  std::string expected_output = "-8";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_ZeroNegativeExponent) {
  std::string input = "0^-3";
  std::string expected_output = "inf";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

TEST(ModelTests, Power_ZeroPositiveExponent) {
  std::string input = "0^5";
  std::string expected_output = "0";
  EXPECT_EQ(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
            expected_output);
}

// Тестирование функции acos с положительным аргументом
TEST(CalculatorBackendTests, Acos_PositiveArgument) {
  std::string input = "acos(0.5)";
  std::string expected_output = "1.0471976";
  EXPECT_NEAR(
      std::stod(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input)),
      std::stod(expected_output), epsilon);
}

// Тестирование функции cos с отрицательным аргументом
TEST(CalculatorBackendTests, Cosine_NegativeArgument) {
  std::string input = "cos(-2.3)";
  std::string expected_output = "-0.66627602127982419332";
  EXPECT_NEAR(
      std::stod(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input)),
      std::stod(expected_output), epsilon);
}

// Тестирование функции asin с аргументом больше единицы
TEST(CalculatorBackendTests, Asine_ArgumentGreaterThanOne) {
  std::string input = "asin(1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

// Тестирование функции sin с отрицательным аргументом
TEST(CalculatorBackendTests, Sine_NegativeArgument) {
  std::string input = "sin(-0.7)";
  std::string expected_output = "-0.64421768723769105367";
  EXPECT_NEAR(
      std::stod(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input)),
      std::stod(expected_output), epsilon);
}

// Тестирование функции atan с положительным аргументом
TEST(CalculatorBackendTests, Atan_PositiveArgument) {
  std::string input = "atan(2.4)";
  std::string expected_output = "1.17600520709513510249";
  EXPECT_NEAR(
      std::stod(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input)),
      std::stod(expected_output), epsilon);
}

TEST(CalculatorBackendTests, Acos_InvalidArgument) {
  std::string input = "acos(1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Asin_ArgumentGreaterThanOne) {
  std::string input = "asin(1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Asin_ArgumentLessThanMinusOne) {
  std::string input = "asin(-1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Atan_InvalidArgument) {
  std::string input = "atan(inf)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Tan_InvalidArgument) {
  std::string input = "tan(PI/2)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Sqrt_NegativeArgument) {
  std::string input = "sqrt(-1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Log_LessThanZero) {
  std::string input = "log(-1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

TEST(CalculatorBackendTests, Ln_LessThanZero) {
  std::string input = "ln(-1.5)";
  EXPECT_THROW(s21::UltraCalculatorsBackEnd::UltraCalculatorsAPI(input),
               std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
