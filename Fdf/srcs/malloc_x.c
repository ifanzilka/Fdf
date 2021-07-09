#include <stdlib.h>

void	*malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(-2);
	return (ptr);
}
