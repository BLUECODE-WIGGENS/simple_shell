#include "shell.h"

/**
 * _unsetEnvironment - unset environment variable
 *
 * @prmData: data's structure
 */
void _unsetEnvironment(appData_t *prmData)
{
	if (prmData == NULL)
		return;

	if (prmData->arguments == NULL)
		return;

	if (prmData->arguments[1] == NULL)
		return;

	_unsetenv(prmData, prmData->arguments[1]);
}

/**
 * _setenv - set environment value
 *
 * @prmEnviron: environment linked list
 * @prmName: environment name
 * @prmValue: environment value
 * @prmOverwrite: overwrite
 */
void _setenv(
	environment_t *prmEnviron,
	char *prmName,
	char *prmValue,
	int prmOverwrite
) {
	environment_t *envNode;
	char *tmp;

	if (prmName == NULL || prmValue == NULL)
		return;

	envNode = _getenv(prmEnviron, prmName);

	if (envNode == NULL)
	{
		tmp = _generateEnvGlobal(prmName, prmValue);
		_addEnvNodeEnd(&prmEnviron, tmp);
		free(tmp);
	}
	else if (prmOverwrite == 1)
	{
		free(envNode->value);
		envNode->value = _strdup(prmValue);
	}
}

/**
 * _deleteEnvNode - delete an environment variable
 *
 * @prmHead: first node
 * @prmName: name
 *
 * Return: error code
 */
int _deleteEnvNode(environment_t *prmHead, char *prmName)
{
	environment_t *beforeNode, *afterNode, *currentNode, *firstNode;
	unsigned int length, currentIndex;

	firstNode = prmHead;
	currentIndex = _getEnvIndex(prmHead, prmName);

	if (firstNode == NULL)
		return (-1);

	length = _listEnvLen(firstNode);

	if (length == 0 || currentIndex > (unsigned int) length - 1)
		return (-1);

	if (currentIndex == 0)
	{
		prmHead = prmHead->next;
		free(firstNode);
		return (1);
	}

	beforeNode = _getEnvNodeAtIndex(firstNode, currentIndex - 1);
	if (currentIndex == length - 1)
		afterNode = NULL;
	else
		afterNode = _getEnvNodeAtIndex(firstNode, currentIndex + 1);

	currentNode = _getEnvNodeAtIndex(firstNode, currentIndex);
	beforeNode->next = afterNode;
	free(currentNode->name);
	currentNode->name = NULL;
	free(currentNode->value);
	currentNode->value = NULL;
	free(currentNode->global);
	currentNode->global = NULL;
	free(currentNode);
	currentNode = NULL;

	return (1);
}

/**
 * _getEnvNodeAtIndex - the nth node of a listint_t linked list
 *
 * @prmHead: first element
 * @prmIndex: element's number
 *
 * Return: a node
 */
environment_t *_getEnvNodeAtIndex(
	environment_t *prmHead,
	unsigned int prmIndex
) {
	unsigned int cLoop = 0;

	while (prmHead != NULL)
	{
		if (prmIndex == cLoop)
			return (prmHead);
		prmHead = prmHead->next;
		cLoop++;
	}

	return (NULL);
}

/**
 * _getEnvIndex - return index of an environment variable
 *
 * @prmHead: first node
 * @prmName: name
 *
 * Return: index
 */
int _getEnvIndex(environment_t *prmHead, char *prmName)
{
	if (prmHead == NULL || _strcmp(prmHead->name, prmName) == 0)
		return (0);
	else
		return (_getEnvIndex(prmHead->next, prmName) + 1);
}
