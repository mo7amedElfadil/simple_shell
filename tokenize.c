#include "main.h"

/**
 * _tokenize - tokenize the input line
 * @term_f: terminal flag (isatty)
 * @envp: environmental pointer
 * @av: argument vector
 * @counter: the counter
 * Return: 1 when exit has been input
 *			0 otherwise
 */
int _tokenize(int term_f, char **envp, char **av, size_t counter)
{
	int line = 0, ret = 0;

	do {
		if (term_f)
			_put_buffer("($) ");

		ret = _tokenize_newline(&line, term_f, envp, av, counter);
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
 * Return: 1 when exit has been input
 *			0 otherwise
 */

int _tokenize_newline(int *line, int term_f,
		char **envp, char **av, size_t counter)
{
	int span = 0;
	size_t len = BUFF;
	char *input = malloc(len), **cmds = NULL;

	*line = getline(&input, &len, stdin);
	if (*line < 0 || !_strncmp(input, "exit", 4))
		exit_handler(*line, term_f, -1, cmds, envp, input, av, counter);
	cmds = _tokenize_n_al(*line, input, envp);
	span = cmds_n_elm(cmds);
	if (!term_f)
	{
		_execute(span, cmds, input, envp, av, counter, term_f);
		_tokenize(term_f, envp, av, counter);
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
	int i = 0, delimited = 0, flag = 0, del1, del2;
	char *token, *var, **cmds = malloc(8 * BUFF);

	del1 = _strcspn(input, " ");
	del2 = _strcspn(input, "\t");
	delimited = (del1 > del2) ? del2 : del1;
	token =  _strtok(input, " \t\r\n\v\f");
	if (!token)
	{
		_frees_buff(-1, cmds, input);
		return (NULL); }
	cmds[i] = malloc(_strlen(token) + 1), _strcpy(cmds[i], token);
	if (delimited < line)
	{
		while (cmds[i])
		{
			flag = 0, i++, token = _strtok(NULL, " \t\r\n\v\f");
			if (!token)
			{
				i--;
				break; }
			if (token[0] == '$')
			{
				var = var_expansion(token, envp);
				if (var)
					flag = 1; }
			if (flag)
				cmds[i] = malloc(_strlen(var) + 1), _strcpy(cmds[i], var), free(var);
			else
				cmds[i] = malloc(_strlen(token) + 1), _strcpy(cmds[i], token); }
	}
	cmds[i + 1] = NULL;
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
