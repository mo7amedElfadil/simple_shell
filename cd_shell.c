#include "main.h"


/**
 * cd_cmd - execute the cd command.
 *
 * i have not decided which name and variables and return should be chosen.
 *
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: 0 if succeeded.
 */
int cd_cmd(int argc, char *argv[], char *envp[])
{
	int err_OPWD = 0, err_PWD = 0;
	char *en_v_OPWD = NULL, *en_v_PWD = NULL, *en_v_HOME = NULL, *en_v_tem = NULL;
	char *F_argv = *(argv + 1), *S_argv = *(argv + 2);

	errno = 0;
	en_v_PWD = get_envalue("PWD", envp, 3);
	en_v_OPWD = get_envalue("OLDPWD", envp, 6);
	if (argc == 3 && strcmp("cd", F_argv) == 0)
	{
		if (_strcmp("-", S_argv) == 0)
		{
			if (chdir(en_v_OPWD) == -1)
				perror("Error");
			else
			{
				if (_setenv("PWD", en_v_OPWD, 1, envp) == -1)
					perror("Error");

				if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
					perror("Error");
				print_envp(envp, en_v_OPWD);
			}
		}
		else if (_strcmp("..", S_argv) == 0)
		{
			if (_setenv("PWD", cd_cmd_dd(en_v_PWD), 1, envp) == -1)
				perror("Error");

			if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
				perror("Error");
		}
		/*I'm not sure about this, maybe we should add && _strlen(S_argv) == 1*/
		else if (_strcmp(".", S_argv) == 0)
			;
		else
			errno = ENOENT, perror("Error"), errno = 0; /*No such file or directory*/
	}
	else if (argc == 2)
	{
		en_v_HOME = get_envalue("HOME", envp, 4);

		if (chdir(en_v_HOME) == -1)
			perror("Error");
		else
		{
			if (_setenv("PWD", en_v_HOME, 1, envp) == -1)
				perror("Error");

			if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
				perror("Error");
		}
	}
	else
		errno = EINVAL, perror("Error"), errno = 0;
	return (0);
}

/**
 * cd_cmd_dd - get the parent directory's path.
 * @en_v_PWD: present working directory's path.
 * Return: parent's path.
 */
char *cd_cmd_dd(char *en_v_PWD)
{
	int x = _strlen(en_v_PWD), i = 0;

	x--;
	do {
		if (!i && en_v_PWD[x - i] == '/')
			en_v_PWD[x - i] = 0, i++;
		else
			en_v_PWD[x - i] = 0;
		i++;
	} while (i < x && en_v_PWD[x - i] != '/');
	en_v_PWD[x - i] = 0;
	return (en_v_PWD);
}


/**
 * print_envp - print the envirement variable's list.
 * @envp: envirement variable's array of strings.
 * @var: if NULL, print the envp list. if not, print the value of this var.
 *
 * for the env built-in cmd, we set var == null.
 *
 * Return: NONE.
 */
void print_envp(char **envp, char *var)
{
	int j, i = 0, a = 0, len = _strlen(var);

	if (val == NULL)
		a = 1;
	while (envp[i])
		if (a)
			printf("%s\n", envp[i]), i++;
		else
		{
			if (_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			{
				j = len + 1;
				while (envp[i][j])
					_put_buff(envp[i][len]), j++;
				_put_buff('\n');
				break;
			}
			i++;
		}
}
