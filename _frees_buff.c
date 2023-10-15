#include "main.h"
/**
 * _frees_buff - frees all buffers
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 */

void _frees_buff(int span, char **cmds, char *input)
{
	static int cmds_freed = 0;
	static int input_freed = 0;
	int idx = 0;

	(void)span;
	if (cmds)
	{
		while (cmds[idx])
		{
			free(cmds[idx]);
			cmds[idx] = NULL;
			idx++;
		}
	}
	if (cmds && !cmds_freed)
	{
		free(cmds);
		cmds_freed = 1;
	}
	if (input && !input_freed)
	{
		free(input);
		input_freed = 1;
	}
}

void _free_envp(char **envp)
{
	int i;

	for (i = 0; envp[i]; i++)
		if (envp[i])
		{
			free(envp[i]);
			envp[i] = NULL;
		}
	if (envp)
	{
		free(envp);
		envp = NULL;
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
			ptr = NULL;
		}
	}
	va_end(ap);
}
