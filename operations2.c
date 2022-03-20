/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:57:27 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 13:55:14 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * rotate
 * * Shift up all elements of stack a by 1. The first element becomes
the last one.
* @param stack		stack
*/
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*aux;

	if (*stack != NULL)
	{
		first = *stack;
		if (first->next != NULL)
		{
			aux = *stack;
			*stack = aux->next;
			while (aux->next != NULL)
			{
				aux = aux->next;
			}
			first->next = NULL;
			aux->next = first;
		}
	}
}

void	ft_rotate(t_stack **a, t_stack **b, int mode)
{
	if (mode == STACKA)
		write(1, "ra\n", 3);
	else if (mode == STACKB)
		write(1, "rb\n", 3);
	else if (mode == BOTHSTACKS)
		write(1, "rr\n", 3);
	if (mode == STACKA || mode == BOTHSTACKS)
		rotate(a);
	if (mode == STACKB || mode == BOTHSTACKS)
		rotate(b);
}

/**
 * reverse_rotate
 * * Shift down all elements of stack a by 1. The last element
becomes the first one
* @param stack		stack
*/
static void	reverse_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*old_last;
	t_stack	*new_last;

	if (*stack != NULL)
	{
		new_last = *stack;
		if (new_last->next != NULL)
		{
			old_last = new_last->next;
			while (old_last->next != NULL)
			{
				old_last = old_last->next;
				new_last = new_last->next;
			}
			first = *stack;
			*stack = old_last;
			old_last->next = first;
			new_last->next = NULL;
		}
	}
}

void	ft_reverse_rotate(t_stack **a, t_stack **b, int mode)
{
	if (mode == STACKA)
		write(1, "rra\n", 4);
	else if (mode == STACKB)
		write(1, "rrb\n", 4);
	else if (mode == BOTHSTACKS)
		write(1, "rrr\n", 4);
	if (mode == STACKA || mode == BOTHSTACKS)
		reverse_rotate(a);
	if (mode == STACKB || mode == BOTHSTACKS)
		reverse_rotate(b);
}
