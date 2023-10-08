#include "main.h"

/**
 * cmd_path - find the path for executable commands
 * @envp: envirement paramaters.
 * @cmd: the commands we search for.
 * Return: the path for the cmd if it is found
 * and NULL if not found
 */
char *cmd_path(char **envp, char *cmd)
{
	int i = 0;
	char *token = NULL, delim[] = "=:";
	DIR *dir;
	struct dirent *entity;

	while (_strncmp(envp[i], "PATH", 4) && envp[i])
		i++;
	token = strtok(envp[i], delim);
	while ((token = strtok(NULL, delim)))
	{
		dir = opendir(token);
		if (dir)
		{
			while ((entity = readdir(dir)))
			{
				if (((_strncmp(entity->d_name, ".", 1)
							|| _strncmp(entity->d_name, "..", 2))
							&& (!_strcmp(entity->d_name, cmd))))
				{
					closedir(dir);
					errno = 0;
					return (token);
				}
			}
			closedir(dir);
		}
	}
	errno = 0;
	return (NULL);
}
