#include "main.h"

/**
 * _tokenize - tokenize the input line
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * @av: argument vector
 * @count: the counter.
 * @ac: arg counter from main.
 * @s: file stream
 * @fd: file descriptor
 * Return: 1 when exit has been input
 *			0 otherwise
 */
int _tokenize(int term_f, char **envp, char **av,
		size_t count, int ac, FILE *s, int fd)
{
	int line = 0, ret = 0;

	if (ac == 2)
	{
		term_f = 0;
	}
	do {
		if (term_f)
			_put_buffer("($) ");
		errno = 0;
		ret = _tokenize_newline(&line, term_f, envp, av, count, ac, s, fd);
		count++;
	} while (line > 0);
	return (ret);
}


/**
 * _tokenize_newline - tokenization of input. Made to be looped
 * @line: length of line from getline
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * @av: argument vector
 * @counter: the counter
 * @ac: arg counter from main.
 * @s: file stream
 * @fd: file descriptor
 * Return: 1 when exit has been input
 *			0 otherwise
 */

int _tokenize_newline(int *line, int term_f, char **envp,
		char **av, size_t counter, int ac, FILE *s, int fd)
{
	int span = 0;
	size_t len = BUFF;
	char *input = malloc(len), **cmds = NULL;

	if (ac == 2 && s && fd)
	{
		*line = getline(&input, &len, s);
		term_f = 0;
		errno = 0;
	}
	else
		*line = getline(&input, &len, stdin);
	if (*line < 0 || !_strncmp(input, "exit", 4))
	{
		if (fd)
			fclose(s);
		exit_handler(*line, term_f, -1, cmds, envp, input, av, counter);
	}
	cmds = _tokenize_n_al(*line, input, envp);
	span = cmds_n_elm(cmds);
	if (!term_f)
	{
		_execute(span, cmds, input, envp, av, counter, term_f);
		_tokenize(term_f, envp, av, counter, ac, s, fd);
		exit_handler(1, 0, 0, NULL, NULL, NULL, av, counter);
	}
	return (_execute(span, cmds, input, envp, av, counter, term_f));
}

/**
 * _tokenize_n_al - tokenize the input line for the non alias cmds.
 * @line: the lenght of line readen by getline.
 * @input: the string returned from getline.
 * @envp: environmental pointer
 * Return: array of strings (commands).
 */
char **_tokenize_n_al(int line, char *input, char **envp)
{
	int i = 0, delim = 0, flag = 0, del1, del2;
	char *token, *var, **cmds = malloc(8 * BUFF);

	del1 = _strcspn(input, " "), del2 = _strcspn(input, "\t");
	delim = (del1 > del2) ? del2 : del1, token =  _strtok(input, " \t\r\n\v\f");
	if (!token)
	{	_frees_buff(-1, cmds, NULL);
		return (NULL); }
	if (!comment(token))
	{	free(cmds);
		return (NULL);	}
	if (token[0] == '$')
	{
		var = var_expansion(token, envp);
		flag = var ? 1 : 0; }
	cmds[i] = (flag ? malloc(_strlen(var) + 1) : malloc(_strlen(token) + 1));
	(flag ? _strcpy(cmds[i], var) : _strcpy(cmds[i], token));
	(flag ? free(var) : (void) 0), flag = 0;
	if (delim < line)
	{
		while (cmds[i])
		{
			flag = 0, i++, token = _strtok(NULL, " \t\r\n\v\f");
			if (!token)
			{
				i--;
				break; }
			if (!comment(token))
			{	cmds[i] = 0;
				break;	}
			if (token[0] == '$')
			{
				var = var_expansion(token, envp);
				flag = var ? 1 : 0; }
			cmds[i] = (flag ? malloc(_strlen(var) + 1) : malloc(_strlen(token) + 1));
			(flag ? _strcpy(cmds[i], var) : _strcpy(cmds[i], token));
			(flag ? free(var) : (void) 0); }
	} cmds[i + 1] = NULL;
	return (cmds);
}
/**
 * var_expansion - expand shell variables
 * @var: token
 * @envp: envirement pointer
 * Return: the expanded variable or null
 */
char *var_expansion(char *var, char **envp)
{
	if (var && var[0] == '$' && (var[1] == '_' || _isalpha(var[1])))
	{
		char *env = malloc(_strlen(var) + 1), *result = NULL;

		_strcpy(env, var);
		env = cut_prefix(env, 1);
		result = get_envalue(env, envp, _strlen(env)), free(env);
		if (!result)
			result = malloc(2), *result = 0;

		return (result);
	}

	return (0);
}

/**
 * cmds_n_elm - calculate the (number of tokens - 1) or index of last token.
 * @cmds: array of cmd after tokenization.
 * Return: index of last token.
 */
int cmds_n_elm(char **cmds)
{
	int i = 0;

	if (!cmds)
		return (0);
	while (*cmds)
		cmds++, i++;
	return (i - 1);
}
