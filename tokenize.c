#include "main.h"
#include <ctype.h>

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
	int i = 0, line = 0, delimited = 0, flag = 0;
	size_t len = BUFF;
	char *input = malloc(len), *token, *var, **cmds = malloc(8 * BUFF);

	line = getline(&input, &len, stdin);
	if (line < 0 || !_strncmp(input, "exit", 4))
		exit_handler(line, term_f, -1, cmds, envp, input, av, counter);
	delimited = _strcspn(input, " "), token =  _strtok(input, " \t\r\n\v\f");
	if (!token)
	{
		_frees_buff(-1, cmds, input);
		return (1); }
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
	if (!term_f)
	{
		_execute(i, cmds, input, envp, av, counter, term_f);
		_tokenize(term_f, envp, av, counter);
		exit_handler(1, 0, 0, NULL, NULL, NULL, av, counter);
	}
	return (_execute(i, cmds, input, envp, av, counter, term_f));
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
 * _isalpha - checks for alphabetical characters.
 * @c: character to test if is alphabetical
 * Return: 1 (Success if character is alphabetical)
 *		   0 (Failure if character is not alphabetical)
 */
int _isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
