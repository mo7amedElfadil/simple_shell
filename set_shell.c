#include "main.h"

/**
 * _setenv_cmd - Initialize a new environment variable, modify an existing one.
 * using command line inside the simple shell.
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _setenv_cmd(int argc, char **argv, char **envp)
{
	argc = 0;

	while (argv[argc])
		argc++;
	if (argc == 3)
	{
		if (_setenv(argv[1], argv[2], 1, envp) == -1)
			return (-1);
	}
	else if (argc == 2)
	{
		if (_setenv(argv[1], "\0", 1, envp) == -1)
			return (-1);
	}
	else
	{
		/* errno = EINVAL, perror("Error"), errno = 0; */
		return (-1);
	}
	return (0);
}
/**
 * _unsetenv_cmd - Remove an environment variable.
 * using command line inside the simple shell.
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _unsetenv_cmd(int argc, char **argv, char **envp)
{
	argc = 0;

	while (argv[argc])
		argc++;
	if (argc == 2)
	{
		if (_unsetenv(argv[1], envp) == -1)
		{
			/* printf("cannot unset the variable\n"); */
			return (-1);
		}
	}
	else
	{
		/* errno = EINVAL, perror("Error"), errno = 0; */
		return (-1);
	}
	return (0);
}


/**
 * _unsetenv - Remove an environment variable.
 * @var: the variable to set.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _unsetenv(char *var, char **envp)
{
	int i, j, len = _strlen(var);

	for (i = 0; envp[i]; i++)
	{
		if (_strncmp(envp[i], var, len) == 0 && envp[i][_strlen(var)] == '=')
		{
			free(envp[i]);
			for (j = i; envp[j]; j++)
				envp[j] = envp[j + 1];
			return (0);
		}
	}
	return (-1);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one.
 * @var: the variable to set.
 * @val: it value.
 * @owr: 1 to overwrite it, 0 creat if only does not exist.
 * @en: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _setenv(char *var, char *val, int owr, char **en)
{
	int i, len = _strlen(var);

	for (i = 0; en[i]; i++)
	{
		if (_strncmp(en[i], var, len) == 0 && en[i][len] == '=')
		{
			if (!owr)
				return (0);
			/* errno set to 0*/
			en[i] = _realloc(en[i], _strlen(en[i]) + 1, len + _strlen(val) + 2);
			/* errno = 0; */
			if (!en[i])
			{
				/* perror("Error"); */
				return (-1); }
			_strcpy(en[i], var), _strcat(en[i], "="), _strcat(en[i], val);
			return (0); }
	}
	if (!en)
	{
		/* perror("Error"); */
		return (-1); }
	en[i] = malloc(_strlen(var) + _strlen(val) + 2);
	if (!en[i])
	{
		/* perror("Error"); */
		return (-1); }
	_strcpy(en[i], var), _strcat(en[i], "="), _strcat(en[i], val);
	en[i + 1] = NULL;
	return (0);
}

/**
 * get_envalue - get the value of envirement variable.
 *
 * NOTE: we use this function only if we are sure the var exist in envp.
 *
 * @var: the variable name we search for.
 * @len: lent of the name of the env variable.
 * @envp: envirement variab	le.
 * Return: pointer the value, or NULL if allocation failed.
 */
char *get_envalue(char *var, char **envp, int len)
{
	char *token = NULL, *envp_tem = NULL;
	int i = 0;

	while (envp[i] && strncmp(envp[i], var, len) != 0)
		i++;
	if (envp[i])
	{
		char *result = NULL;

		envp_tem = malloc(sizeof(char) * (_strlen(envp[i]) + 1));
		if (!envp_tem)
		{
			return (NULL);
		}
		_strcpy(envp_tem, envp[i]);
		strtok(envp_tem, "=");
		token = strtok(NULL, "=");
		result = malloc(_strlen(token) + 1);
		_strcpy(result, token);
		free(envp_tem);
		return (result);
	}
	return (NULL);
}

