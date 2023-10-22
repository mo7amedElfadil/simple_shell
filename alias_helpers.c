#include "main.h"
/**
 * _list_value - returns value
 * @head: head of list
 * @name: name of member
 * Return: value of member
 */
char *_list_value(al_list *head, char *name)
{
	if (!name)
		return (0);

	while (head && head->next && _strcmp(head->name, name))
		head = head->next;
	if (head->value && !_strcmp(head->name, name))
		return (head->value);
	return (0);
}
/**
 * _find_alias - returns aliased value
 * @head: head of list
 * @name: name of member
 * Return: value of member
 */

char *_find_alias(al_list *head, char *name)
{
	char *al = 0;

	if (!head || !name)
		return (0);
	al = _list_value(head, name);
	if (al)
	{
		char *ax = _find_alias(head, al);

		if (ax)
			al = ax;
	}
	else
		return (name);
	return (al);
}
/**
 * _cmd_replace - replace command value
 * @cmds: command to replace
 * @value: value to replace command with
 * Return: new cmds
 */
char *_cmd_replace(char *cmds, char *value)
{
	if (value && _strcmp(cmds, value))
	{
		int len_v = _strlen(value) + 1, len_c = _strlen(cmds) + 1;

		cmds = _realloc(cmds, len_c, len_v);
		_strcpy(cmds, value);
	}

	return (cmds);
}
