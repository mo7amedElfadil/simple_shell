#include "main.h"

/**
 * alias - prints the aliases or creates new one or modifies existing
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @envp: environmental pointer
 * Return: 0 on success.
 */
int alias(int span, char **cmds, char **envp)
{

	make_void(3, span, **cmds, **envp);
	_put_buffer("alias\n");
	return (0);
}
