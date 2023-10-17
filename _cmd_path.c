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
	unsigned int len = 0;
	char *token = NULL, delim[] = "=:", ENV[PATH_MAX];
	DIR *dir;
	struct dirent *entity;

	while (_strncmp(envp[i], "PATH", 4) && envp[i])
		i++;
	len = _strlen(envp[i]);
	if (len)
	{
		_memcpy(ENV, envp[i], len + 1);
		token = strtok(ENV, delim);
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
						char *result = malloc(_strlen(token) + 1);

						_strcpy(result, token);
						closedir(dir);
						/* , errno = 0; */
						return (result);
					}
				}
				closedir(dir);
			}
		}
	}
	return (NULL);
}

/**
 * _path_cat - concatinate path with command
 * @envp: environmental pointer
 * @cmds: commands pointer
 */
int _path_cat(char **envp, char **cmds)
{
	char *token = NULL;

	token = cmd_path(envp, cmds[0]);
	if (token)
	{
		char *path = NULL;

		path = malloc(_strlen(cmds[0]) + 1);

		_strcpy(path, cmds[0]);

		cmds[0] = _realloc(cmds[0], strlen(cmds[0]) + 1,
				_strlen(cmds[0]) + _strlen(token) + 2);

		_strcpy(cmds[0], token), _strcat(cmds[0], "/");

		_strcat(cmds[0], path);
		free(token), free(path);
		return (0);

	}
	else if (!strncmp(*cmds, "./", 2))
	{
		*cmds = cut_prefix(*cmds, 2);
		*cmds = prepend_pwd(*cmds, envp);
		return (0);
	}
	/* errno = ENOENT; */
	return (1);

}

char *cut_prefix(char *cmds, int size)
{
	char tok[100];
	int len = _strlen(cmds), i = 0;
	while (cmds[i + size] && (i + size) < len)
		tok[i] = cmds[i + size], i++;
	tok[i] = 0;
	cmds = _realloc(cmds, len + 1, _strlen(tok) + 1);
	_strcpy(cmds, tok);
	return (cmds);
}


char *prepend_pwd(char *cmds, char **envp)
{
	char tok[100], *pwd;
	int len = _strlen(cmds);
	pwd = get_envalue("PWD", envp, 3);
	_strcpy(tok, pwd);
	_strcat(tok, "/");
	_strcat(tok, cmds);
	cmds = _realloc(cmds, len + 1, _strlen(tok) + 1);
	_strcpy(cmds, tok);
	free(pwd);
	return (cmds);
}
