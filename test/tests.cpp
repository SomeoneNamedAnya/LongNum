#include <gtest/gtest.h>
#include <exception>
#include <string>
#include "longnum.h"
using namespace LongNumLib;

TEST(AdditionOperationTest, PositiveNumbers) {
  LongNum first, second, ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = 30.01_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();

  first = 105.0005_LN;
  second = 15.005_LN;
  ans = 120.0055_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
 
  first = 25.5_LN;
  second = 15.535_LN;
  ans = 41.035_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
 
}

TEST(AdditionOperationTest, NegativeNumbers) {
  LongNum first, second, ans;
  first = -15.005_LN;
  second = -15.005_LN;
  ans = -30.01_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();

  first = -105.0005_LN;
  second = -15.005_LN;
  ans = -120.0055_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
  
  first = -25.5_LN;
  second = -15.535_LN;
  ans = -41.035_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
}

TEST(AdditionOperationTest, DifSignNumbers) {
  LongNum first, second, ans;
  first = -15.005_LN;
  second = 15.005_LN;
  ans = 0_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();

  first = 105.0005_LN;
  second = -15.005_LN;
  ans = 89.9955_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
 
  first = -25.5_LN;
  second = 15.535_LN;
  ans = -9.965_LN;
  EXPECT_EQ((first + second).GetLongNum(), ans.GetLongNum()) << (first + second).GetLongNum();
}

TEST(DifferenceOperationTest, PositiveNumbers) {
  LongNum first, second, ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = 0_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();

  first = 105.0005_LN;
  second = 15.005_LN;
  ans = 89.9955_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
  first = 25.5_LN;
  second = 15.535_LN;
  ans = 9.965_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
}

TEST(DifferenceOperationTest, NegativeNumbers) {
  LongNum first, second, ans;
  first = -15.005_LN;
  second = -15.005_LN;
  ans = 0_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();

  first = -105.0005_LN;
  second = -15.005_LN;
  ans = -89.9955_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
  first = -25.5_LN;
  second = -15.535_LN;
  ans = -9.965_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
}

TEST(DifferenceOperationTest, DifSignNumbers) {
  LongNum first, second, ans;
  first = -15.005_LN;
  second = 15.005_LN;
  ans = -30.01_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();

  first = 105.0005_LN;
  second = -15.005_LN;
  ans = 120.0055_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
  first = -25.5_LN;
  second = 15.535_LN;
  ans = -41.035_LN;
  EXPECT_EQ((first - second).GetLongNum(), ans.GetLongNum()) << (first - second).GetLongNum();
 
}

TEST(MulOperationTest, Numbers) {
  LongNum first, second, ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = 225.150025_LN;
  EXPECT_EQ((first * second).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();

  first = 105.0005_LN;
  second = 0_LN;
  ans = 0_LN;
  EXPECT_EQ((first * second).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();
 
  first = 0_LN;
  second = 15.535_LN;
  ans = 0_LN;
  EXPECT_EQ((first * second).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();

  first = -15.005_LN;
  second = 100.005_LN;
  ans = -1500.575025_LN;
  EXPECT_EQ((first * second).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();

  first = -15.005_LN;
  second = -100.005_LN;
  ans = 1500.575025_LN;
  EXPECT_EQ((first * second).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();

}

TEST(DivOperationTest, Numbers) {
  LongNum first, second, ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = 1_LN;
  EXPECT_EQ((first / second).GetLongNum(), ans.GetLongNum()) << (first / second).GetLongNum();

  first = 105.0005_LN;
  second = 0_LN;
  ans = 0_LN;
  EXPECT_ANY_THROW(first / second) << (first / second).GetLongNum();
 
  first = 0_LN;
  second = 15.535_LN;
  ans = 0_LN;
  EXPECT_EQ((first / second).GetLongNum(), ans.GetLongNum()) << (first / second).GetLongNum();
  
  first = -15.005_LN;
  second = 100.005_LN;
  ans = -0.15_LN;
  EXPECT_EQ((first / second).GetLongNum(), ans.GetLongNum()) << (first / second).GetLongNum();

  first = -13_LN;
  second = -7.1_LN;
  ans = 1.83098_LN;
  EXPECT_EQ((first.Div(second, 5)).GetLongNum(), ans.GetLongNum()) << (first * second).GetLongNum();

}

TEST(MinusOperationTest, Numbers) {
  LongNum first;
  std::string ans;
  first = -15.005_LN;
  ans = "15.005";
  EXPECT_EQ((-first).GetLongNum(), ans) << (-first).GetLongNum();

  first = 15.005_LN;
  ans = "-15.005";
  EXPECT_EQ((-first).GetLongNum(), ans) << (-first).GetLongNum();

  first = 0_LN;
  ans = "0";
  EXPECT_EQ((-first).GetLongNum(), ans) << (-first).GetLongNum();

  first = -0_LN;
  ans = "0";
  EXPECT_EQ((-first).GetLongNum(), ans) << (-first).GetLongNum();

}

TEST(LogicOperationTest, Equals) {
  LongNum first, second;
  bool ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.0050001_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = -15.005_LN;
  ans = true;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = 15.00500001_LN;
  ans = false;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 0.000_LN;
  second = 0_LN;
  ans = true;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();


  first = 0.000_LN;
  second = -0_LN;
  ans = true;
  EXPECT_EQ(first == second, ans) << first.GetLongNum() << " " << second.GetLongNum();

}

TEST(LogicOperationTest, NotEquals) {
  LongNum first, second;
  bool ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.0050001_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = -15.005_LN;
  ans = false;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = 15.00500001_LN;
  ans = true;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 0.000_LN;
  second = 0_LN;
  ans = false;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 0.000_LN;
  second = -0_LN;
  ans = false;
  EXPECT_EQ(first != second, ans) << first.GetLongNum() << " " << second.GetLongNum();

}

TEST(LogicOperationTest, More) {
  LongNum first, second;
  bool ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 150.005_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = -15.005_LN;
  ans = true;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.00500001_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = 15.00500001_LN;
  ans = false;
  EXPECT_EQ(first > second, ans) << first.GetLongNum() << " " << second.GetLongNum();

}

TEST(LogicOperationTest, Less) {
  LongNum first, second;
  bool ans;
  first = 15.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 150.005_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = -15.005_LN;
  second = 15.005_LN;
  ans = true;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = -15.005_LN;
  ans = false;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.00500001_LN;
  second = 15.005_LN;
  ans = false;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

  first = 15.005_LN;
  second = 15.00500001_LN;
  ans = true;
  EXPECT_EQ(first < second, ans) << first.GetLongNum() << " " << second.GetLongNum();

}

TEST(PiCalculationTest, More) {
  LongNum first = PiCalculation(100);
  std::string ans = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
  EXPECT_EQ(first.GetLongNum(), ans) << first.GetLongNum() << " " << ans;

  first = PiCalculation(1);
  ans = "3.1";
  EXPECT_EQ(first.GetLongNum(), ans) << first.GetLongNum() << " " << ans;

  first = PiCalculation(0);
  ans = "3";
  EXPECT_EQ(first.GetLongNum(), ans) << first.GetLongNum() << " " << ans;

  EXPECT_ANY_THROW(PiCalculation(-1));
  
}
