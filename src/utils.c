/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:34 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 17:51:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_freestack(t_stack **stack)
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

int	get_stack_len(t_stack *stack)
{
	int		i;

	i = 0;
	while (stack != NULL)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

uint	greater_of(const uint x, const uint y)
{
	if (x > y)
		return (x);
	return (y);
}
