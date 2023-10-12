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
	char *en_v_OPWD = NULL, *en_v_PWD = NULL, *en_v_HOME = NULL;
	char *F_argv = argv[0], *S_argv = argv[1];

	errno = 0;
	en_v_PWD = get_envalue("PWD", envp, 3);
	en_v_OPWD = get_envalue("OLDPWD", envp, 6);
	if (argc == 2 && strcmp("cd", F_argv) == 0)
	{
		if (_strcmp("-", S_argv) == 0)
		{
			if (chdir(en_v_OPWD) == -1)
			{
				perror("Error");
				return (-1);
			}
			else
			{
				if (_setenv("PWD", en_v_OPWD, 1, envp) == -1)
				{
					perror("Error");
					return (-1);
				}

				if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
				{
					perror("Error");
					return (-1);
				}
				print_envp(envp, "PWD");
			}
			return (0);
		}
		else if (_strcmp("..", S_argv) == 0)
		{
			if (chdir(en_v_OPWD) == -1)
			{
				perror("Error");
				return (-1);
			}
			else
			{
				if (_setenv("PWD", cd_cmd_dd(en_v_PWD), 1, envp) == -1)
				{
					perror("Error");
					return (-1);
				}
				if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
				{
					perror("Error");
					return (-1);
				}
			}
		}
		/*I'm not sure about this, maybe we should add && _strlen(S_argv) == 1*/
		else if (_strcmp(".", S_argv) == 0)
			;
		else
			errno = ENOENT, perror("Error"), errno = 0; /*No such file or directory*/
	}
	else if (argc == 1 && strcmp("cd", F_argv) == 0)
	{
		en_v_HOME = get_envalue("HOME", envp, 4);
		if (chdir(en_v_HOME) == 0)
		{
			if (_setenv("PWD", en_v_HOME, 1, envp) == -1)
			{
				perror("Error");
				return (-1);
			}

			if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
			{
				perror("Error");
				return (-1);
			}
			return (0);
		}
		else
		{
			perror("Error");
			return (-1);
		}
	}
	else
	{
		errno = EINVAL, perror("Error"), errno = 0;
		return (-1);
	}
	return (0);
}
/**
 * set_pwd_opwd - set and update the PWD and OPWD values.
 * @target: the target path to be the new PWD.
 * @previous: the old PWD to be the new OLDPWD.
 * @envp: envirement variable.
 * @printPWD: 0 for not printing the new PWD, any value to do so.
 * Return: 0 if succeeded, -1 in case of failure.
 */

int set_pwd_opwd(char *target, char *previous, char **envp, int printPWD)
{
	if (!printPWD)
	{
		if (_setenv("PWD", target, 1, envp) == -1)
		{
			perror("Error");
			return (-1);
		}

		if (_setenv("OLDPWD", previous, 1, envp) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	else
		print_envp(envp, target);
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
	int i = 0, a = 0, len;

	if (envp == NULL || *envp == NULL)
	{
		printf("envp is null");
		return;
	}
	if (var == NULL)
		a = 1;
	else
		len = _strlen(var);
	while (envp[i])
		if (a)
			printf("%s\n", envp[i]), i++, printf("------>");
		else
		{
			if (_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			{
				_put_buffer(&envp[i][len + 1]);
				_put_buffer("\n");
				break;
			}
			i++;
		}
}
