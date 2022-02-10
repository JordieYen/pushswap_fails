#include <stdio.h>
#include <stdlib.h>
#include "libft/ft_atoi.c"
#include "libft/ft_calloc.c"

typedef struct
{
	int	*stck;
	int	*size;
} stack;

void	swap(stack s)
{
	int	i;

	if (*s.size >= 2)
	{
		i = s.stck[0];
		s.stck[0] = s.stck[1];
		s.stck[1] = i;
	}
}

void	movesecondup(stack s)
{
	int	i;

	i = 0;
	while (i < *s.size)
	{
		s.stck[i] = s.stck[i + 1];
		i++;
	}
}

void	moveseconddown(stack s)
{
	int	size;

	size = *s.size;
	while (size > 0)
	{
		s.stck[size] = s.stck[size - 1];
		size--;
	}
}

void	push(stack s1, stack s2)
{
	int	firststack1;
	int	temp;
	int	i;

	i = 0;
	if (*s1.size > 0)
	{
		firststack1 = s1.stck[0];
		movesecondup(s1);
		*s1.size -= 1;
		moveseconddown(s2);
		s2.stck[0] = firststack1;
		*s2.size += 1;
	}
}

void	rotate(stack s)
{
	int	first;

	first = s.stck[0];
	movesecondup(s);
	s.stck[*s.size - 1] = first;
}

void	reverserotate(stack s)
{
	int last;

	last = s.stck[*s.size - 1];
	moveseconddown(s);
	s.stck[0] = last;
}

void	printstack(stack s)
{
	int	i;

	i = 0;
	printf("( ");
	while (i < *s.size)
	{
		printf("%d ", s.stck[i]);
		i++;
	}
	printf(")\n");
}

int	getmedian(stack s)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < *s.size)
	{
		sum += s.stck[i];
		i++;
	}
	return (sum / *s.size);
}

void	sortstack(stack s1, stack s2, int buff, int a)
{
	int i;
	int	med;

	printf("---------\n");
	printstack(s1);
	printstack(s2);
	while (*s1.size >= (3 + buff))
	{
		i = 0;
		med = getmedian(s1);
		printf("median = %d\n", med);
		while (i <= *s1.size && *s1.size > (2 + buff))
		{
			if (s1.stck[0] <= med)
			{
				push(s1, s2);
				if (a == 1)
					printf("pushed (%d) from stack1 to stack2\n", s2.stck[0]);
			}
			else
			{
				if (a == 1)
					printf("stack1 rotated (%d)\n", s1.stck[0]);
				rotate(s1);
			}
			i++;
		}
		printstack(s1);
		printstack(s2);
	}
	if (s1.stck[0] > s1.stck[1] && *s1.size == 2)
	{
		swap(s1);
		printf("swapped first 2 numbers from stack1\n");
	}
	printf("---------\n");
}

void	sortstack10(stack a, stack b)
{
	int i;

	sortstack(a, b, 0, 1);
	sortstack(b, a, 0, 1);
	sortstack(a, b, 0, 1);
	reverserotate(b);
	push(b, a);
	reverserotate(b);
	push(b, a);
	sortstack(b, a, 0, 1);
	sortstack(a, b, 2, 1);
	reverserotate(b);
	push(b, a);
	reverserotate(b);
	push(b, a);
	sortstack(b, a, 0, 1);
	sortstack(a, b, 4, 1);
	reverserotate(b);
	push(b, a);
	reverserotate(b);
	push(b, a);
	if (*b.size == 2)
	{
		if (b.stck[0] < b.stck[1])
			swap(b);
		push(b, a);
		push(b, a);
	}
}

int	checksorted(stack a, stack b)
{
	int i;

	i = 0;
	while (i < *a.size)
	{
		if (a.stck[i] > a.stck[i + 1] && a.stck[i + 1] != '\0')
			return (0);
		i++;
	}
	if (*b.size != 0)
		return (0);
	return (1);
}

void	sortstacku(stack a, stack b)
{
	int buff;

	buff = 0;
	sortstack(a, b, 0, 0);
	while (checksorted(a, b) == 0)// && buff <= 20)
	{
		sortstack(b, a, 0, 1);
		sortstack(a, b, buff, 1);
		reverserotate(b);
		push(b, a);
		reverserotate(b);
		push(b, a);
		if (*b.size == 2)
		{
			if (b.stck[0] < b.stck[1])
				swap(b);
			push(b, a);
			push(b, a);
		}
		buff += 2;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	stack	a;
	stack	b;
	int		asize = 0;
	int		bsize = 0;

	a.stck = ft_calloc((argc - 1), sizeof(int));
	b.stck = ft_calloc((argc - 1), sizeof(int));
	a.size = &asize;
	b.size = &bsize;
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			a.stck[i - 1] = ft_atoi(argv[i]);
			*a.size += 1;
			i++;
		}
		sortstacku(a, b);
		printf("stack a > ");
		printstack(a);
		//printf("\n");
		printf("stack b > ");
		printstack(b);
	}
	return (0);
}
