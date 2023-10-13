#include "main.h"
#include <stdarg.h>
/**
 * _frees_buff - frees all buffers
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @input: input string from getline()
 */


void _frees_buff(int span, char **cmds, char *input)
{
	if (cmds)
		for (; span >= 0 && cmds[span]; span--)
			free(cmds[span]);
	free(cmds);
	free(input);
}

void _free_envp(char **envp)
{
	int i;

	for (i = 0; envp[i]; i++)
		free(envp[i]);
	free (envp);

}

void _free_cd(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	for (; n > 0; n--)
		free(va_arg(ap, void *));
}
