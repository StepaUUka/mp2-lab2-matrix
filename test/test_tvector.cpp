#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(5);
	v1[0] = 4;
	v1[1] = 7;
	v1[2] = 9;
	v1[3] = 5;
	v1[4] = 0;
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i=0;i<size(v1);i++)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(5);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	v1[4] = 5;
	TDynamicVector<int> v2(v1);
	v1[0] = 100;
	v1[1] = 200;
	v1[2] = 300;
	v1[3] = 400;
	v1[4] = 500;
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(2, v2[1]);
	EXPECT_EQ(3, v2[2]);
	EXPECT_EQ(4, v2[3]);
	EXPECT_EQ(5, v2[4]);
	v2[0] = 876;
	EXPECT_EQ(100, v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-3));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(100));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v1(5);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	v1[4] = 5;
	v1 = v1;
	EXPECT_EQ(5, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(3, v1[2]);
	EXPECT_EQ(4, v1[3]);
	EXPECT_EQ(5, v1[4]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(4);
	v2[0] = 9;
	v2[1] = 8;
	v2[2] = 7;
	v2[3] = 6;
	v1 = v2;
	EXPECT_EQ(4, v1.size());
	EXPECT_EQ(9, v1[0]);
	EXPECT_EQ(8, v1[1]);
	EXPECT_EQ(7, v1[2]);
	EXPECT_EQ(6, v1[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(9, v2[0]);
	EXPECT_EQ(8, v2[1]);
	EXPECT_EQ(7, v2[2]);
	EXPECT_EQ(6, v2[3]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v3(v1);
	TDynamicVector<int> v2(5);
	v2[0] = 9;
	v2[1] = 8;
	v2[2] = 7;
	v2[3] = 6;
	v2[4] = 5;
	v1 = v2;
	EXPECT_EQ(5, v1.size());
	v2 = v3;
	EXPECT_EQ(4, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(5);
	v2[0] = 9;
	v2[1] = 8;
	v2[2] = 7;
	v2[3] = 6;
	v2[4] = 5;
	v1 = v2;
	EXPECT_EQ(5, v1.size());
	EXPECT_EQ(9, v1[0]);
	EXPECT_EQ(8, v1[1]);
	EXPECT_EQ(7, v1[2]);
	EXPECT_EQ(6, v1[3]);
	EXPECT_EQ(5, v1[4]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(4);
	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;
	v2[3] = 4;
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	EXPECT_TRUE(v1 == v1);
	v1[0] = 1000;
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(5);
	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;
	v2[3] = 4;
	v2[4] = 5;
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> result=v1+5;
	EXPECT_EQ(4, result.size());
	EXPECT_EQ(6, result[0]);
	EXPECT_EQ(7, result[1]);
	EXPECT_EQ(8, result[2]);
	EXPECT_EQ(9, result[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(2, v2[1]);
	EXPECT_EQ(3, v2[2]);
	EXPECT_EQ(4, v2[3]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> result = v1 - 5;
	EXPECT_EQ(4, result.size());
	EXPECT_EQ(-4, result[0]);
	EXPECT_EQ(-3, result[1]);
	EXPECT_EQ(-2, result[2]);
	EXPECT_EQ(-1, result[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(2, v2[1]);
	EXPECT_EQ(3, v2[2]);
	EXPECT_EQ(4, v2[3]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> result = v1 * 5;
	EXPECT_EQ(4, result.size());
	EXPECT_EQ(5, result[0]);
	EXPECT_EQ(10, result[1]);
	EXPECT_EQ(15, result[2]);
	EXPECT_EQ(20, result[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(2, v2[1]);
	EXPECT_EQ(3, v2[2]);
	EXPECT_EQ(4, v2[3]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(4);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	TDynamicVector<int> v3=v1+v2;
	EXPECT_EQ(4, v3.size());
	EXPECT_EQ(11, v3[0]);
	EXPECT_EQ(22, v3[1]);
	EXPECT_EQ(33, v3[2]);
	EXPECT_EQ(44, v3[3]);
	EXPECT_EQ(4, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(3, v1[2]);
	EXPECT_EQ(4, v1[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(10, v2[0]);
	EXPECT_EQ(20, v2[1]);
	EXPECT_EQ(30, v2[2]);
	EXPECT_EQ(40, v2[3]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(5);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	v2[4] = 50;
	ASSERT_ANY_THROW(TDynamicVector<int> v3=v1+v2);
	ASSERT_ANY_THROW(TDynamicVector<int> v3 = v2 + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(4);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	TDynamicVector<int> v3 = v1 - v2;
	EXPECT_EQ(4, v3.size());
	EXPECT_EQ(-9, v3[0]);
	EXPECT_EQ(-18, v3[1]);
	EXPECT_EQ(-27, v3[2]);
	EXPECT_EQ(-36, v3[3]);
	EXPECT_EQ(4, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(3, v1[2]);
	EXPECT_EQ(4, v1[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(10, v2[0]);
	EXPECT_EQ(20, v2[1]);
	EXPECT_EQ(30, v2[2]);
	EXPECT_EQ(40, v2[3]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(5);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	v2[4] = 50;
	ASSERT_ANY_THROW(TDynamicVector<int> v3 = v1 - v2);
	ASSERT_ANY_THROW(TDynamicVector<int> v3 = v2 - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(4);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	int v3 = v1 * v2;
	EXPECT_EQ(300, v3);
	EXPECT_EQ(4, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(3, v1[2]);
	EXPECT_EQ(4, v1[3]);
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(10, v2[0]);
	EXPECT_EQ(20, v2[1]);
	EXPECT_EQ(30, v2[2]);
	EXPECT_EQ(40, v2[3]);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	TDynamicVector<int> v2(5);
	v2[0] = 10;
	v2[1] = 20;
	v2[2] = 30;
	v2[3] = 40;
	v2[4] = 50;
	ASSERT_ANY_THROW(int v3 = v1*v2);
	ASSERT_ANY_THROW(int v3 = v2 * v1);
}

