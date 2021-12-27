#include "shell.h"

/**
 * _strcat - concatenates two string
 *
 * @prmDest: char pointer
 * @prmSrc: char pointer
 *
 * Return: string
 */
char *_strcat(char *prmDest, char *prmSrc)
{
	int length, d_size, s_size;

	d_size = _strlen(prmDest);
	s_size = _strlen(prmSrc);

	for (length = 0; length < s_size; length++)
	{
		prmDest[d_size + length] = prmSrc[length];
	}

	return (prmDest);
}

/**
 * _strcmp - compare two strings
 * @str1: string pointer to compare
 * @str2: another string to compare
 * 
 * Return: compare strings
 */

int _strcmp(char *str1, char *str2)
{
int len;

for (len = 0; str1[len] != '\0'; len++)
{
if (str1[len] - str2[len] != 0)
return (str1[len] - str2[len]);
}
return (0);
}

/**
 * _strconcat - concatenates two strings.
 *
 * @prmString1: char pointer to concatenate
 * @prmString2: char pointer to concatenate
 *
 * Return: char pointer concatenated
 */
char *_strconcat(char *prmString1, char *prmString2)
{
	char *s;
	int cLoop1, cLoop2, size;

	if (prmString1 == NULL)
		prmString1 = "\0";

	if (prmString2 == NULL)
		prmString2 = "\0";

	size = _strlen(prmString1) + _strlen(prmString2);
	s = malloc(sizeof(char) * (size + 1));

	if (s == NULL)
		return (NULL);

	for (cLoop1 = 0; prmString1[cLoop1]; cLoop1++)
		s[cLoop1] = prmString1[cLoop1];

	for (cLoop2 = 0; prmString2[cLoop2]; cLoop1++, cLoop2++)
		s[cLoop1] = prmString2[cLoop2];

	s[cLoop1] = '\0';

	return (s);
}

/**
 * _strcpy - copies the string pointed to by src,
 *               including the terminating null byte (\0),
 *               to the buffer pointed to by dest
 *
 * @prmDest: char pointer
 * @prmSrc: char pointer
 *
 * Return: char*
 */
char *_strcpy(char *prmDest, char *prmSrc)
{
	int cLoop, size = _strlen(prmSrc);

	for (cLoop = 0; cLoop < size; cLoop++)
	{
		prmDest[cLoop] = prmSrc[cLoop];
	}

	prmDest[size] = '\0';

	return (prmDest);
}

/**
 * _strcspn - gets the length of a prefix substring.
 *
 * @prmString: string to search
 * @prmDeny: characters to deny
 *
 * Return: a pointer to the first occurrence of the character c
 *         in the string s, or NULL if the character is not found
 */
unsigned int _strcspn(char *prmString, char *prmDeny)
{
	unsigned int sLoop, dLoop;

	for (dLoop = 0; prmDeny[dLoop] != '\0'; dLoop++)
	{
		for (sLoop = 0; prmDeny[dLoop] != prmString[sLoop]; sLoop++)
			if ('\0' == prmString[sLoop])
				return (sLoop);
	}

	return (sLoop);
}
