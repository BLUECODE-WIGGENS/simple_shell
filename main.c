#include "shell.h"

int main(int argc __attribute__((unused)), char **argv)
{
	appData_t *appData = NULL;
	int cLoop;
	void (*func)(appData_t *);

	appData = _initData(argv);

	do {
		signal(SIGINT, _ctrlC);
		_prompt();

		_getline(appData);

		appData->history = _strtow(appData->buffer, COMMAND_SEPARATOR, ESCAPE_SEPARATOR);

		if (appData->history == NULL)
		{
			_freeAppData(appData);
			free(appData);
			continue;

		}

		for (cLoop = 0; appData->history[cLoop] != NULL; cLoop++)
		{
			appData->arguments = _strtow(appData->history[cLoop], SEPARATORS, ESCAPE_SEPARATOR);

			if (appData->arguments == NULL)
			{
				_freeAppData(appData);
				_freeEnvList(appData->env);
				appData->env = NULL;
				free(appData);
				appData = NULL;
				break;
			}

			appData->commandName = _strdup(appData->arguments[0]);

			if (appData->commandName != NULL)
			{
				func = _getCustomFunction(appData->commandName);
				if (func != NULL)
					func(appData);
				else
					_execCommand(appData);
			}
			_freeCharDoublePointer(appData->arguments);
			appData->arguments = NULL;
			free(appData->commandName);
			appData->commandName = NULL;
		}

		_freeAppData(appData);
	} while (1);
	return (EXIT_SUCCESS);
}

/**
 * _getline - Return command line type by user
 *
 * @prmData: data structure
 *
 * Return: buffer
 */
void _getline(appData_t *prmData)
{
	char c = '\0';
	int i = 0, rd, bufferSize = BUFFER_SIZE;

	prmData->buffer = _calloc(sizeof(char), BUFFER_SIZE);

	while (c != '\n' && c != EOF)
	{
		rd = read(STDIN_FILENO, &c, 1);

		if (rd == 0)
		{
			_putchar('\n');
			if (prmData->env != NULL)
				_freeEnvList(prmData->env);
			prmData->env = NULL;
			_freeAppData(prmData);
			free(prmData);
			exit(EXIT_SUCCESS);
		}

		if (i >= bufferSize - 1)
		{
			prmData->buffer = _realloc(
				prmData->buffer,
				bufferSize,
				sizeof(char) * (i + 2)
			);
			bufferSize = i + 2;
		}
		prmData->buffer[i] = c;
		i++;
	}
	prmData->buffer[i] = '\0';
}

/**
 * _getCustomFunction - check custom command
 *
 * @prmCommand: command
 *
 * Return: pointer function
 */
void (*_getCustomFunction(char *prmCommand))(appData_t *)
{
	int i = 0;

	customCommand_t fp[] = {
		{"cd", _changeDirectory},
		{"env", _env},
		{"setenv", _setEnvironment},
		{"unsetenv", _unsetEnvironment},
		{"exit", _exitStatus},
		{"help", _help}
	};

	while (i < 6)
	{
		if (_strcmp(prmCommand, (fp + i)->commandName) == 0)
			return ((fp + i)->func);
		i++;
	}

	return (NULL);
}


/**
 * _execCommand - Execute a command
 *
 * @prmData: app data array
 */
void _execCommand(appData_t *prmData)
{
	pid_t child_pid;
	char *command;
	int status;

	if (prmData->commandName == NULL)
		return;

	/* Get the absolute path of the command */
	command = _which(prmData);

	if (command != NULL)
	{
		if (prmData->commandName != command)
			free(prmData->commandName);
		prmData->commandName = command;
	}
	else
	{
		return;
	}

	/* Create a child */
	child_pid = fork();
	if (child_pid == 0)
	{
		/* Execute command*/
		if (execve(prmData->commandName, prmData->arguments, NULL) == -1)
			_errorHandler(prmData, 103);
		return;
	}
	else if (child_pid == -1)
	{
		_errorHandler(prmData, 102);
	}

	else
		waitpid(child_pid, &status, WUNTRACED);
}
