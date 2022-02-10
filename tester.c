#include <stdio.h>
#include <stdlib.h>
#include "libft/ft_atoi.c"
#include "libft/ft_calloc.c"

typedef struct	stacks
{
	int	*a;
	int	*b;
	int	asize;
	int	bsize;
} stack;

int	stacksize(int *stack)
{
	int	i;

	i = 0;
	while (stack[i] != '\0')
		i++;
	return (i);
}

void	swap(int *stack)
{
	int	i;

	i = stacksize(stack);
	if (i >= 2)
	{
		i = stack[0];
		stack[0] = stack[1];
		stack[1] = i;
	}
}

void	movesecondup(int *stack)
{
	int	size;
	int	i;

	i = 0;
	size = stacksize(stack);
	while (i < size && stack[i] != '\0')
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[i] = '\0';
}

void	moveseconddown(int *stack)
{
	int	size;

	size = stacksize(stack);
	while (size > 0)
	{
		stack[size] = stack[size - 1];
		size--;
	}
}

void	push(int *stack1, int *stack2)
{
	int	firststack1;
	int	size;
	int	temp;
	int	i;

	i = 0;
	size = stacksize(stack1);
	if (stacksize(stack1) > 0)
	{
		firststack1 = stack1[0];
		movesecondup(stack1);
		moveseconddown(stack2);
		stack2[0] = firststack1;
	}
}

void	rotate(int *stack)
{
	int	first;
	int	size;

	first = stack[0];
	size = stacksize(stack);
	movesecondup(stack);
	stack[size - 1] = first;
}

void	reverserotate(int *stack)
{
	int last;
	int	size;

	size = stacksize(stack);
	last = stack[size - 1];
	moveseconddown(stack);
	stack[0] = last;
	stack[size] = '\0';
}

void	printstack(int *stack)
{
	int	i;

	i = 0;
	printf("( ");
	while (stack[i] != '\0')
	{
		printf("%d ", stack[i]);
		i++;
	}
	printf(")\n");
}

int	getmedian(int *stack)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (stack[i] != '\0')
	{
		sum += stack[i];
		i++;
	}
	return (sum / stacksize(stack));
}

void	sortstack(int *stack1, int *stack2, int buff, int a)
{
	int i;
	int	med;
	int	asize;
	int size;

	asize = stacksize(stack1);
	printf("---------\n");
	printstack(stack1);
	printstack(stack2);
	while (asize >= (3 + buff))
	{
		i = 0;
		med = getmedian(stack1);
		printf("median = %d\n", med);
		size = stacksize(stack1);
		while (i <= size && stacksize(stack1) > (2 + buff))
		{
			if (stack1[0] <= med)
			{
				push(stack1, stack2);
				if (a == 1)
					printf("pushed (%d) from stack1 to stack2\n", stack2[0]);
			}
			else
			{
				//rotate(stack1);
				if (a == 1)
					printf("stack1 rotated (%d)\n", stack1[0]);
				rotate(stack1);
			}
			i++;
		}
		printstack(stack1);
		printstack(stack2);
		asize = stacksize(stack1);
	}
	if (stack1[0] > stack1[1] && stacksize(stack1) == 2)
	{
		swap(stack1);
		printf("swapped first 2 numbers from stack1\n");
	}
	printf("---------\n");
}

void	sortstack10(int *stacka, int *stackb)
{
	int i;

	sortstack(stacka, stackb, 0, 1);
	sortstack(stackb, stacka, 0, 1);
	sortstack(stacka, stackb, 0, 1);
	reverserotate(stackb);
	push(stackb, stacka);
	reverserotate(stackb);
	push(stackb, stacka);
	sortstack(stackb, stacka, 0, 1);
	sortstack(stacka, stackb, 2, 1);
	reverserotate(stackb);
	push(stackb, stacka);
	reverserotate(stackb);
	push(stackb, stacka);
	sortstack(stackb, stacka, 0, 1);
	sortstack(stacka, stackb, 4, 1);
	reverserotate(stackb);
	push(stackb,stacka);
	reverserotate(stackb);
	push(stackb, stacka);
	if (stacksize(stackb) == 2)
	{
		if (stackb[0] < stackb[1])
			swap(stackb);
		push(stackb, stacka);
		push(stackb, stacka);
	}
}

int	checksorted(int *stacka, int *stackb)
{
	int asize;
	int bsize;
	int i;

	i = 0;
	while (stacka[i] != '\0')
	{
		if (stacka[i] > stacka[i + 1] && stacka[i + 1] != '\0')
			return (0);
		i++;
	}
	if (stacksize(stackb) != 0)
		return (0);
	return (1);
}

void	sortstacku(int *stacka, int *stackb)
{
	int buff;

	buff = 0;
	sortstack(stacka, stackb, 0, 0);
	while (checksorted(stacka, stackb) == 0 && buff <= 20)
	{
		sortstack(stackb, stacka, 0, 1);
		sortstack(stacka, stackb, buff, 1);
		reverserotate(stackb);
		push(stackb, stacka);
		reverserotate(stackb);
		push(stackb, stacka);
		if (stacksize(stackb) == 2)
		{
			if (stackb[0] < stackb[1])
				swap(stackb);
			push(stackb, stacka);
			push(stackb, stacka);
		}
		buff += 2;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	stack	stacks;

	stacks.a = ft_calloc(argc, sizeof(int));
	stacks.b = ft_calloc(argc, sizeof(int));
	stacks.asize = 0;
	stacks.bsize = 0;
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			stacks.a[i - 1] = ft_atoi(argv[i]);
			i++;
		}
		stacks.a[i] = '\0';
		sortstacku(stacks.a, stacks.b);
		printf("stack a > ");
		printstack(stacks.a);
		//printf("\n");
		printf("stack b > ");
		printstack(stacks.b);

		char c = '0';
		i = ft_atoi(&c);
		printf("%d\n", i);
	}
	return (0);
}
