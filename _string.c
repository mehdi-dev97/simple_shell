#include "main.h"

/**
 * string_length - get length of given string
 * @str: string
 *
 * Return: string length
 */
int string_length(char *str)
{
	int length = 0;

	if (!str)
	{
		return (0);
	}

	while (*str++)
	{
		length++;
	}
	return (length);
}

/**
 * string_compare - comparison of two given strangs.
 * @str1: first strang
 * @str2: second strang
 *
 * Return: 1 on (Success) -1 on difference
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
	{
		return (*str1 < *str2 ? -1 : 1);
	}
}

/**
 * string_start_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *string_start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * string_concat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_concat(char *dest, char *src)
{
	char *string = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (string);
}

