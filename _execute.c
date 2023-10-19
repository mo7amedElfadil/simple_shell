#include "main.h"
/**
 * _execute - execute the commands
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 * @envp: environmental pointer
 * @av: argument vector
 * @count: the counter
 * @term_f: from issaty, 1 for interactive mode, 0 if not.
 * Return: -1 when execve fails
 *			0 otherwise
 */


int _execute(int span, char **cmds, char *input,
		char **envp, char **av, size_t count, int term_f)
{
	int status, flag = 0, cat = 1;
	pid_t pid;
	char *err_msg = NULL;

	if (!cmds || is_nulled(cmds))
	{
		_frees_buff(span, cmds, input);
		return (EXIT_FAILURE);
	}
	flag = choose_mode(span, cmds, envp);
	if (flag && access(*cmds, F_OK))
		cat = !(_path_cat(envp, cmds));
	if (flag && cat && !access(*cmds, F_OK))
	{
		pid = fork();
		return (exec_fork(pid, &status, err_msg,
					span, cmds, envp, input, av, count));
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
				exit_handler(1, 0, span, cmds, envp, input, av, count);
		}
		_frees_buff(span, cmds, input);
	}

	return (EXIT_SUCCESS);
}

/**
 * exec_fork - Handles the forked process.
 * @pid: process id.
 * @status: exit status of child process.
 * @err_msg: error message
 * @span: indix of last elements in cmds.
 * @cmds: array of tokens/commands.
 * @envp: environmental pointer
 * @input: input string from getline().
 * @av: argv.
 * @count: count how many cmd has been executed.
 * Return: exit 0 on success.
 */
int exec_fork(pid_t pid, int *status, char *err_msg, int span, char **cmds,
		char **envp, char *input, char **av, size_t count)
{
		if (pid == -1)
		{
			_frees_buff(span, cmds, input), perror("Error");
			return (EXIT_FAILURE); }
		else if (pid == 0)
		{
			execve(*cmds, cmds, envp);
			err_msg = _generate_error(cmds, av, count), errno = 127,
					perror(err_msg), free(err_msg);
			exit_handler(1, 0, span, cmds, envp, input, av, count); }
		if (waitpid(pid, status, 0) == -1)
		{
			perror("Error"), _frees_buff(span, cmds, input);
			return (EXIT_FAILURE); }
		if (WIFEXITED(*status))
			_frees_buff(span, cmds, input), errno = (*status / 256);
					return (0);
}

/**
 * check_echo - check if cmds is echo and is followed with $$ or $?
 * @cmds: array of tokens/commands
 * Return: 1 if it is followed woth $$ or $?, and 0 if not echo.
 */
int check_echo(char **cmds)
{
	int j = (!_strncmp(*cmds, "echo", 4) &&
			(cmds[1] ?
			 ((!_strncmp(cmds[1], "$$", 2) ^ !_strncmp(cmds[1], "$?", 2)))
			 ? 1 : 0 : 0));
	return (j);
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
		{"unsetenv", _unsetenv_cmd}, {"alias", alias}, {NULL, NULL}};

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
