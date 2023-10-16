#include "main.h"

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 * @envp_origin: environmental point
 * Return: 0
 */
int main(int ac, char **av, char *envp_origin[])
{
	size_t counter = 0;
	char **envp = NULL;

	envp = copy_envp_main(envp_origin);

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
	if (envp)
		_free_envp(envp);

	return (0);
}

/**
 * copy_envp_main - copy the envp variable in the main.
 * @envp: the envirement variable list.
 * Return: pointer to the new envirement variable list.
 */
char **copy_envp_main(char **envp)
{
	char **new_envp = NULL;
	int i = 0;

	while (envp[i])
		i++;
	if (i)
	{
		new_envp = malloc(sizeof(char *) * (i + 100));
		if (!new_envp)
			return (envp);
		i = 0;
		while (envp[i])
		{
			new_envp[i] = malloc(_strlen(envp[i]) + 1);
			_strcpy(new_envp[i], envp[i]), i++;
		}
		new_envp[i] = NULL;
		return (new_envp);
	}

	return (envp);
}
