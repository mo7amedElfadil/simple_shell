#include "main.h"
/**
 * _realloc - reeallocates a memory block using malloc and free
 * @ptr: pointer to reallocate memory of
 * @old_size: the old size of the pointer
 * @new_size: the new size of the pointer
 * Return: the reassigned pointer (Success)
 *			NULL (Failure) when malloc fails to assign or new_size is 0
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *real = NULL, *temp;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	temp = ptr;
	real = malloc(new_size);
	if (!real)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			real[i] = temp[i];
	}
	else if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			real[i] = temp[i];
	}
	free(ptr);
	return (real);
}
