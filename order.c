/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:14:54 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 16:33:48 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Order asc length 3 stack 
* @param stack	stack
* @param mode	mode
*/
void	order3(t_stack **stack, int mode)
{
	int		first;
	int		second;
	int		third;
	t_stack	*aux;

	while (1)
	{
		aux = *stack;
		first = aux->nbr;
		second = aux->next->nbr;
		third = aux->next->next->nbr;
		if (second > first && second > third)
			ft_reverse_rotate(stack, stack, mode);
		else if (first > second && first > third)
			ft_rotate(stack, stack, mode);
		else if (first > second)
			ft_swap(stack, stack, mode);
		else
			break ;
	}
}

/**
 * * Order asc length 5 stack 
* @param a	stack 1
* @param b	stack 2
*/
void	order5(t_stack **a, t_stack **b)
{
	t_stack	*first;
	t_stack	*second;

	while (get_stack_len(*a) != 3)
	{
		first = *a;
		second = first->next;
		if (first->order == 1 || first->order == 2 || first->order == 5)
			ft_push(a, b, STACKB);
		else if (second->order == 1 || second->order == 2 || second->order == 5)
			ft_swap(a, b, STACKA);
		else
			ft_reverse_rotate(a, b, STACKA);
	}
	order3(a, STACKA);
	while (get_stack_len(*b) != 0)
	{
		ft_push(a, b, STACKA);
		first = *a;
		if (first->order == 5)
			ft_rotate(a, b, STACKA);
		else if (first->order == 2 && first->next->order == 1)
			ft_swap(a, b, STACKA);
	}
}
