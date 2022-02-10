#include <stdio.h>
#include <stdlib.h>
#include "libft/ft_atoi.c"
#include "libft/ft_calloc.c"

typedef struct
{
	int	*stck;
	int	*size;
} stack;

void	freestack(stack s)
{
	free(s.stck);
	s.stck = NULL;
}

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

int	getmedian(stack s, int buff)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < buff)
	{
		sum += s.stck[i];
		i++;
	}
	return (sum / buff);
}

void	sort3a(stack s)
{
	while (s.stck[0] > s.stck[1] || s.stck[0] > s.stck[2] || s.stck[1] > s.stck[2])
	{
		if (s.stck[0] > s.stck[1])
		{
			swap(s);
			printf("sa\n");
		}
		if (s.stck[1] > s.stck[2])
		{
			rotate(s);
			printf("ra\n");
			swap(s);
			printf("sa\n");
			reverserotate(s);
			printf("ra\n");
			if (s.stck[0] > s.stck[1])
			{
				swap(s);
				printf("sa\n");
			}
		}
	}
}

void	sort3b(stack s)
{
	while (s.stck[0] < s.stck[1] || s.stck[0] < s.stck[2] || s.stck[1] < s.stck[2])
	{
		if (s.stck[0] < s.stck[1])
		{
			swap(s);
			printf("sb\n");
		}
		if (s.stck[1] < s.stck[2])
		{
			rotate(s);
			printf("rb\n");
			swap(s);
			printf("sb\n");
			reverserotate(s);
			printf("rb\n");
			if (s.stck[0] < s.stck[1])
			{
				swap(s);
				printf("sb\n");
			}
		}
	}
}

