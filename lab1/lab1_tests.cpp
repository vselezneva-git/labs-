#include <gtest/gtest.h>
#include "BitArray.h"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray b(6);
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.to_string(), "000000");
}
TEST(BitArrayTest, ParamConstructor) {
    BitArray b(10, 7); 
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(b.to_string(), "0000000111");
}

TEST(BitArrayTest, ParamConstructorWithNegativeSize) {
    EXPECT_THROW(BitArray(-1), std::invalid_argument);
}

TEST(BitArrayTest, CopeConstructor) {
    BitArray b1(12, 8);
    BitArray b2(b1);
    EXPECT_EQ(b2.size(), 12);
    EXPECT_EQ(b2.to_string(), "000000001000");
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray b1(8, 3);
    BitArray b2;
    b2 = b1;
    EXPECT_EQ(b2.size(), 8);
    EXPECT_EQ(b2.to_string(), "00000011");
}

TEST(BitArrayTest, Swap) {
    BitArray b1(10, 6);
    BitArray b2(10, 8);
    b1.Swap(b2);
    EXPECT_EQ(b1.to_string(), "0000001000");
    EXPECT_EQ(b2.to_string(), "0000000110");
}

TEST(BitArrayTest, ResizeGreaterTrue) {
    BitArray b1(10, 6); 
    b1.Resize(13, true); 
    EXPECT_EQ(b1.to_string(), "1110000000110");
    EXPECT_EQ(b1.size(), 13);
}

TEST(BitArrayTest, ResizeGreaterFalse) {
    BitArray b1(10, 6); 
    b1.Resize(15); 
    EXPECT_EQ(b1.to_string(), "000000000000110");
    EXPECT_EQ(b1.size(), 15);
}

TEST(BitArrayTest, ResizeLess) {
    BitArray b1(23, 6); 
    b1.Resize(5); 
    EXPECT_EQ(b1.to_string(), "00110");
    EXPECT_EQ(b1.size(), 5);
}

TEST(BitArrayTest, Clear) {
    BitArray b(15, 9);
    b.clear();
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayTest, PushBackTrue) {
    BitArray b1(8, 2); 
    b1.push_back(1);
    b1.push_back(1);
    b1.push_back(1);
    EXPECT_EQ(b1.to_string(), "11100000010");
    EXPECT_EQ(b1.size(), 11);
}

TEST(BitArrayTest, PushBackFalse) {
    BitArray b1(5, 7); 
    b1.push_back(0);
    b1.push_back(0);
    EXPECT_EQ(b1.to_string(), "0000111");
    EXPECT_EQ(b1.size(), 7);
}


TEST(BitArrayTest, BitwiseAndEqual) {
    BitArray b1(6, 7); 
    BitArray b2(6, 11);
    b1 &= b2;
    EXPECT_EQ(b1.to_string(), "000011");
}

TEST(BitArrayTest, BitwiseAndEqualWithError) {
    BitArray b1(26, 33); 
    BitArray b2(50, 27);
    EXPECT_THROW(b1 &= b2, std::invalid_argument);
}

TEST(BitArrayTest, BitwiseOrEqual) {
    BitArray b1(10, 24);
    BitArray b2(10, 37); 
    b1 |= b2;
    EXPECT_EQ(b1.to_string(), "0000111101");
}

TEST(BitArrayTest, BitwiseOrEqualWithError) {
    BitArray b1(13, 1); 
    BitArray b2(7, 7);
    EXPECT_THROW(b1 |= b2, std::invalid_argument);
}

TEST(BitArrayTest, BitwiseXorEqual) {
    BitArray b1(4, 9); 
    BitArray b2(4, 6); 
    b1 ^= b2;
    EXPECT_EQ(b1.to_string(), "1111");
}

TEST(BitArrayTest, BitwiseXorEqualWithError) {
    BitArray b1(1); 
    BitArray b2(5, 3);
    EXPECT_THROW(b1 ^= b2, std::invalid_argument);
}

TEST(BitArrayTest, ShiftRightEqual) {
    BitArray b1(7, 14);
    b1 >>= 3; 
    EXPECT_EQ(b1.to_string(), "0000001");
    EXPECT_EQ(b1.size(), 7);
}

TEST(BitArrayTest, ShiftRightEqualWithNegShift) {
    BitArray b1(9, 8); 
    EXPECT_THROW(b1 >>= -3, std::invalid_argument);
}

TEST(BitArrayTest, ShiftLeftEqual) {
    BitArray b1(7, 1);
    b1 <<= 3; 
    EXPECT_EQ(b1.to_string(), "0001000");
    EXPECT_EQ(b1.size(), 7);
}

TEST(BitArrayTest, ShiftLeftEqualWithNegShift) {
    BitArray b1(10, 11); 
    EXPECT_THROW(b1 <<= -3, std::invalid_argument);
}

