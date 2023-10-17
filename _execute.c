#include "main.h"
/**
 * _execute - execute the commands
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 * @envp: environmental pointer
 * @av: argument vector
 * @count: the counter
 * Return: -1 when execve fails
 *			0 otherwise
 */


int _execute(int span, char **cmds, char *input,
		char **envp, char **av, size_t count, int term_f)
{
	int status, flag = 0, cat = 1;
	pid_t pid;
	char *err_msg = NULL;


	flag = choose_mode(span, cmds, envp);
	if (flag && access(*cmds, F_OK))
		cat = !_path_cat(envp, cmds);
	if (flag && cat && !access(*cmds, F_OK))
	{
		pid = fork();
		if (pid == -1)
		{
			_frees_buff(span, cmds, input), perror("Error");
			return (EXIT_FAILURE); }
		else if (pid == 0)
		{
			execve(*cmds, cmds, envp);
			err_msg = _generate_error(cmds, av, count), errno = 127,
					perror(err_msg), free(err_msg);
			exit_handler(1, 0, span, cmds, envp, input); }
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error"), _frees_buff(span, cmds, input);
			return (EXIT_FAILURE); }
		if (WIFEXITED(status))
			_frees_buff(span, cmds, input);
	}
	else
	{
		if (errno)
		{
			if (errno == ENOENT)
				err_msg = _custom_err(_generate_error(cmds, av, count),
						"not found\n"), errno = 127, _put_error(err_msg), free(err_msg);
			else if (errno)
				err_msg = _generate_error(cmds, av, count), errno = 127,
						_put_error(err_msg), free(err_msg);

			errno = 127;
			if (!term_f)
				exit_handler(1, 0, span, cmds, envp, input);
		}
		_frees_buff(span, cmds, input);
	}

	return (EXIT_SUCCESS);
}



/**
 * choose_mode - chose the execution mode
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @envp: environmental pointer
 * Return: 1 when execve fails, 0 in success.
 */
int choose_mode(int span, char **cmds, char **envp)
{
	int i = 0, j = check_echo(cmds);
	_built builtins[] = {
		{"cd", cd_cmd}, {"$$", print_pid}, {"$?", print_err},
		{"env", print_envp}, {"setenv", _setenv_cmd},
		{"unsetenv", _unsetenv_cmd}, {"alias", alias},
		{NULL, NULL}};


	for (i = 0; builtins[i].cmd; i++)
	{
		if (!strcmp(cmds[j], builtins[i].cmd))
		{
			switch (i)
			{
				case 0:
					cd_cmd(span + 1, cmds, envp);
					return (EXIT_SUCCESS);
				case 1:
					print_pid(span, cmds, envp);
					return (0);
				case 2:
					print_err(span, cmds, envp);
					return (0);
				case 3:
					print_envp(span + 1, NULL, envp);
					return (0);
				case 4:
					_setenv_cmd(span + 1, cmds, envp);
					return (0);
				case 5:
					_unsetenv_cmd(span + 1, cmds, envp);
					return (0);
				case 6:
					alias(span, cmds, envp);
					return (0);
			}
		}
	}
	return (1);
}
/**
 * builtin_list - contiens the custom built-in cmds to be executed.
 * Return: return a list of that built-in cmds in _built data type.
 */
_built *builtin_list(void)
{
	static _built builtins[] = {
		{"cd", cd_cmd}, {"$$", print_pid}, {"$?", print_err},
		{"env", print_envp}, {"setenv", _setenv_cmd},
		{"unsetenv", _unsetenv_cmd}, {"alias", alias},
		{NULL, NULL}};
	return (builtins);
}
/**
 * check_echo - check if cmds is echo and is followed with $$ or $?
 * @cmds: array of tokens/commands
 * Return: 1 if it is followed woth $$ or $?, and 0 if not echo.
 */
int check_echo(char **cmds)
{
	int j = (!_strcmp(*cmds, "echo") &&
			(cmds[1] ?
			 ((!_strcmp(cmds[1], "$$") ^ !_strcmp(cmds[1], "$?")))
			 ? 1 : 0 : 0));
	return (j);
}
