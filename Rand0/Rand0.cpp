/////////////////////////////////////////////////////////////////////////////////////////
//написать программу, котора€ генерирует примеры, которые нужно решить. Ќапример:
//5 + 6 * 2, или 5 + (10 - 7).
/////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <sstream>
#include <string>
/////////////////////////////////////////////////////////////////////////////////////////
typedef std::string     T_str;
/////////////////////////////////////////////////////////////////////////////////////////
const   char    SPACE_SYMB = ' ';
const   int     SEGMENT_SIZE_FOR_RESULT = 13;
const   int     SEGMENT_SIZE_FOR_OPERAND = 13;
/////////////////////////////////////////////////////////////////////////////////////////
enum    T_operation
{
	add_op,
	sub_op,
	mult_op,
	div_op,
	op_count
};
/////////////////////////////////////////////////////////////////////////////////////////
T_operation     get_rand_op()
{
	return  T_operation(
		rand() % op_count
	);
}
/////////////////////////////////////////////////////////////////////////////////////////
int     get_rand_num_starting_with_1_from_segment_with_size(int    segment_size)
{
	return  rand() % segment_size + 1;
}
/////////////////////////////////////////////////////////////////////////////////////////
void    set_operands_for_op_and_result
(
	T_operation         op,
	int                 result,
	int             &   operand_1,
	int             &   operand_2
)
{
	do
	{
		operand_2 = get_rand_num_starting_with_1_from_segment_with_size(SEGMENT_SIZE_FOR_OPERAND);
	} while (
		op == mult_op
		&& result  %   operand_2 != 0
		);

	switch (op)
	{
	case    add_op:
		operand_1 = result - operand_2;
		break;

	case    sub_op:
		operand_1 = result + operand_2;
		break;

	case    mult_op:
		operand_1 = result / operand_2;
		break;

	case    div_op:
		operand_1 = result * operand_2;
		break;

	default:
		;
	}//switch
}
/////////////////////////////////////////////////////////////////////////////////////////
int     prior(T_operation  op)
{
	switch (op)
	{
	case    add_op:
	case    sub_op:
		return  1;

	default:
		return  2;
	}//switch
}
/////////////////////////////////////////////////////////////////////////////////////////
char    get_op_symb(T_operation  op)
{
	switch (op)
	{
	case    add_op:   return  '+';
	case    sub_op:   return  '-';
	case    mult_op:   return  '*';
	case    div_op:   return  '/';
	default:   return  SPACE_SYMB;
	}//switch
}
/////////////////////////////////////////////////////////////////////////////////////////
T_str   op_to_str(T_operation  op)
{
	std::ostringstream  sout;

	sout << SPACE_SYMB
		<< get_op_symb(op)
		<< SPACE_SYMB;

	return  sout.str();
}
/////////////////////////////////////////////////////////////////////////////////////////
T_str   generate_exercise_with_operation_and_result
(
	T_operation     op,
	int             result
)
{
	int     operand_1 = 0;
	int     operand_2 = 0;

	set_operands_for_op_and_result
	(
		op,
		result,
		operand_1,
		operand_2
	);

	std::ostringstream  sout;

	sout << operand_1
		<< op_to_str(op)
		<< operand_2;

	return  sout.str();
}
/////////////////////////////////////////////////////////////////////////////////////////
void    take_in_brackets(T_str     &   expr)
{
	expr.insert(0, 1, '(');
	expr.push_back(')');
}
/////////////////////////////////////////////////////////////////////////////////////////
void    set_exercise_with_two_rand_operations_and_rand_result
(
	T_str   &   exercise,
	int     &   result
)
{
	result = get_rand_num_starting_with_1_from_segment_with_size(SEGMENT_SIZE_FOR_RESULT);
	T_operation     op_1 = get_rand_op();
	T_operation     op_2 = get_rand_op();
	int             operand_1 = 0;
	int             operand_2 = 0;

	int     index_of_operation_with_higher_priority = rand() % 2 + 1;

	std::ostringstream  sout;

	if (index_of_operation_with_higher_priority == 1)
	{
		set_operands_for_op_and_result
		(
			op_2,
			result,
			operand_1,
			operand_2
		);

		T_str   operand_1_str = generate_exercise_with_operation_and_result
		(
			op_1,
			operand_1
		);

		//—тавим скобки ,если приоритет второй операции выше.
		if (
			prior(op_1)
			< prior(op_2)
			)
		{
			take_in_brackets(operand_1_str);
		}//if

		sout << operand_1_str
			<< op_to_str(op_2)
			<< operand_2;
	}
	else
	{
		set_operands_for_op_and_result
		(
			op_1,
			result,
			operand_1,
			operand_2
		);

		T_str   operand_2_str = generate_exercise_with_operation_and_result
		(
			op_2,
			operand_2
		);

		//—тавим скобки, если приоритет первой операции выше или такой же, но она €вл€етс€ вычитанием или делением.
		if (
			prior(op_2)
			< prior(op_1)

			|| prior(op_2)
			== prior(op_1)

			&& (
				op_1 == sub_op
				|| op_1 == div_op
				)
			)
		{
			take_in_brackets(operand_2_str);
		}//if

		sout << operand_1
			<< op_to_str(op_1)
			<< operand_2_str;
	}//else

	exercise = sout.str();
}
/////////////////////////////////////////////////////////////////////////////////////////
int     main()
{
	srand(unsigned(time(0)));

	for (;;)
	{
		T_str   exercise;
		int     result = 0;

		set_exercise_with_two_rand_operations_and_rand_result
		(
			exercise,
			result
		);

		int     user_result = 0;

		do
		{
			std::cout << exercise
				<< "\t= ";

			std::cin >> user_result;
		} while (
			user_result
			!= result
			);
	}//for
}