#include "shell.h"

/**
 * _strdup - a pointer to a newly allocated space in memory,
 *           which contains a copy of the string given as a parameter.
 *
 * @prmString: char pointer to copy
 *
 * Return: a new char pointer
 */
char *_strdup(char *prmString)
{
	char *string;
	int cLoop;

	if (prmString == NULL)
		return (NULL);

	string = malloc(sizeof(char) * (_strlen(prmString) + 1));

	if (string == NULL)
		return (NULL);

	for (cLoop = 0; cLoop < _strlen(prmString) + 1; cLoop++)
		string[cLoop] = prmString[cLoop];

	return (string);
}

/**
 * _strlen - return string length
 *
 * @prmStr: string
 *
 * Return: string length
 */
int _strlen(char *prmStr)
{
	if (prmStr == NULL || *prmStr == '\0')
		return (0);
	return (_strlen(prmStr + 1) + 1);
}

/**
 * _strncpy - copies a string
 *
 * @prmDest: char pointer
 * @prmSrc: char pointer
 * @prmLimit: number of character
 *
 * Return: string
 */
char *_strncpy(char *prmDest, char *prmSrc, int prmLimit)
{
	int length, size_s;

	size_s = _strlen(prmSrc);

	for (length = 0; length < prmLimit; length++)
	{
		prmDest[length] = (length <= size_s) ? prmSrc[length] : '\0';
	}

	return (prmDest);
}

/**
 * _strstr - locates a substring.
 *
 * @prmHaystack: string where to search
 * @prmNeedle: string to search
 * @prmBegin: force to start at begin if true
 *
 * Return: the address to first location
 */
char *_strstr(char *prmHaystack, char *prmNeedle, int prmBegin)
{
	int haystackLoop = 0, needleLoop = 0, size = _strlen(prmNeedle);

	if (prmNeedle[0] == '\0')
	{
		return (prmHaystack);
	}

	for (
		haystackLoop = 0, needleLoop = 0;
		(haystackLoop + needleLoop) < _strlen(prmHaystack);
		needleLoop++
	)
	{
		if (prmNeedle[needleLoop] != prmHaystack[haystackLoop + needleLoop])
		{
			if (prmBegin == 0)
			{
				haystackLoop += needleLoop;
				needleLoop = 0;
			}
			else
				return (NULL);
		}

		if (needleLoop == size - 1)
		{
			return (&prmHaystack[haystackLoop]);
		}
	}

	return (NULL);
}

/**
 * _strtow - splits a string into words
 *
 * @prmString: char pointer
 * @prmSeparators: separators
 * @prmEscapeSeparators: escaping separators
 *
 * Return: word array
 */
char **_strtow(char *prmString, char *prmSeparators, char *prmEscapeSeparators)
{
	int cLoop = 0, cLoop1 = 0, wordSize = 0, word_number = 0, size = 0;
	char *word = NULL, **words = NULL, character;

	if (prmString == NULL)
		return (NULL);

	size = _strlen(prmString);
	word_number = _wordNumber(prmString, prmSeparators);

	if (prmString == NULL || !prmString || word_number == 0)
		return (NULL);

	words = _calloc(sizeof(char *), (word_number + 1));

	if (words == NULL)
		return (NULL);

	for (cLoop = 0; cLoop <= size && cLoop1 < word_number; cLoop++)
	{
		character = prmString[cLoop];
		if (_checkEscapeSeparators(character, prmEscapeSeparators))
			break;
		if (!_checkSeparators(character, prmSeparators))
			wordSize++;
		else
			if (wordSize > 0)
			{
				word = _getword(prmString, cLoop - wordSize, wordSize);
				_addWord(word, &cLoop1, words);
				wordSize = 0;
			}
	}
	words[cLoop1] = NULL;

	return (words);
}
