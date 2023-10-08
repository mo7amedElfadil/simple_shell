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
	int i = 0, err_OPWD = 0, err_PWD = 0;
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
		errno = EINVAL, perror("Error");
	return (0);
}


/**
 * get_envalue - get the value of envirement variable.
 * @var: the variable name we search for.
 * @len: lent of the name of the env variable.
 * @envp: envirement variable.
 * Return: pointer the value.
 */
char *get_envalue(char *var, char **envp, int len)
{
	char *token = NULL;
	int i = 0;

	while (strncmp(envp[i], var, len) != 0)
		i++;

	token = strtok(envp[i], "=");
	token = strtok(NULL, "=");
	return (token);
}

