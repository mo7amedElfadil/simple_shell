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
	char *en_v_OPWD = NULL, *en_v_PWD = NULL, *en_v_HOME = NULL;
	char *F_argv = argv[0], *S_argv = argv[1];

	errno = 0, en_v_PWD = get_envalue("PWD", envp, 3); /* errno set to 0*/
	en_v_OPWD = get_envalue("OLDPWD", envp, 6);
	if (argc == 2 && strcmp("cd", F_argv) == 0)
	{
		if (_strcmp("-", S_argv) == 0)
		{
			if (!en_v_OPWD)
				en_v_OPWD = get_envalue("PWD", envp, 3);
			if (cd_cmd__(en_v_OPWD, en_v_PWD, envp) == -1)
				return (-1); }
		else if (_strcmp("..", S_argv) == 0)
		{
			if (cd_cmd_par(en_v_PWD, envp) == -1)
				return (-1); }
		else if (_strcmp(".", S_argv) == 0)
		{
			if (_setenv("OLDPWD", en_v_PWD, 1, envp) == -1)
				return (-1); }
		else if (is_v_path(S_argv))
		{
			if (cd_cmd_sup(S_argv, en_v_PWD, envp) == -1)
				return (-1); }
		else /*No such file or directory*/
		{errno = ENOENT, perror("Error"), errno = 0; /*errno re-set to 0*/
			return (-1); }
	}
	else if (argc == 1 && strcmp("cd", F_argv) == 0)
	{en_v_HOME = get_envalue("HOME", envp, 4);
		if (cd_cmd_sup(en_v_HOME, en_v_PWD, envp) == -1)
			return (-1); }
	else
	{errno = EINVAL, perror("Error"), errno = 0;
		return (-1); }
	_free_cd(3, en_v_PWD, en_v_OPWD, en_v_HOME);
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
