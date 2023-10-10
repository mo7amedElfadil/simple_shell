#include "main.h"

/**
 * setenv_cmd - Initialize a new environment variable, modify an existing one.
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _setenv_cmd(int argc, char **argv, char **envp)
{
	if (argc == 3)
	{
		_setenv(argv[1], argv[2], 1, envp);
		return (0);
	}
	else
		errno = EINVAL, perror("Error"), errno = 0;
	return (-1);
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
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 if in failure.
 */
int _setenv(char *var, char *val, int owr, char **envp)
{
	int i, len = _strlen(var);
	char *new_var = NULL, **new_envp = NULL;

	for (i = 0; envp[i]; i++)
	{
		if (_strncmp(envp[i], var, len) == 0 && envp[i][_strlen(var)] == '=')
		{
			if (!owr)
				return (0);
			new_var = malloc(_strlen(var) + _strlen(val) + 2);
			if (!new_var)
				return (-1);

			_strcpy(new_var, var), _strcat(new_var, "="), _strcat(new_var, val);
			envp[i] = new_var;
			return (0);
		}
	}

	new_var = malloc(_strlen(var) + _strlen(val) + 2);
	if (!new_var)
		return (-1);
	_strcpy(new_var, var), _strcat(new_var, "="), _strcat(new_var, val);

	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
	{
		free(new_var);
		return (-1);
	}
	for (i = 0; envp[i]; i++)
		new_envp[i] = envp[i];

	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	return (0);
}

/**
 * get_envalue - get the value of envirement variable.
 *
 * NOTE: we use this function only if we are sure the var exist in envp.
 *
 * @var: the variable name we search for.
 * @len: lent of the name of the env variable.
 * @envp: envirement variable.
 * Return: pointer the value, or NULL if allocation failed.
 */
char *get_envalue(char *var, char **envp, int len)
{
	char *token = NULL, *envp_tem = NULL;
	int i = 0;

	while (_strncmp(envp[i], var, len) != 0)
		i++;
	if (envp[i])
	{
		envp_tem = malloc(sizeof(char) * (_strlen(envp[i] + 1)));
		if (envp_tem)
			return (NULL);
		_strcpy(envp_tem, envp[i]);
		token = strtok(envp_tem, "=");
		token = strtok(NULL, "=");
	}
	return (token);
}

