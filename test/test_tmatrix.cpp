#include "tmatrix.h"
#include "types_of_matrix.h"

#include <gtest.h>

//ASSERT_NO_THROW(code)    проверяет, что код не бросает исключение
//ASSERT_ANY_THROW(code)   проверяет, что код бросает исключение
//ASSERT_EQ(a, b)          проверяет равенство a == b
//EXPECT_EQ нефатальная проверка

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) //с полож размером
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) //размер больше положеного
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) //с отриц. длиной
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) //конструктор копирования
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) //скопированная матрица
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 2; m[0][1] = 4; m[0][2] = 1;
	m[1][0] = 5; m[1][1] = 3; m[1][2] = 7;
	m[2][0] = 8; m[2][1] = 6; m[2][2] = 9;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) //копия не должна измениться
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 3; m[0][1] = 5;
	m[1][0] = 7; m[1][1] = 2;
	TDynamicMatrix<int> m1(m);
	m[0][0] = 10;
	EXPECT_NE(m[0][0], m1[0][0]);
	EXPECT_EQ(3, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[1][1] = 9;
	EXPECT_EQ(9, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(-1)[0] = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(10)[0] = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) //обрабатывает случай m = m
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 4; m[0][1] = 6;
	m[1][0] = 8; m[1][1] = 2;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(4, m[0][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) //присваивания матриц одинакового размера
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1; m1[0][1] = 3;
	m1[1][0] = 5; m1[1][1] = 7;
	m2 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) //размер целевой матрицы меняется на размер исходной
{
	TDynamicMatrix<int> m1(2), m2(3);
	m2 = m1; // присваиваем матр 2x2 матр 3x3
	EXPECT_EQ(2, m2.size()); // размер должен измениться на 2
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) //присв матрицы разного размера
{
	TDynamicMatrix<int> m1(2), m2(4);
	ASSERT_NO_THROW(m2 = m1); //бросает исключение?
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 2; m1[0][1] = 4;
	m1[1][0] = 6; m1[1][1] = 8;
	m2[0][0] = 2; m2[0][1] = 4;
	m2[1][0] = 6; m2[1][1] = 8;
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 2;
	m[1][0] = 3; m[1][1] = 4; m[1][2] = 5;
	m[2][0] = 6; m[2][1] = 7; m[2][2] = 8;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(3);
	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), expected(2);
	m1[0][0] = 1; m1[0][1] = 3;
	m1[1][0] = 5; m1[1][1] = 7;
	m2[0][0] = 2; m2[0][1] = 4;
	m2[1][0] = 6; m2[1][1] = 8;
	expected[0][0] = 3; expected[0][1] = 7;
	expected[1][0] = 11; expected[1][1] = 15;
	EXPECT_EQ(expected, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 + m2);
}



TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), expected(2);
	m1[0][0] = 10; m1[0][1] = 12;
	m1[1][0] = 14; m1[1][1] = 16;
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3; m2[1][1] = 4;
	expected[0][0] = 9; expected[0][1] = 10;
	expected[1][0] = 11; expected[1][1] = 12;
	EXPECT_EQ(expected, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), expected(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;
	m2[0][0] = 5; m2[0][1] = 6;
	m2[1][0] = 7; m2[1][1] = 8;
	// Правильное вычисление:
	// (1*5 + 2*7, 1*6 + 2*8) = (5+14, 6+16) = (19, 22)
	// (3*5 + 4*7, 3*6 + 4*8) = (15+28, 18+32) = (43, 50)
	expected[0][0] = 19; expected[0][1] = 22;
	expected[1][0] = 43; expected[1][1] = 50;
	EXPECT_EQ(expected, m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m(2), expected(2);
	m[0][0] = 2; m[0][1] = 3;
	m[1][0] = 4; m[1][1] = 5;
	expected[0][0] = 6; expected[0][1] = 9;
	expected[1][0] = 12; expected[1][1] = 15;
	EXPECT_EQ(expected, m * 3);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2), expected(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;
	v[0] = 3; v[1] = 2;
	// Правильное вычисление:
	// 1*3 + 2*2 = 3 + 4 = 7
	// 3*3 + 4*2 = 9 + 8 = 17
	expected[0] = 7; expected[1] = 17;
	EXPECT_EQ(expected, m * v);
}


//here
TEST(TGeneralBandMatrix, can_create_with_positive_size_and_bandwidth)
{
	ASSERT_NO_THROW(TGeneralBandMatrix<int> m(5, 1, 1));
}

TEST(TGeneralBandMatrix, throws_when_bandwidth_too_large)
{
	ASSERT_ANY_THROW(TGeneralBandMatrix<int> m(3, 5, 5));
}

TEST(TGeneralBandMatrix, can_set_and_get_element_within_band)
{
	TGeneralBandMatrix<double> m(4, 1, 1);
	ASSERT_NO_THROW(m(1, 1) = 5.5);
	EXPECT_EQ(5.5, m(1, 1));
}

TEST(TGeneralBandMatrix, throws_when_set_element_outside_band)
{
	TGeneralBandMatrix<int> m(4, 1, 1);
	ASSERT_ANY_THROW(m(0, 2) = 10);
}

TEST(TGeneralBandMatrix, correctly_stores_band_elements)
{
	TGeneralBandMatrix<int> m(3, 1, 1);
	m(0, 0) = 2; m(0, 1) = 3;
	m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
	m(2, 1) = 7; m(2, 2) = 8;
	EXPECT_EQ(2, m(0, 0));
	EXPECT_EQ(3, m(0, 1));
	EXPECT_EQ(4, m(1, 0));
	EXPECT_EQ(5, m(1, 1));
	EXPECT_EQ(6, m(1, 2));
	EXPECT_EQ(7, m(2, 1));
	EXPECT_EQ(8, m(2, 2));
}

TEST(TGeneralBandMatrix, multiplication_works_correctly)
{
	TGeneralBandMatrix<int> A(3, 1, 1);
	TGeneralBandMatrix<int> B(3, 1, 1);

	// Заполняем матрицу A
	A(0, 0) = 2; A(0, 1) = 3;
	A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
	A(2, 1) = 7; A(2, 2) = 8;

	// Заполняем матрицу B  
	B(0, 0) = 1; B(0, 1) = 2;
	B(1, 0) = 3; B(1, 1) = 4; B(1, 2) = 5;
	B(2, 1) = 6; B(2, 2) = 7;

	auto C = A * B;

	// Проверяем результат (все элементы матрицы 3x3)
	// Правильное вычисление:
	// C(0,0) = 2*1 + 3*3 = 2 + 9 = 11
	// C(0,1) = 2*2 + 3*4 = 4 + 12 = 16
	// C(0,2) = 2*0 + 3*5 = 0 + 15 = 15
	// C(1,0) = 4*1 + 5*3 + 6*0 = 4 + 15 + 0 = 19
	// C(1,1) = 4*2 + 5*4 + 6*6 = 8 + 20 + 36 = 64
	// C(1,2) = 4*0 + 5*5 + 6*7 = 0 + 25 + 42 = 67
	// C(2,0) = 7*3 + 8*0 = 21 + 0 = 21
	// C(2,1) = 7*4 + 8*6 = 28 + 48 = 76
	// C(2,2) = 7*5 + 8*7 = 35 + 56 = 91

	EXPECT_EQ(11, C(0, 0));
	EXPECT_EQ(16, C(0, 1));
	EXPECT_EQ(15, C(0, 2));
	EXPECT_EQ(19, C(1, 0));
	EXPECT_EQ(64, C(1, 1));
	EXPECT_EQ(67, C(1, 2));
	EXPECT_EQ(21, C(2, 0));
	EXPECT_EQ(76, C(2, 1));
	EXPECT_EQ(91, C(2, 2));
}

TEST(TSymmetricBandMatrix, can_create_symmetric_matrix)
{
	ASSERT_NO_THROW(TSymmetricBandMatrix<double> m(5, 2));
}

TEST(TSymmetricBandMatrix, maintains_symmetry)
{
	TSymmetricBandMatrix<int> m(4, 1);
	m(0, 1) = 5;
	EXPECT_EQ(5, m(1, 0));
	EXPECT_EQ(5, m(0, 1));
}

TEST(TTriangleBandMatrix, can_create_upper_triangular)
{
	ASSERT_NO_THROW(TTriangleBandMatrix<double> m(4, 1, true));
}

TEST(TTriangleBandMatrix, can_create_lower_triangular)
{
	ASSERT_NO_THROW(TTriangleBandMatrix<double> m(4, 1, false));
}

TEST(TTriangleBandMatrix, upper_triangular_blocks_lower_access)
{
	TTriangleBandMatrix<int> m(3, 1, true);
	m(0, 1) = 5;
	ASSERT_ANY_THROW(m(1, 0) = 10);
}

TEST(TTriangleBandMatrix, lower_triangular_blocks_upper_access)
{
	TTriangleBandMatrix<int> m(3, 1, false);
	m(1, 0) = 5;
	ASSERT_ANY_THROW(m(0, 1) = 10);
}

TEST(TTriangleBandMatrix, correctly_identifies_matrix_type)
{
	TTriangleBandMatrix<int> upper(3, 1, true);
	TTriangleBandMatrix<int> lower(3, 1, false);
	EXPECT_TRUE(upper.is_upper_triangle());
	EXPECT_FALSE(upper.is_lower_triangle());
	EXPECT_TRUE(lower.is_lower_triangle());
	EXPECT_FALSE(lower.is_upper_triangle());
}

TEST(TCSRMatrix, can_create_with_positive_dimensions)
{
	ASSERT_NO_THROW(TCSRMatrix<double> m(3, 3));
}

TEST(TCSRMatrix, throws_when_invalid_dimensions)
{
	ASSERT_ANY_THROW(TCSRMatrix<int> m(0, 5));
	ASSERT_ANY_THROW(TCSRMatrix<int> m(MAX_MATRIX_SIZE + 1, 3));
}

TEST(TCSRMatrix, can_set_and_get_nonzero_elements)
{
	TCSRMatrix<double> m(3, 3);
	m.set(0, 0, 1.5);
	m.set(1, 1, 2.5);
	m.set(2, 2, 3.5);
	EXPECT_EQ(1.5, m(0, 0));
	EXPECT_EQ(2.5, m(1, 1));
	EXPECT_EQ(3.5, m(2, 2));
	EXPECT_EQ(0.0, m(0, 1));
}

TEST(TCSRMatrix, does_not_store_zero_elements)
{
	TCSRMatrix<int> m(2, 2);
	m.set(0, 0, 5);
	m.set(0, 1, 0);
	EXPECT_EQ(1, m.non_zeros());
}

TEST(TCSRMatrix, can_update_existing_element)
{
	TCSRMatrix<int> m(2, 2);
	m.set(0, 0, 5);
	m.set(0, 0, 10);
	EXPECT_EQ(10, m(0, 0));
	EXPECT_EQ(1, m.non_zeros());
}

TEST(TCSRMatrix, can_remove_element_by_setting_to_zero)
{
	TCSRMatrix<int> m(2, 2);
	m.set(0, 0, 5);
	EXPECT_EQ(1, m.non_zeros());
	m.set(0, 0, 0);
	EXPECT_EQ(0, m.non_zeros());
	EXPECT_EQ(0, m(0, 0));
}

TEST(TCSRMatrix, correctly_counts_nonzero_elements)
{
	TCSRMatrix<int> m(3, 3);
	EXPECT_EQ(0, m.non_zeros());
	m.set(0, 0, 1);
	m.set(1, 1, 2);
	m.set(2, 2, 3);
	EXPECT_EQ(3, m.non_zeros());
}

TEST(TCSRMatrix, get_method_returns_correct_values)
{
	TCSRMatrix<int> m(2, 2);
	m.set(0, 0, 7);
	EXPECT_EQ(7, m.get(0, 0));
	EXPECT_EQ(0, m.get(0, 1));
	EXPECT_EQ(0, m.get(1, 0));
	EXPECT_EQ(0, m.get(1, 1));
}

TEST(TCSRMatrix, operator_access_works_like_get)
{
	TCSRMatrix<int> m(2, 2);
	m.set(0, 0, 8);
	EXPECT_EQ(8, m(0, 0));
	EXPECT_EQ(0, m(0, 1));
	EXPECT_EQ(m.get(0, 0), m(0, 0));
}