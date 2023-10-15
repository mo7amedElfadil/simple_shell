#include "main.h"
/**
 * _frees_buff - frees all buffers
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 */

void _frees_buff(int span, char **cmds, char *input)
{
	
	int idx = 0;

	if (cmds)
	{
		while (idx <= span && cmds[idx])
		{
			free(cmds[idx]);
			idx++;
		}
	}
	if (cmds)
	{
		free(cmds);
	}
	if (input)
	{
		free(input);
	}
}

/**
 * _free_envp - free the envp,copied in the main.
 * @envp: the enviromental variable.
 * Return: void.
 */
void _free_envp(char **envp)
{
	int i;

	for (i = 0; envp[i]; i++)
		if (envp[i])
		{
			free(envp[i]);
		}
	if (envp)
	{
		free(envp);
	}
}

/**
 * _free_cd - free the all the allocation in cd and setenv.
 * @n:number of arguments .
 * Return: void.
 */
void _free_cd(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	for (; n > 0; n--)
	{
		void *ptr = va_arg(ap, void *);

		if (ptr)
		{
			free(ptr);
		}
	}
	va_end(ap);
}
