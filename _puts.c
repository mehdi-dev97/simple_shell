#include "main.h"

/**
 * error_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Always Nothing
 */
void error_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		error_put_char(str[i]);
		i++;
	}
}

/**
 * put_file_descriptor - print character by given file descriptor
 * @c: character to be print
 * @file_descriptor: file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_file_descriptor(char c, int file_descriptor)
{
	static int i;
	static char buffer[WR_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WR_BUFFER_SIZE)
	{
		write(file_descriptor, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * error_put_char - print character to stderr
 * @c: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_put_char(char c)
{
	static int i;
	static char buf[WR_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WR_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}
