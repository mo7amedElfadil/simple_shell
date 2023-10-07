#include "main.h"

/**
 * cmd_path - find the path for executable commands
 * @envp: envirement paramaters.
 * @cmd: the commands we search for.
 * Return: the path for the cmd if it is found
 * and NULL
 */
char *cmd_path(char **envp, char *cmd)
{
	int i = 0;
	char *token = NULL, delim[] = "=:";
	DIR *dir;
	struct dirent *entity;

	errno = 0;

	while (_strncmp(en[i], "PATH=", 5))
		i++;


	token = strtok(en[i], delim);
	while ((token = strtok(NULL, delim)))
	{
		dir = opendir(token);
		if (dir)
		{
			while ((entity = readdir(dir)))
			{
				if ((_strncmp(entity->d_name, ".", 1)
							|| _strncmp(entity->d_name, "..", 1)
							&& !_strcmp(entity->d_name, cmd)))
				{
					errno = 0;
					closedir(dir);
					return (token);
				}
			}
		}
	}


	errno = ENOENT;
	closedir(dir);
	return (NULL);
}
