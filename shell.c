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
	int fd = 0;
	FILE *stream = NULL;

	envp = copy_envp_main(envp_origin);
	if (!envp)
		exit_handler(0, 1, 0, 0, 0, 0, av, 0);
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			open_error(av, counter), errno = 127;
			exit_handler(0, 0, 0, 0, envp, 0, 0, 0);
		}
		else
			stream = fdopen(fd, "r");
		errno = 0;
	}
	while (1)
	{
		int term_f = 0, err = 0;

		counter++;
		term_f = isatty(STDIN_FILENO), errno = 0;
		err = _tokenize(term_f, envp, av, counter, ac, stream, fd);
		if (!term_f || err == -1)
			break;
	}
	alias(0, NULL, envp);
	if (envp)
		_free_envp(envp);
	if (fd && stream)
		fclose(stream);
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

	if (!envp)
		return (NULL);
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
/**
 * open_error - generate error message for open funtion
 * @counter: the counter
 * @av: argument vector
 * Return:NONE.
 */
void open_error(char **av, size_t counter)
{
	char *err_msg = malloc(100), *ul = NULL;

	_strcpy(err_msg, av[0]);
	_strcat(err_msg, ": ");
	ul = _ultoa(counter);
	_strcat(err_msg, ul);
	_strcat(err_msg, ": ");
	_strcat(err_msg, "Can't open ");
	_strcat(err_msg, av[1]);
	_strcat(err_msg, "\n");
	_put_error(err_msg);
	free(ul);
	free(err_msg);
}
