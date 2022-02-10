#include <stdio.h>
#include <stdlib.h>
#include "libft/ft_atoi.c"
#include "libft/ft_calloc.c"

typedef struct
{
	int	*a;
	int	*b;
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
	while (stack[i] != '\0')
	{
		printf("%d ", stack[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	stack	stacks;

	stacks.a = ft_calloc(argc, sizeof(int));
	stacks.b = ft_calloc(argc, sizeof(int));
	if (argc > 1)
	{
		printf("%d", argc);
		printf("\n----------------\n");
		i = 1;
		while (i < argc)
		{
			printf("%s\n", argv[i]);
			stacks.a[i - 1] = ft_atoi(argv[i]);
			i++;
		}
		printf("----------------\n a > ");
		stacks.a[i] = '\0';
		i = 0;
		swap(stacks.a);
		printstack(stacks.a);
		printf("\n----------------\n a > ");
		push(stacks.a, stacks.b);
		push(stacks.a, stacks.b);
		swap(stacks.b);
		printstack(stacks.a);
		printf("\n----------------\n b > ");
		printstack(stacks.b);
		printf("\n----------------\n a > ");
		rotate(stacks.a);
		rotate(stacks.b);
		printstack(stacks.a);
		printf("\n----------------\n b > ");
		printstack(stacks.b);
		reverserotate(stacks.a);
		reverserotate(stacks.b);
		printf("\n----------------\n a > ");
		printstack(stacks.a);
		printf("\n----------------\n b > ");
		printstack(stacks.b);
	}
	return (0);
}
