#include "monty.h"
#include <stdio.h>

stack_t *global_current_stack;
instruction_t *instruction;
/**
 * format_instruction - monty reader
 * @line: line to excute the function
 * @line_number: number of line of instruction
 *
 * reads line, and returns the instruction
 *
 * Return: instruction struct
 */
instruction_t *format_instruction(char *line, unsigned int line_number)
{
	char *ptr;

	instruction = malloc(sizeof(instruction_t));
	if (instruction == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	memset(instruction, 0, sizeof(instruction_t));
	ptr = strtok(line, DELIM);
	instruction->opcode = ptr;
	if (is_noargs(ptr))
		instruction->f = set_noargs(ptr);
	else if (strcmp(ptr, "push") == 0)
	{
		instruction->f = push;
		ptr = strtok(NULL, DELIM);
		if (ptr == NULL || !is_number(ptr))
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		global_current_stack = malloc(sizeof(stack_t));
		if (global_current_stack == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}
		global_current_stack = memset(global_current_stack, 0, sizeof(stack_t));
		global_current_stack->n = atoi(ptr);
	}
	else if (ptr[0] == '#')
		instruction->f = nop;
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, ptr);
		exit(EXIT_FAILURE);
	}
	return (instruction);
}
/**
 * is_noargs - opcode function
 * @opcode: str of opcode
 *
 * sets function of op code
 * for no args opcode
 *
 * Return: Function
 */
bool is_noargs(char *opcode)
{
	char *ops[] = {"pall", "pint", "pop",
				   "swap", "add", "nop",
				   "sub", "div", "mul",
				   "mod", "pchar", "pstr",
				   "rotl", "rotr", NULL};
	size_t i;

	for (i = 0; ops[i] != NULL; i++)
		if (strcmp(opcode, ops[i]) == 0)
			return (true);

	return (false);
}
/**
 * set_noargs - opcode function
 * @opcode: str of opcode
 *
 * sets function of op code
 * for no args opcode
 *
 * Return: Function
 */
void (*set_noargs(char *opcode))(stack_t **stack, unsigned int line_number)
{
	if (strcmp(opcode, "pall") == 0)
		return (pall);
	else if (strcmp(opcode, "pint") == 0)
		return (pint);
	else if (strcmp(opcode, "swap") == 0)
		return (swap);
	else if (strcmp(opcode, "add") == 0)
		return (add);
	else if (strcmp(opcode, "nop") == 0)
		return (nop);
	else if (strcmp(opcode, "sub") == 0)
		return (sub);
	else if (strcmp(opcode, "div") == 0)
		return (_div);
	else if (strcmp(opcode, "mul") == 0)
		return (mul);
	else if (strcmp(opcode, "mod") == 0)
		return (mod);
	else if (strcmp(opcode, "pchar") == 0)
		return (pchar);
	else if (strcmp(opcode, "pstr") == 0)
		return (pstr);
	else if (strcmp(opcode, "rotl") == 0)
		return (rotl);
	else if (strcmp(opcode, "rotr") == 0)
		return (rotr);
	else
		return (pop);
}