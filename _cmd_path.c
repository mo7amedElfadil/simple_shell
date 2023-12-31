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
	DIR *dir = 0;
	struct dirent *entity;

	if (!envp)
		return (0);
	while (envp[i] && _strncmp(envp[i], "PATH", 4))
		i++;
	if (!envp[i] || !(envp[i][4] == '='))
		return (NULL);
	len = _strlen(envp[i]);
	if (len)
	{
		_memcpy(ENV, envp[i], len + 1);
		token = _strtok(ENV, delim);
		while ((token = _strtok(NULL, delim)))
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

						_strcpy(result, token), closedir(dir);
						errno = 0;
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
 * Return: 0 if success, 1 on failure.
 */
int _path_cat(char **envp, char **cmds)
{
	char *token = NULL;

	if (!_strncmp(*cmds, "./", 2))
	{

		*cmds = cut_prefix(*cmds, 2);
		*cmds = prepend_pwd(*cmds, envp);
		return (0);
	}
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
		/* errno = ENOENT; */
	return (1);

}
/**
 * cut_prefix - cut the prefix.
 * @cmds: the commands to cut.
 * @size: size of prefix.
 * Return: the cutted cmds.
 */
char *cut_prefix(char *cmds, int size)
{
	int len = _strlen(cmds), i = 0;
	char *tok = malloc(len - size + 1);

	while (cmds[i + size] && (i + size) < len)
		tok[i] = cmds[i + size], i++;
	tok[i] = 0;
	cmds = _realloc(cmds, len + 1, _strlen(tok) + 1);
	_strcpy(cmds, tok), free(tok);
	return (cmds);
}

/**
 * prepend_pwd - prepand the pwd to cmds.
 * @cmds: the commands to cut.
 * @envp: enviremental variables.
 * Return: full path of the cmd.
 */
char *prepend_pwd(char *cmds, char **envp)
{
	int len = _strlen(cmds);
	char *tok, *pwd;

	pwd = get_envalue("PWD", envp, 3);
	tok = malloc(_strlen(pwd) + len + 2);
	_strcpy(tok, pwd);
	_strcat(tok, "/");
	_strcat(tok, cmds);
	cmds = _realloc(cmds, len + 1, _strlen(tok) + 1);
	_strcpy(cmds, tok);
	free(pwd), free(tok);
	return (cmds);
}
/**
 * comment - determine if a token is #
 * @token: the token to check
 * Return: 0 if true, otherwise > 0
 */
int comment(char *token)
{
	return (_strncmp(token, "#", 1));
}
