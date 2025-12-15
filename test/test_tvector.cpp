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

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) //скопированный вектор аналогичный
{
	TDynamicVector<int> v(3);
	v[0] = 2; v[1] = 4; v[2] = 6;
	TDynamicVector<int> v1(v);
	ASSERT_TRUE(v == v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(5);
	v[0] = 3; v[1] = 5; v[2] = 7; v[3] = 9; v[4] = 11;
	TDynamicVector<int> v1(v);
	v[0] = 8;
	EXPECT_NE(v[0], v1[0]);
	EXPECT_EQ(3, v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 7;
	EXPECT_EQ(7, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(-1) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(10) = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)  //v = v
{
	TDynamicVector<int> v(3);
	v[0] = 2; v[1] = 4; v[2] = 6;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(2, v[0]);
	EXPECT_EQ(6, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 3; v1[1] = 6; v1[2] = 9;
	v2 = v1;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size) //размер вектора меняется на размер исходного
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 1; v1[1] = 3; v1[2] = 5;
	v2 = v1;
	EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) // присв векторы разного размера
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 2; v1[1] = 4; v1[2] = 8;
	ASSERT_NO_THROW(v2 = v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) //==
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 5; v1[1] = 10; v1[2] = 15;
	v2[0] = 5; v2[1] = 10; v2[2] = 15;
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)  //равен самомму себе
{
	TDynamicVector<int> v(3);
	v[0] = 4; v[1] = 7; v[2] = 11;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) //разный размер
{
	TDynamicVector<int> v1(3), v2(5);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3), expected(3);
	v[0] = 2; v[1] = 4; v[2] = 6;
	expected[0] = 5; expected[1] = 7; expected[2] = 9;
	EXPECT_EQ(expected, v + 3);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3), expected(3);
	v[0] = 8; v[1] = 12; v[2] = 16;
	expected[0] = 5; expected[1] = 9; expected[2] = 13;
	EXPECT_EQ(expected, v - 3);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3), expected(3);
	v[0] = 3; v[1] = 5; v[2] = 7;
	expected[0] = 9; expected[1] = 15; expected[2] = 21;
	EXPECT_EQ(expected, v * 3);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), expected(3);
	v1[0] = 2; v1[1] = 5; v1[2] = 8;
	v2[0] = 3; v2[1] = 7; v2[2] = 11;
	expected[0] = 5; expected[1] = 12; expected[2] = 19;
	EXPECT_EQ(expected, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), expected(3);
	v1[0] = 10; v1[1] = 15; v1[2] = 20;
	v2[0] = 3; v2[1] = 7; v2[2] = 12;
	expected[0] = 7; expected[1] = 8; expected[2] = 8;
	EXPECT_EQ(expected, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 2; v1[1] = 4; v1[2] = 6;
	v2[0] = 3; v2[1] = 5; v2[2] = 7;
	// Скалярное произведение: 2*3 + 4*5 + 6*7 = 6 + 20 + 42 = 68
	EXPECT_EQ(68, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 * v2);
}