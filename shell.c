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
	size_t counter = 0;

	(void)ac, (void)av;
	while (1)
	{
		int term_f = 0, err = 0;

		counter++;

		term_f = isatty(STDIN_FILENO);
		if (term_f)
			_put_buffer("($) ");
		err = _tokenize(term_f, envp, av, counter);
		if (!term_f || err == -1)
			break;
	}
	return (0);
}
