#include "simple_shell.h"

/**
 * print - Prints a string.
 *
 * @str: Given string to be printed.
 *
 * Return: Length of printed characters.
 */
int print(char *str)
{
	return ((int)write(1, str, _strlen(str)));
}

/**
 * trim_str - Removes leading and trailing blank spaces from a string.
 *
 * @str1: Pointer to a string.
 *
 * Return: 0 on SUCCESS,
 *        -1 otherwise.
 */
int trim_str(char **str)
{
	int i = 0, start = 0;
	char *tmp = *str;

	if (!str || !*str)
		return (-1);

	/* Find start position after leading blank(s) */
	while (tmp[start] && tmp[start] <= ' ')
		start++;

	/* Move text to begining of string from start position */
	if (start)
	{
		while (tmp[start])
			tmp[i++] = tmp[start++];
		tmp[i] = '\0';
	}

	/* Remove trailing blanks from end of string*/
	i = _strlen(tmp);
	if (i--)
		while (i && tmp[i] <= ' ')
			tmp[i--] = '\0';

	return (0);
}

/**
 * _strlen - Counts characters in a given string.
 *
 * @str: Given string to be measured.
 *
 * Return: Length of given string.
 */
int _strlen(char *str)
{
	int i = 0;

	while (str && *str++)
		i++;

	return (i);
}

/**
 * _concat - Concatenates two strings to form a path.
 *
 * @str1: First string to be concatenated before a '/'.
 * @str2: Second string to be concatenated after a '/'.
 *
 * Return: New concatenated string on success,
 *         NULL on error.
 */
char *_concat(char *str1, char *str2)
{
	char *str = NULL;
	int i = 0, tmp = 0;

	/* Data validation */
	if (!str1 || !str2 || !*str1 || !*str2)
		return (NULL);

	/* Create new, big, empty string */
	str = malloc(sizeof(char *) * ARR_SIZE);
	if (!str)
		return (NULL);

	/* Copy first string/path */
	while (str1[tmp] && i < ARR_SIZE)
		str[i++] = str1[tmp++];

	/* Add a forward slash after str1 and reset index */
	str[i++] = '/', tmp = 0;

	/* Concatenate second string/command to new string */
	while (str2[tmp] && i < ARR_SIZE)
		str[i++] = str2[tmp++];
	str[i] = '\0';

	return (str);
}

/**
 * _strcomp - Compares two strings to check equality.
 *
 * @str1: First string to be checked.
 * @str2: Second string to be checked.
 *
 * Return: 0 if both strings are equal,
 *         1 otherwise.
 */
int _strcomp(char *str1, char *str2)
{
	int i = 0;

	if (!str1 || !str2)
		return (1);

	while (str1[i] && str2[i])
		if (str1[i] == str2[i])
			i++;
		else
			break;

	if (str1[i] == str2[i])
		return (0);

	return (1);
}
