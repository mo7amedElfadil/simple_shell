#include "main.h"
/**
 * print_list - print all elements of a list_t list
 * @h: head of the linked list to be printed
 * Return: number of elements
 */

size_t print_list(list_c *h)
{
	if (!(h))
		return (0);

	if (h->str == NULL)
		printf("[0] (nil)\n");
	else
		printf("[%u] %s\n", h->len, h->str);
	return (1 + print_list(h->next));



}
/**
 * add_node_end - adds a node at the beginning of a list_t list
 * @head: ptr to head ptr of the linked list
 * @str: string to be duplicated into the node's str member
 * Return:  address of a new element or null if failed
 */

list_c *add_node_end(list_c **head, char *str)
{

	if (*head == NULL)
	{
		list_t *new = NULL;

		new = malloc(sizeof(list_t));
		if (new == NULL)
			return (NULL);

		if (str)
		{
			new->str = strdup(str);
			new->len = _strlen(str);
		}
		else
			new->str = NULL;
		new->next = NULL;
		(*head) = new;
	}
	else
	{
		(*head)->next = (add_node_end(&(*head)->next, str));
	}


	return (*head);



}



/**
 * add_node - adds a node at the beginning of a list_t list
 * @head: ptr to head ptr of the linked list
 * @str: string to be duplicated into the node's str member
 * Return:  address of a new element or null if failed
 */

list_c *add_node(list_c **head, char *str)
{
	list_c *new = NULL;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	if (str)
	{
		new->str = strdup(str);
		new->len = _strlen(str);
	}
	else
		new->str = NULL;
	new->next = (*head);
	(*head) = new;
	return (*head);
}


/**
 * free_list - frees a linked list list_t
 * @head: ptr to head ptr of the linked list
 */

void free_list(list_c *head)
{
	if (head != NULL)
	{
		(free_list(head->next));
		if (head->str)
			free(head->str);
		free(head);
	}

}

/**
 * delete_nodeint_at_index - deletes a node at the idx position
 *						of a listint_t linked list.
 * @head: head of the linked list to be printed
 * @index: index of list
 * Return: node at index or NULL if failed
 */

int delete_nodeint_at_index(list_c **head, unsigned int index)
{
	if (!head || !*head)
		return (-1);
	if (index)
	{
		return (delete_nodeint_at_index(&(*head)->next, index - 1));
	}
	else
	{
		list_c *temp = (*head);

		(*head) = (*head)->next;
		free(temp);
		return (1);
	}
}

/**
 * insert_nodeint_at_index - inserts a node at the idx position
 *						of a listint_t linked list.
 * @head: head of the linked list to be printed
 * @idx: index of list
 * @n: data to be assigned to node
 * Return: node at index or NULL if failed
 */

list_c *insert_nodeint_at_index(list_c **head, unsigned int idx, int n)
{
	list_c *new = NULL;

	if (!head)
		return (NULL);
	if (!idx)
		return (add_nodeint(head, n));

	if (idx > 0)
	{
		if (!*head)
			return (NULL);
		return (insert_nodeint_at_index(&(*head)->next, idx - 1, n));
	}
	return (new);
}
/**
 * add_nodeint - adds a node at the beginning of a listint_t list
 * @head: ptr to head ptr of the linked list
 * @n: integer value to be assigned to node
 * Return:  address of a new element or null if failed
 */

list_c *add_nodeint(list_c **head, int n)
{
	list_c *new = NULL;

	new = malloc(sizeof(list_c));
	if (new == NULL)
		return (NULL);
	new->n = n;
	new->next = (*head);
	(*head) = new;
	return (*head);
}
