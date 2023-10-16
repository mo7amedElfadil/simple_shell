#include "main.h"
#include <linux/limits.h>

/**
 * cd_cmd__ - execute the cd - inside cd_cmd function.
 * @target: the target path we want to change our dir to it.
 * @previous: the previous path (PWD).
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 in case of failure.
 */

int cd_cmd__(char *target, char *previous, char **envp)
{
	char *pwd = "PWD";

	if (chdir(target) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		if (_setenv("PWD", target, 1, envp) == -1)
			return (-1);

		if (_setenv("OLDPWD", previous, 1, envp) == -1)
			return (-1);
		print_envp(0, &pwd, envp);
	}
	return (0);
}
/**
 * cd_cmd_sup - to be executed inside cd_cmd function,
 * change the PWD to target path.
 * @target: the target path we want to change our dir to it.
 * @previous: the previous path (PWD).
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 in case of failure.
 */

int cd_cmd_sup(char *target, char *previous, char **envp)
{
	if (chdir(target) == -1)
	{
		perror("Error"), errno = 0;
		return (-1);
	}
	else
	{
		char buff[PATH_MAX];
		if (target[0] != '/')
		{
			_strcpy(buff, previous);
			_strcat(buff, "/");
			_strcat(buff, target);

		}
		else
			_strcpy(buff, target);
		if (_setenv("PWD", buff, 1, envp) == -1)
			return (-1);

		if (_setenv("OLDPWD", previous, 1, envp) == -1)
			return (-1);
	}
	return (0);
}

/**
 * cd_cmd_par - to be executed inside cd_cmd function,
 * change the PWD to parent path.
 * @target: the target path we want to change our dir to it.
 * @envp: envirement variable.
 * Return: 0 if succeeded, -1 in case of failure.
 */

int cd_cmd_par(char *target, char **envp)
{
	char buffer[PATH_MAX];

	_strcpy(buffer, target);
	cd_cmd_dd(target);
	if (chdir(target) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		if (_setenv("PWD", target, 1, envp) == -1)
			return (-1);

		if (_setenv("OLDPWD", buffer, 1, envp) == -1)
			return (-1);
	}
	return (0);
}
/**
 * is_v_path - Check if the given path is a valid directory.
 * @path: The path to be checked.
 * Return: 1 if it's a valid directory, 0 if it's not.
 */
int is_v_path(const char *path)
{
	struct stat dir_path;

	if (stat(path, &dir_path) == 0 && (dir_path.st_mode & S_IFDIR))
		return (1);
	return (0);
}

