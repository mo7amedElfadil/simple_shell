#include "main.h"
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

