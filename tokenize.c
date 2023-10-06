#include "main.h"

/**
 * _tokenize - tokenize the input line
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * Return: 1 when exit has been input
 *			0 otherwise
 */
int _tokenize(int term_f, char **envp)
{
	int i = 0;
	size_t len = 120, l = 0, x = 0;
	char *input = malloc(len), *token;
	char **cmds = malloc(sizeof(*cmds) * 10);

	(void)term_f;
	l = getline(&input, &len, stdin);
	if (!strncmp(input, "exit", 4))
	{
		free(input), free(cmds);
		return (-1);
	}
	x = strcspn(input, " ");
	cmds[i] = malloc(10);
	token =  strtok(input, " \t\r\n\v\f");
	_strcpy(cmds[i], token);
	if (x < l)
	{
		while (cmds[i])
		{
			i++;
			token = strtok(NULL, " \t\r\n\v\f");
			if (!token)
			{
				i--;
				break;
			}
			cmds[i] = malloc(10);
			_strcpy(cmds[i], token);
		}
	}
	cmds[i + 1] = NULL;
	return (_execute(i, cmds, input, envp));
}
/**
 * _execute - execute the commands
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 * @envp: environmental pointer
 * Return: -1 when execve fails
 *			0 otherwise
 */

int _execute(int span, char **cmds, char *input, char **envp)
{
	int status;
	pid_t pid;
	char *err_msg = NULL;
	(void)err_msg;

	pid = fork();
	if (pid == -1)
	{
		_frees_buff(span, cmds, input);
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(*cmds, cmds, envp);
		perror(_generate_error(cmds, span));
		_frees_buff(span, cmds, input);
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error");
		_frees_buff(span, cmds, input);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		_frees_buff(span, cmds, input);
	return (EXIT_SUCCESS);
}

/**
 * generate_error - generate error message
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * Return:
 * */
char *_generate_error(char **cmds, int span)
{
	char *err_msg = malloc(100);

	strcpy(err_msg, cmds[0]);
	strcat(err_msg, ": ");
	strcat(err_msg, _itoa(span));
	return (err_msg);
}
