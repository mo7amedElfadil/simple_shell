#include "main.h"


/**
 * cd_cmd - execute the cd command.
 * @argc: tem for number of argument.
 * @argv: temporary variable for tokens.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 in case of failure.
 */
int cd_cmd(int argc, char *argv[], char *envp[])
{
	char *OPWD = NULL, *PWD = NULL, *HOME = NULL;
	char *F_argv = argv[0], *S_argv = argv[1];
	int a = 0;

	errno = 0, PWD = get_envalue("PWD", envp, 3); /* errno set to 0*/
	OPWD = get_envalue("OLDPWD", envp, 6);
	if (argc == 2 && strcmp("cd", F_argv) == 0)
	{
		if (_strcmp("-", S_argv) == 0)
		{
			if (!OPWD)
				OPWD = get_envalue("PWD", envp, 3), a = 1;
			if (cd_cmd__(OPWD, PWD, envp, a) == -1)
				return (-1); }
		else if (_strcmp("..", S_argv) == 0)
		{
			if (cd_cmd_par(PWD, envp) == -1)
				return (-1); }
		else if (_strcmp(".", S_argv) == 0)
		{
			if (_setenv("OLDPWD", PWD, 1, envp) == -1)
				return (-1); }
		else if (is_v_path(S_argv))
		{
			if (cd_cmd_sup(S_argv, PWD, envp) == -1)
				return (-1); }
		else /*No such file or directory*/
		{errno = ENOENT, perror("Error"), errno = 0, _free_cd(3, PWD, OPWD, HOME);
			return (-1); }
	}
	else if (argc == 1 && strcmp("cd", F_argv) == 0)
	{HOME = get_envalue("HOME", envp, 4);
		if (cd_cmd_sup(HOME, PWD, envp) == -1)
			return (-1); }
	else
	{errno = EINVAL, perror("Error"), errno = 0;
	_free_cd(3, PWD, OPWD, HOME);
		return (-1); }
	a == 0 ? _free_cd(3, PWD, OPWD, HOME) : _free_cd(2, PWD, HOME);
	return (0);
}
/**
 * cd_cmd_dd - get the parent directory's path.
 * @PWD: present working directory's path.
 * Return: parent's path.
 */
char *cd_cmd_dd(char *PWD)
{
	int x = _strlen(PWD), i = 0;

	x--;
	do {
		if (!i && PWD[x - i] == '/')
			PWD[x - i] = 0, i++;
		else
			PWD[x - i] = 0;
		i++;
	} while (i < x && PWD[x - i] != '/');
	PWD[x - i] = 0;
	return (PWD);
}


/**
 * print_envp - print the envirement variable's list.
 * @envp: envirement variable's array of strings.
 * @var: if NULL, print the envp list. if not, print the value of this var.
 * @span: counter
 *
 * for the env built-in cmd, we set var == null.
 *
 * Return: NONE.
 */
int print_envp(int span, char **var, char **envp)
{
	int i = 0, a = 0, len;

	make_void(1, span);
	if (envp == NULL || *envp == NULL)
		return (1);
	if (var == NULL)
		a = 1;
	else
		len = _strlen(*var);
	while (envp[i])
		if (a)
		{
			_put_buffer(envp[i]);
			_put_buffer("\n");
			i++;
		}
		else
		{
			if (_strncmp(envp[i], *var, len) == 0 && envp[i][len] == '=')
			{
				_put_buffer(&envp[i][len + 1]);
				_put_buffer("\n");
				break;
			}
			i++;
		}
	return (0);
}
