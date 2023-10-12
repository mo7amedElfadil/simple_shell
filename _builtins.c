#include "main.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_pid - prints pid of the shell process
 */
int print_pid(int span, char **cmds, char **envp)
{

	make_void(3, span, **cmds, **envp);
	_put_buffer(_itoa(getppid()));
	_put_buffer("\n");
	return (0);
}
/**
 * print_err - prints errno of the shell process
 */
int print_err(int span, char **cmds, char **envp)
{
	make_void(3, span, **cmds, **envp);
	_put_buffer(_itoa(errno));
	_put_buffer("\n");
	return (0);
}

/**
 * alias - prints the aliases or creates new one or modifies existing
 */
void alias(char **cmds, int span)
{
	(void)cmds, (void)span;
		_put_buffer(_itoa(errno));
}

void make_void(int num, ...)
{
	va_list ap;

	va_start(ap, num);
	while (num > 0)
	{
		(void)va_arg(ap, void *);
		num--;
	}
	va_end(ap);

}