TEST(BitArrayTest, ShiftLeft) {
    BitArray b1(4, 9); 
    BitArray result = b1 << 2;
    EXPECT_EQ(result.to_string(), "0100");
}

TEST(BitArrayTest, ShiftRight) {
    BitArray b1(5, 3); 
    BitArray result = b1 >> 2;
    EXPECT_EQ(result.to_string(), "00000");
}

TEST(BitArrayTest, SetValueTrue) {
    BitArray b1(4, 2); //0010
    b1.Set(3, 1);
    EXPECT_EQ(b1.to_string(), "1010");
}

TEST(BitArrayTest, SetValueFalse) {
    BitArray b1(4, 1); //0001
    b1.Set(0, 0);
    EXPECT_EQ(b1.to_string(), "0000");
}

TEST(BitArrayTest, SetValueWithNegIndex) {
    BitArray b1(10, 11); 
    EXPECT_THROW(b1.Set(-1, 0), std::invalid_argument);
}

TEST(BitArrayTest, SetOutOfRange) {
    BitArray b1(12, 15); 
    EXPECT_THROW(b1.Set(20, 1), std::out_of_range);
}

TEST(BitArrayTest, SetTrue) {
    BitArray b1(9, 12); 
    b1.Set();
    EXPECT_EQ(b1.to_string(), "111111111");
}

TEST(BitArrayTest, Reset) {
    BitArray b1(9, 12); 
    b1.Reset(2);
    EXPECT_EQ(b1.to_string(), "000001000");
}

TEST(BitArrayTest, ResetOutOfRange) {
    BitArray b1(6, 4); 
    EXPECT_THROW(b1.Reset(15), std::out_of_range);
}

TEST(BitArrayTest, ResetAllFalse) {
    BitArray b1(7, 17); 
    b1.Reset();
    EXPECT_EQ(b1.to_string(), "0000000");
}

TEST(BitArrayTest, Any) {
    BitArray b1(4, 0);
    EXPECT_FALSE(b1.any());
    b1.Set(0, true); 
    EXPECT_TRUE(b1.any());
}

TEST(BitArrayTest, None) {
    BitArray b1(6, 0);
    EXPECT_TRUE(b1.none());
    b1.Set(4, true); 
    EXPECT_FALSE(b1.none());
}

TEST(BitArrayTest, BitwiseNot) {
    BitArray b1(4, 9); 
    BitArray b1_not = ~b1;
    EXPECT_EQ(b1_not.to_string(), "0110");
}

TEST(BitArrayTest, Count) {
    BitArray b1(5, 20); 
    EXPECT_EQ(b1.count(), 2);
}

TEST(BitArrayTest, BracketOperator) {
    BitArray b1(4, 5); 
    EXPECT_TRUE(b1[0]);
    EXPECT_FALSE(b1[1]);
    EXPECT_TRUE(b1[2]);
    EXPECT_FALSE(b1[3]);
}

TEST(BitArrayTest, BracketOperatorOutOfRange) {
    BitArray b1(9, 21); 
    EXPECT_THROW(b1[40], std::out_of_range);
}

TEST(BitArrayTest, BracketOperatorNegativeInd) {
    BitArray b1(4, 2); 
    EXPECT_THROW(b1[-3], std::invalid_argument);
}

TEST(BitArrayTest, Size) {
    BitArray b1(5, 18); 
    EXPECT_EQ(b1.size(), 5);
}

TEST(BitArrayTest, Empty) {
    BitArray b1(2, 1);
    b1.clear();
    EXPECT_TRUE(b1.empty());
    b1.Resize(4);
    EXPECT_FALSE(b1.empty());
}

TEST(BitArrayTest, ToString) {
    BitArray b1(8); 
    EXPECT_EQ(b1.to_string(), "00000000");
}

TEST(BitArrayTest, EqualityOperator) {
    BitArray b1(7, 13); 
    BitArray b2(7, 13); 
    BitArray b3(5, 8); 
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
}

TEST(BitArrayTest, NotEqualityOperator) {
    BitArray b1(7, 13); 
    BitArray b2(7, 13); 
    BitArray b3(5, 8); 
    EXPECT_TRUE(b1 != b3);
    EXPECT_FALSE(b1 != b2);
}

TEST(BitArrayTest, BitwiseAnd) {
    BitArray b1(4, 9); 
    BitArray b2(4, 6); 
    BitArray b_and = b1 & b2;
    EXPECT_EQ(b_and.to_string(), "0000");
}

TEST(BitArrayTest, BitwiseOr) {
    BitArray b1(4, 9); 
    BitArray b2(4, 6); 
    BitArray b_or = b1 | b2;
    EXPECT_EQ(b_or.to_string(), "1111");
}

TEST(BitArrayTest, BitwiseXor) {
    BitArray b1(4, 9); 
    BitArray b2(4, 6); 
    BitArray b_xor = b1 ^ b2;
    EXPECT_EQ(b_xor.to_string(), "1111");
}








