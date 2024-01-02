/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:07 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 19:33:00 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *node)
{
	while (node != NULL)
	{
		printf("%d ", node->order);
		node = node->next;
	}
	printf("\n");
}

static void	ft_freestack(t_stack **stack)
{
	t_stack	*aux;

	aux = *stack;
	while (aux != NULL)
	{
		aux = aux->next;
		free(*stack);
		*stack = aux;
	}
}

static int	isordered(t_stack *stack)
{
	uint	i;

	i = 1;
	while (stack != NULL)
	{
		if (i != stack->order)
			return (0);
		stack = stack->next;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_stack	*stacka;
	int		error;

	i = 0;
	error = 0;
	stacka = NULL;
	while (++i < argc)
	{
		if (!parse_nbr(argv[i], &stacka))
		{
			write(2, "Error\n", 7);
			error = EINVAL;
			break ;
		}
	}
	if (!error)
	{
		if (!isordered(stacka))
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	ft_freestack(&stacka);
	return (error);
}