int	checksortedi(stack s, int max)
{
	int i;

	i = 0;
	while (i < (max - 1))
	{
		if (s.stck[i] > s.stck[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	checkbelowmed(stack s, int max, int med)
{
	int i;

	i = 0;
	while (i < max)
	{
		if (s.stck[i] <= (med + 1))
			return (0);
		i++;
	}
	return (1);
}


int	quicksorta(stack a, stack b, int buff)
{
	int i;
	int	med;
	int size;
	int	pcount;
	int rcount;

	i = 0;
	pcount = 0;
	rcount = 0;
	med = getmedian(a, buff);
	while (i < buff)
	{
		//printf("[%d]\n", med);
		//printstack(a);
		//printf("[%d]\n", buff - pcount - rcount);
		if (checkbelowmed(a, (buff - (pcount)), med) == 0)
		{
			//printf("{%d}\n", med);
			//printstack(a);
			//printf("{%d}\n", buff - pcount);
			if (a.stck[0] <= med)
			{
				push(a, b);
				printf("pa\n");
				pcount++;
			}
			else
			{
				rotate(a);
				printf("ra\n");
				rcount++;
			}
		}
		else
			break;
		i++;
	}
	i = 0;
	while (i++ < rcount && checksortedi(a, rcount))// && checkbelowmed(a, rcount, med))
	{
		reverserotate(a);
		printf("rra\n");
	}
	if (rcount == 3)
	{
		sort3a(a);
	}
	if (rcount == 2)
	{
		if (a.stck[0] > a.stck[1])
		{
			swap(a);
			printf("sa\n");
		}
	}
	if (pcount == 3)
	{
		sort3b(b);
		push(b, a);
		push(b, a);
		push(b, a);
		printf("pa\npa\npa\n");
		pcount -= 3;
	}
	if (pcount == 2)
	{
		if (b.stck[0] < b.stck[1])
		{
			swap(b);
			printf("sb\n");
		}
		push(b, a);
		push(b, a);
		printf("pa\npa\n");
		pcount -= 2;
	}
	if (a.stck[0] > a.stck[1] && *a.size == 2)
	{
		swap(a);
		printf("sa\n");
	}
	return (pcount);
}

int	quicksortb(stack b, stack a, int buff)
{
	int i;
	int	med;
	int	rcount;
	int	pcount;

	i = 0;
	rcount = 0;
	med = getmedian(b, buff);
	pcount = 0;
	while (i < buff)
	{
		if (b.stck[0] > med)
		{
			push(b, a);
			pcount++;
		}
		else
		{
			rotate(b);
			rcount++;
		}
		i++;
	}
	i = 0;
	while (i++ < rcount)
	{
		reverserotate(b);
	}
	if (pcount == 3)
	{
		sort3a(a);
	}
	if (pcount == 2)
	{
		if (a.stck[0] > a.stck[1])
		{
			swap(a);
		}
	}
	if (rcount == 3)
	{
		sort3b(b);
		push(b, a);
		push(b, a);
		push(b, a);
		pcount += 3;
	}
	if (rcount == 2)
	{
		if (b.stck[0] < b.stck[1])
		{
			swap(b);
		}
		push(b, a);
		push(b, a);
		pcount += 2;
	}
	if (b.stck[0] < b.stck[1] && *b.size == 2)
	{
		swap(b);
	}
	return (pcount);
}

int	checksorted(stack a, stack b)
{
	int i;

	i = 0;
	while (i < (*a.size - 1))
	{
		if (a.stck[i] > a.stck[i + 1])
			return (0);
		i++;
	}
	if (*b.size != 0)
		return (0);
	return (1);
}

//int	checksortedi(stack s, int max)
//{
//	int i;
//
//	i = 0;
//	while (i < (max - 1))
//	{
//		if (s.stck[i] > s.stck[i + 1])
//			return (0);
//		i++;
//	}
//	return (1);
//}

int	checkn(stack s, int n)
{
	if (*s.size == n && checksortedi(s, n) == 1)
		return (1);
	return (0);
}

int	sort20(stack a, stack b, int buff)
{
	stack	main;
	int		size;
	int		i;
	int		pcount;

	size = 0;
	main.stck = ft_calloc(*a.size, sizeof(int));
	main.size = &size;
	if (buff == 3)
		sort3a(a);
	if (buff == 2)
	{
		if (a.stck[0] > a.stck[1])
			swap(a);
	}
	if (checksorted(a, b) == 0)
	{
		while (buff > 3)
		{
			if (!((checkn(a, 5) == 1) || checkn(a, 6) == 1 || checkn(a, 4) == 1))
			{
				main.stck[size] = quicksorta(a, b, buff);
				buff -= main.stck[size];
				size++;
			}
			else
				break ;
		}
		i = size - 1;
		while (i >= 0)
		{
			if (main.stck[i] <= 10)
			{
				while (main.stck[i] > 3)
				{
					pcount = quicksortb(b, a, main.stck[i]);
					main.stck[i] -= pcount;
					if (main.stck[i] > 3)
					{
						if (!(main.stck[i] == 5 && checksortedi(a, 5) == 1))
						{
							pcount = quicksorta(a, b, main.stck[i]);
							main.stck[i] += pcount;
						}
					}
				}
			}
			i--;
		}
	}
	freestack(main);
	return(*a.size);
}

void sort(stack a, stack b)
{
	int asize;
	int	bsize;
	int i;
	int n;

	asize = sort20(a, b, *a.size);
	while (checksorted(a, b) == 0)
	{
		i = 0;
		sort20(b, a, *b.size);
		bsize = *b.size;
		while (*a.size > asize)
			push(a, b);
		while (i < bsize)
		{
			reverserotate(b);
			push(b, a);
			i++;
		}
		asize += bsize;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	stack	a;
	stack	b;
	int		asize = 0;
	int		bsize = 0;

	a.stck = ft_calloc((argc), sizeof(int));
	b.stck = ft_calloc((argc), sizeof(int));
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
		//printstack(a);
		//printf("{%d}\n", checkbelowmed(a, *a.size, 4));
		sort(a, b);
		if (checksorted(a, b) == 0)
			printf("STACK IS NOT SORTED\n");
		else
			printf("Stack is sorted, hell yeah!\n");
	}
	return (0);
}
