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
