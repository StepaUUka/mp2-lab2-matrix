//Изменения для коммита с упомянанием)
#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(m1);
	EXPECT_EQ(3, m2.size());
	EXPECT_EQ(1, m2[0][0]); EXPECT_EQ(2, m2[0][1]); EXPECT_EQ(3, m2[0][2]);
	EXPECT_EQ(4, m2[1][0]); EXPECT_EQ(5, m2[1][1]); EXPECT_EQ(6, m2[1][2]);
	EXPECT_EQ(7, m2[2][0]); EXPECT_EQ(8, m2[2][1]); EXPECT_EQ(9, m2[2][2]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(m1);
	m1[0][0] = 10; m1[0][1] = 20; m1[0][2] = 30;
	m1[1][0] = 40; m1[1][1] = 50; m1[1][2] = 60;
	m1[2][0] = 70; m1[2][1] = 80; m1[2][2] = 90;
	EXPECT_EQ(3, m2.size());
	EXPECT_EQ(1, m2[0][0]); EXPECT_EQ(2, m2[0][1]); EXPECT_EQ(3, m2[0][2]);
	EXPECT_EQ(4, m2[1][0]); EXPECT_EQ(5, m2[1][1]); EXPECT_EQ(6, m2[1][2]);
	EXPECT_EQ(7, m2[2][0]); EXPECT_EQ(8, m2[2][1]); EXPECT_EQ(9, m2[2][2]);
	m2[0][0] = 100;
	EXPECT_EQ(10, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m1(3);
	EXPECT_EQ(3, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 100;
	EXPECT_EQ(100, m1[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0][-1]);
	ASSERT_ANY_THROW(m[-1][0]);
	ASSERT_ANY_THROW(m[-1][-4]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0][100]);
	ASSERT_ANY_THROW(m[100][0]);
	ASSERT_ANY_THROW(m[100][30]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	m1 = m1;
	EXPECT_EQ(3, m1.size());
	EXPECT_EQ(1, m1[0][0]); EXPECT_EQ(2, m1[0][1]); EXPECT_EQ(3, m1[0][2]);
	EXPECT_EQ(4, m1[1][0]); EXPECT_EQ(5, m1[1][1]); EXPECT_EQ(6, m1[1][2]);
	EXPECT_EQ(7, m1[2][0]); EXPECT_EQ(8, m1[2][1]); EXPECT_EQ(9, m1[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(3);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30;
	m2[1][0] = 40; m2[1][1] = 50; m2[1][2] = 60;
	m2[2][0] = 70; m2[2][1] = 80; m2[2][2] = 90;
	m1 = m2;
	EXPECT_EQ(3, m1.size());
	EXPECT_EQ(10, m1[0][0]); EXPECT_EQ(20, m1[0][1]); EXPECT_EQ(30, m1[0][2]);
	EXPECT_EQ(40, m1[1][0]); EXPECT_EQ(50, m1[1][1]); EXPECT_EQ(60, m1[1][2]);
	EXPECT_EQ(70, m1[2][0]); EXPECT_EQ(80, m1[2][1]); EXPECT_EQ(90, m1[2][2]);
	EXPECT_EQ(3, m2.size());
	EXPECT_EQ(10, m2[0][0]); EXPECT_EQ(20, m2[0][1]); EXPECT_EQ(30, m2[0][2]);
	EXPECT_EQ(40, m2[1][0]); EXPECT_EQ(50, m2[1][1]); EXPECT_EQ(60, m2[1][2]);
	EXPECT_EQ(70, m2[2][0]); EXPECT_EQ(80, m2[2][1]); EXPECT_EQ(90, m2[2][2]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m3(m1);
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30; m2[0][3] = 40;
	m2[1][0] = 50; m2[1][1] = 60; m2[1][2] = 70; m2[1][3] = 80;
	m2[2][0] = 90; m2[2][1] = 100; m2[2][2] = 110; m2[2][3] = 120;
	m2[3][0] = 130; m2[3][1] = 140; m2[3][2] = 150; m2[3][3] = 160;
	m1 = m2;
	EXPECT_EQ(4, m1.size());
	m2 = m3;
	EXPECT_EQ(3, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30; m2[0][3] = 40;
	m2[1][0] = 50; m2[1][1] = 60; m2[1][2] = 70; m2[1][3] = 80;
	m2[2][0] = 90; m2[2][1] = 100; m2[2][2] = 110; m2[2][3] = 120;
	m2[3][0] = 130; m2[3][1] = 140; m2[3][2] = 150; m2[3][3] = 160;
	m1 = m2;
	EXPECT_EQ(4, m1.size());
	EXPECT_EQ(10, m1[0][0]); EXPECT_EQ(20, m1[0][1]); EXPECT_EQ(30, m1[0][2]); EXPECT_EQ(40, m1[0][3]);
	EXPECT_EQ(50, m1[1][0]); EXPECT_EQ(60, m1[1][1]); EXPECT_EQ(70, m1[1][2]); EXPECT_EQ(80, m1[1][3]);
	EXPECT_EQ(90, m1[2][0]); EXPECT_EQ(100, m1[2][1]); EXPECT_EQ(110, m1[2][2]); EXPECT_EQ(120, m1[2][3]);
	EXPECT_EQ(130, m1[3][0]); EXPECT_EQ(140, m1[3][1]); EXPECT_EQ(150, m1[3][2]); EXPECT_EQ(160, m1[3][3]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(3);
	m2[0][0] = 1; m2[0][1] = 2; m2[0][2] = 3;
	m2[1][0] = 4; m2[1][1] = 5; m2[1][2] = 6;
	m2[2][0] = 7; m2[2][1] = 8; m2[2][2] = 9;
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	EXPECT_TRUE(m1 == m1);
	m1[0][0] = 1000;
	EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30; m2[0][3] = 40;
	m2[1][0] = 50; m2[1][1] = 60; m2[1][2] = 70; m2[1][3] = 80;
	m2[2][0] = 90; m2[2][1] = 100; m2[2][2] = 110; m2[2][3] = 120;
	m2[3][0] = 130; m2[3][1] = 140; m2[3][2] = 150; m2[3][3] = 160;
	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(3);
	m2[0][0] = 11; m2[0][1] = 22; m2[0][2] = 33;
	m2[1][0] = 44; m2[1][1] = 55; m2[1][2] = 66;
	m2[2][0] = 77; m2[2][1] = 88; m2[2][2] = 99;
	EXPECT_EQ(m1.size(), m2.size());
	TDynamicMatrix<int> m3=m1+m2;
	EXPECT_EQ(12, m3[0][0]); EXPECT_EQ(24, m3[0][1]); EXPECT_EQ(36, m3[0][2]);
	EXPECT_EQ(48, m3[1][0]); EXPECT_EQ(60, m3[1][1]); EXPECT_EQ(72, m3[1][2]);
	EXPECT_EQ(84, m3[2][0]); EXPECT_EQ(96, m3[2][1]); EXPECT_EQ(108, m3[2][2]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30; m2[0][3] = 40;
	m2[1][0] = 50; m2[1][1] = 60; m2[1][2] = 70; m2[1][3] = 80;
	m2[2][0] = 90; m2[2][1] = 100; m2[2][2] = 110; m2[2][3] = 120;
	m2[3][0] = 130; m2[3][1] = 140; m2[3][2] = 150; m2[3][3] = 160;
	ASSERT_ANY_THROW(TDynamicMatrix<int> m3 = m1 + m2);
	ASSERT_ANY_THROW(TDynamicMatrix<int> m3 = m2 + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(3);
	m2[0][0] = 11; m2[0][1] = 22; m2[0][2] = 33;
	m2[1][0] = 44; m2[1][1] = 55; m2[1][2] = 66;
	m2[2][0] = 77; m2[2][1] = 88; m2[2][2] = 99;
	EXPECT_EQ(m1.size(), m2.size());
	TDynamicMatrix<int> m3 = m2 - m1;
	EXPECT_EQ(10, m3[0][0]); EXPECT_EQ(20, m3[0][1]); EXPECT_EQ(30, m3[0][2]);
	EXPECT_EQ(40, m3[1][0]); EXPECT_EQ(50, m3[1][1]); EXPECT_EQ(60, m3[1][2]);
	EXPECT_EQ(70, m3[2][0]); EXPECT_EQ(80, m3[2][1]); EXPECT_EQ(90, m3[2][2]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30; m2[0][3] = 40;
	m2[1][0] = 50; m2[1][1] = 60; m2[1][2] = 70; m2[1][3] = 80;
	m2[2][0] = 90; m2[2][1] = 100; m2[2][2] = 110; m2[2][3] = 120;
	m2[3][0] = 130; m2[3][1] = 140; m2[3][2] = 150; m2[3][3] = 160;
	ASSERT_ANY_THROW(TDynamicMatrix<int> m3 = m1 - m2);
	ASSERT_ANY_THROW(TDynamicMatrix<int> m3 = m2 - m1);
}

