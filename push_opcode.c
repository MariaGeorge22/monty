#include "monty.h"
/**
 * push - monty opcode - put value in the stack
 * @stack: stack to update the node or the array
 * @line_number: number of instruction line
 *
 * executes the push opcode
 *
 * Return: void
 */
void push(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	if ((*stack) != NULL)
		(*stack)->prev = global_current_stack;
	global_current_stack->next = (*stack);
	global_current_stack->prev = NULL;
	(*stack) = global_current_stack;
}