#include "main.h"

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 * @envp: environmental point
 * Return: 0
 */
int main(int ac, char **av, char *envp[])
{
	while (1)
	{
		int term_f = 0, err = 0;

		term_f = isatty(stdin->_fileno);
		if (term_f)
			_put_buffer("($) ");
		err = _tokenize(term_f, envp);
		if (err == EXIT_FAILURE)
			_put_buffer("Not a shell command\n");
		if (!term_f || err == -1)
			break;
	}
	return (0);
}
