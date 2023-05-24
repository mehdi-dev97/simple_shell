#include "main.h"

/**
 * string_copy - function to copy given string
 * @dest: string destination
 * @src: string source
 *
 * Return: destination pointer
 */
char *string_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * string_duplicate - function to duplicate given string
 * @str: the string to duplicate
 *
 * Return: pointer string duplicated
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *string;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (NULL);
	for (length++; length--;)
		string[length] = *--str;
	return (string);
}

/**
 * string_copy_numbers - function to copy given string
 * @dest: string destination
 * @src: concat string
 * @n: number of copied characters
 *
 * Return: destination pointer
 */
char *string_copy_numbers(char *dest, char *src, int n)
{
	int i = 0, j;
	char *str = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * string_concat_number - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @num: number of contact string
 * Return: the concatenated string
 */
char *string_concat_number(char *dest, char *src, int num)
{
	int i = 0, j = 0;
	char *str = dest;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
	{
		dest[i] = '\0';
	}
	return (str);
}

/**
 * string_search - search char in string
 * @s: string
 * @c: char to search in
 *
 * Return: (str) pointer str area or NULL if not found
 */
char *string_search(char *str, char c)
{
	do {
		if (*str == c)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

