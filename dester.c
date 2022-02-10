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
	while (i < buff)//*s.size)
	{
		sum += s.stck[i];
		i++;
	}
	return (sum / buff);//*s.size);
}

void	sort3a(stack s)
{
	while (s.stck[0] > s.stck[1] || s.stck[0] > s.stck[2] || s.stck[1] > s.stck[2])
	{
		if (s.stck[0] > s.stck[1])
			swap(s);
		if (s.stck[1] > s.stck[2])
		{
			rotate(s);
			swap(s);
			reverserotate(s);
			if (s.stck[0] > s.stck[1])
				swap(s);
		}
	}
}

void	sort3b(stack s)
{
	while (s.stck[0] < s.stck[1] || s.stck[0] < s.stck[2] || s.stck[1] < s.stck[2])
	{
		if (s.stck[0] < s.stck[1])
			swap(s);
		if (s.stck[1] < s.stck[2])
		{
			rotate(s);
			swap(s);
			reverserotate(s);
			if (s.stck[0] < s.stck[1])
				swap(s);
		}
	}
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
	printf("QUICK SORT A STARTS\n");
	printstack(a);
	printstack(b);
	printf("med = %d\n", med);
	while (i < buff)
	{
		if (a.stck[0] <= med)
		{
			push(a, b);
			printf("pushed %d from stack a to b\n", a.stck[0]);	
			pcount++;
		}
		else
		{
			rotate(a);
			printf("a rotated up\n");
			rcount++;
		}
		i++;
	}
	printstack(a);
	printstack(b);
	i = 0;
	while (i++ < rcount)
	{
		printf("a rotated down\n");
		reverserotate(a);
	}
	if (rcount == 3)
	{
		printf("sorted the first 3 numbers in stack a\n");
		sort3a(a);
	}
	if (rcount == 2)
	{
		if (a.stck[0] > a.stck[1])
		{
			printf("swapped first 2 numbers in stack a\n");
			swap(a);
		}
	}
	if (pcount == 3)
	{
		sort3b(b);
		printf("sorted first 3 numbers in stack b\n");
		push(b, a);
		push(b, a);
		push(b, a);
		printf("pushed first 3 numbers from stack b to stack a\n");
		pcount -= 3;
	}
	if (pcount == 2)
	{
		if (b.stck[0] < b.stck[1])
		{
			printf("swapped first 2 numbers in stack b\n");
			swap(b);
		}
		push(b, a);
		push(b, a);
		printf("pushed first 2 numbers from stack b to stack a\n");
		pcount -= 2;
	}
	if (a.stck[0] > a.stck[1] && *a.size == 2)
	{
		printf("swapped first 2 numbers in stack a\n");
		swap(a);
	}
	printstack(a);
	printstack(b);
	//if (*a.size == 3)
	//	sort3a(a);
	printf("QUICK SORT A ENDS\n");
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
	printf("QUICK SORT B STARTS\n");
	printstack(a);
	printstack(b);
	printf("med = %d\n", med);
	while (i < buff)
	{
		if (b.stck[0] > med)
		{
			push(b, a);
			printf("pushed %d from stack b to a\n", a.stck[0]);
			pcount++;
		}
		else
		{
			rotate(b);
			printf("b rotated up\n");
			rcount++;
		}
		i++;
	}
	printstack(a);
	printstack(b);
	i = 0;
	while (i++ < rcount)
	{
		reverserotate(b);
		printf("b rotated down\n");
	}
	if (pcount == 3)
	{
		sort3a(a);
		printf("sorted first 3 numbers in stack a\n");
	}
	if (pcount == 2)
	{
		if (a.stck[0] > a.stck[1])
		{
			printf("swapped first 2 numbers in stack a\n");
			swap(a);
		}
	}
	if (rcount == 3)
	{
		sort3b(b);
		printf("sorted first 3 numbers in stack b\n");
		push(b, a);
		push(b, a);
		push(b, a);
		printf("pushed first 3 numbers from stack b to stack a\n");
		pcount += 3;
	}
	if (rcount == 2)
	{
		if (b.stck[0] < b.stck[1])
		{
			printf("swapped first 2 numbers in stack b\n");
			swap(b);
		}
		push(b, a);
		push(b, a);
		printf("pushed first 2 numbers in from stack b to stack a\n");
		pcount += 2;
	}
//	if (pcount == 3)
//	{
//		sort3a(a);
//		printf("sorted first 3 numbers in stack a\n");
//	}
//	if (pcount == 2)
//	{
//		if (a.stck[0] > a.stck[1])
//		{
//			printf("swapped first 2 numbers in stack a\n");
//			swap(a);
//		}
//	}
	if (b.stck[0] < b.stck[1] && *b.size == 2)
	{
		printf("swapped first 2 numbers in stack b\n");
		swap(b);
	}
	printstack(a);
	printstack(b);
	//if (*b.size == 3)
	//	sort3b(b);
	printf("QUICK SORT B ENDS\n");
	return (pcount);
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

int	sort(stack a, stack b, int buff)
{
	stack	main;
	int		temp;
	int		size;
	int		i;
	int		pcount;

	size = 0;
	temp = buff;
	main.stck = ft_calloc(*a.size, sizeof(int));
	main.size = &size;
	if (checksorted(a, b) == 0)
	{
		//while (*a.size > 3)
		//while (buff > 3)
		while (buff > 3)
		{
			if (!((*a.size == 5 && checksortedi(a, 5) == 1) || (*a.size == 6 && checksortedi(a, 6) == 1)))
			{
				main.stck[size] = quicksorta(a, b, buff);
				buff -= main.stck[size];
				size++;
			}
			else
				break ;
			printstack(a);
			//printstack(b);
		}
		printf("stack A > ");
		printstack(a);
		printf("stack B > ");
		printstack(b);	
		printstack(main);
		i = size - 1;
		while (i >= 0)
		{
			printf("stack A > ");
			printstack(a);
			printf("stack B > ");
			printstack(b);
			if (main.stck[i] <= 10)
			{
				while (main.stck[i] > 3)
				{
					pcount = quicksortb(b, a, main.stck[i]);
					printstack(main);
					main.stck[i] -= pcount;
					if (main.stck[i] > 3)
					{
						if (!(main.stck[i] == 5 && checksortedi(a, 5) == 1))
						{
							pcount = quicksorta(a, b, main.stck[i]);
							main.stck[i] += pcount;
							if (main.stck[i] > 3 && !(main.stck[i] == 5 && checksortedi(a, 5) == 1))
							{
								//pcount = quicksorta(a, b, main.stck[i]);
								//temp += pcount;
								//main.stck[i] -= pcount;
								//printstack(main);
								//temp = sort(a, b, main.stck[i]);
								//main.stck[i] -= temp ;//+ 3;
								//if (temp == 0)
								//	break;
							}
							//main.stck[i] += temp;
						}
					}
					printstack(main);
				}
			}
			i--;
		}
	}
	return (temp);
	freestack(main);
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
		sort(a, b, asize);
		//quicksorta(a, b, asize);
		//quicksorta(a, b, asize);
		//quicksortb(b, a, 3);
		printf("stack A > ");
		printstack(a);
		//printf("\n");
		printf("stack B > ");
		printstack(b);
		printf("Stack A size > %d\nStack B size > %d\n", asize, bsize);
		if (checksorted(a, b) == 0)
			printf("STACK IS NOT SORTED\n");
		else
			printf("Stack is sorted, hell yeah!\n");
	}
	return (0);
}
