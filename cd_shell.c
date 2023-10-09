#include "main.h"


/**
 * cd_cmd - execute the cd command.
 *
 * i have not decided which name and variables and return should be chosen.
 *
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: o if succeeded.
 */
int cd_cmd(int argc, char *argv[], char *envp[])
{
	int err_OPWD = 0, err_PWD = 0;
	char *en_v_OPWD = NULL, *en_v_PWD = NULL, *en_v_HOME = NULL;
	char *F_argv = *(argv + 1), *S_argv = *(argv + 2);

	errno = 0;
	en_v_PWD = get_envalue("PWD", envp, 3);
	en_v_OPWD = get_envalue("OLDPWD", envp, 6);
	if (argc == 3 && strcmp("cd", F_argv) == 0)
	{
		if (strcmp("-", S_argv) == 0)
		{
			if (chdir(en_v_OPWD) == -1)
				perror("Error");
			err_OPWD = setenv("PWD", en_v_OPWD, 1);
			if ((err_OPWD) == -1)
				perror("Error");
			err_PWD = setenv("OLDPWD", en_v_PWD, 1);
			if ((err_PWD) == -1)
				perror("Error");
		}
		else
			perror("Error");
	}
	else if (argc == 2)
	{
		en_v_HOME = get_envalue("HOME", envp, 4);

		if (chdir(en_v_HOME) == -1)
			perror("Error");
		err_OPWD = setenv("PWD", en_v_HOME, 1);
		if (err_OPWD == -1)
			perror("Error");
		err_PWD = setenv("OLDPWD", en_v_PWD, 1);
		if (err_PWD == -1)
			perror("Error");
	}
	else
		errno = EINVAL, perror("Error"), errno = 0;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable.
 * @var: the variable to set.
 * @envp: envirement variable.
 * Return: 0 if succeeded.
 */
int _unsetenv(char *var, char **envp)
{
	int i, j;

	for (i = 0; envp[i]; i++)
	{
		if (_strncmp(envp[i], var, _strlen(var)) == 0 && envp[i][_strlen(var)] == '=')
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
 * Return: 0 if succeeded.
 */
int _setenv(char *var, char *val, int owr, char **envp)
{
	int i;
	char *new_var = NULL, **new_envp = NULL;

	for (i = 0; envp[i]; i++)
	{
		if (_strncmp(envp[i], var, _strlen(var)) == 0 && envp[i][_strlen(var)] == '=')
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
 * Return: pointer the value.
 */
char *get_envalue(char *var, char **envp, int len)
{
	char *token = NULL;
	int i = 0;

	while (_strncmp(envp[i], var, len) != 0)
		i++;
	if (envp[i])
	{
		token = strtok(envp[i], "=");
		token = strtok(NULL, "=");
	}
	return (token);
}
/**
 * cd_cmd_dd - dd
 * en_v_PWD: pwd
 * Return: path
 */
char *cd_cmd_dd(char *en_v_PWD)
{
	int x = _strlen(en_v_PWD), i = 0;
	x--;
	do
	{
		if (!i && en_v_PWD[x - i] == '/')
			en_v_PWD[x - i] = 0, i++;
		else
			en_v_PWD[x - i] = 0;
		i++;
	} while ( i < x && en_v_PWD[x - i] != '/');
	en_v_PWD[x - i] = 0;
	return (en_v_PWD);
}
