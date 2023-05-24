#include "main.h"

/**
 *_print - function prints string
 *@str: string printed
 *
 * Return: Always Nothing
 */
void _print(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_char(str[i]);
		i++;
	}
}

/**
 * print_char - print character to prompt
 * @c: The character to print
 *
 * Return: 1 (Success) -1 on error
 */
int print_char(char c)
{
	static int i;
	static char buffer[WR_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WR_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * print_file_descriptor - prints string in prompt
 * @str: string to print
 * @file_descriptor: file descriptor
 *
 * Return: the number of chars put
 */
int print_file_descriptor(char *str, int file_descriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_file_descriptor(*str++, file_descriptor);
	}
	return (i);
}

/**
 * error_print - prints error message in stdout
 * @inf: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_print(info_t *inf, char *estr)
{
	error_puts(inf->file_name);
	error_puts(": ");
	print_decimal(inf->line_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(inf->argv[0]);
	error_puts(": ");
	error_puts(estr);
}

/**
 * print_decimal - print decimal based on 10
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int file_descriptor)
{
	int (*print_char)(char) = print_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_descriptor == STDERR_FILENO)
    {
		print_char = error_put_char;
    }
	if (input < 0)
	{
		_abs_ = -input;
		print_char('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

