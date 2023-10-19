#include "main.h"

/**
 * alias - prints the aliases or creates new one or modifies existing
 * @span: number of tokens - 1 (or index of last token)
 * @cmds: array of tokens/commands
 * @envp: environmental pointer
 * Return: 0 on success.
 */
char *alias(int span, char **cmds, char **envp)
{
	static al_list *head;
	al_list *srch = head;
	int i = 1, len = 0;
	char *name = NULL, *value = NULL, not[1000];

	(void)envp;
	if (!cmds && head)
	{	free_linked_list(head), head = NULL;
		return (0); }
	if (!span)
		print_linked_list(NULL, head);
	else
	{
		while (i <= span && cmds[i])
		{	len = _strlen(cmds[i]), _strcpy(not, cmds[i]), name = strtok(not, "=");
			if (_strcspn(cmds[i], "\'") < len)
				value = strtok(NULL, "'");
			else if (_strcspn(cmds[i], "\"") < len)
				value = strtok(NULL, "\"");
			else
				value = strtok(NULL, " ");
			if (!value)
			{
				print_linked_list(name, head);
			}
			else
			{
				while (srch && srch->name && strcmp(name, srch->name))
					srch = srch->next;
				if (!srch)
					if (!head)
						head = add_node_linked_list(&head, name, value);
					else
						add_node_linked_list(&head, name, value);
				else
				{	free(srch->value), len = _strlen(value) + 1;
					srch->value = malloc(len), _strcpy(srch->value, value); }
			}
			i++; }
	}
	return (0); }
/**
 * _list_value - returns value
 * @head: head of list
 * @name: name of member
 * Return: value of member
 */
char *_list_value(al_list *head, char *name)
{
	while (head && _strcmp(head->name, name))
		head = head->next;
	return (head->value);

}
/**
 * add_node_end - adds a new node at the end of a al_list of alias.
 * @head: ptr to head ptr of the linked list
 * @nam: string to be duplicated into the node's name member
 * @val: string to be duplicated into the node's value member
 * Return: address of a new element or null if failed
 */
al_list *add_node_linked_list(al_list **head, char *nam, char *val)
{
	al_list  *new = NULL, *tmp = NULL;


	new = malloc(sizeof(al_list));
	if (new == NULL)
		return (NULL);

	new->name = strdup(nam);
	if (new->name == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = strdup(val);
	if (new->value == NULL)
	{
		free(new->name), free(new);
		return (NULL);
	}
	new->next = NULL;


	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;

	return (new);
}
/**
 * print_linked_list - prints all alias in the al_list.
 * @head: pointer to a struct of type al_list.
 * @name: string to be duplicated into the node's name member
 * Return: None.
 */
void print_linked_list(char *name, al_list *head)
{
	int a = 0, b = 0;

	if (!head)
		return;
	while (head)
	{
		a = 0;
		if (!name)
			a = 1;
		else
		{
			if (!strcmp(name, head->name))
				a = 1, b = 1;
		}
		if (a == 1)
		{
			_put_buffer(head->name);
			_put_buffer("=");
			_put_buffer("'");
			_put_buffer(head->value);
			_put_buffer("'");
			_put_buffer("\n");
			if (b)
				break;
		}
		head = head->next;
	}
}


/**
 * free_linked_list - frees a linked list list_t
 * @head: ptr to head ptr of the linked list
 */
void free_linked_list(al_list *head)
{
	if (head != NULL)
	{
		(free_linked_list(head->next));
		if (head->name)
			free(head->name);
		if (head->value)
			free(head->value);
		free(head);
	}
}
