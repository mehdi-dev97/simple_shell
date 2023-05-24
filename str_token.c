#include "main.h"

/**
 * **string_to_word - splits a string into words
 * @str: given string
 * @d: delimeter
 * Return: pointer to an array of strings or NULL on error
 */

char **string_to_word(char *str, char *delimeter)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_separator(str[i], delimeter) && (is_separator(str[i + 1], delimeter) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_separator(str[i], delimeter))
			i++;
		k = 0;
		while (!is_separator(str[i + k], delimeter) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **string_to_words - split string to words list
 * @str: given string
 * @delimiter: delimeter
 * Return: array pointer of strings or NULL on error
 */
char **string_to_words(char *str, char delimiter)
{
	int i, j, k, m, words_number = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			words_number++;
	if (words_number == 0)
		return (NULL);
	s = malloc((1 + words_number) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words_number; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

