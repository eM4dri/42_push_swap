/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_moves_to_order.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:29:58 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 18:03:25 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*less_moves_to_order_next(
	t_stack_extended *a,
	t_stack_extended *b
)
{
	t_stack	*node;
	t_stack	*min_moves_node;
	uint	min;

	calculate_node_moves(a, b);
	node = *b->s;
	min_moves_node = node;
	min = node->total_moves;
	while (node != NULL)
	{
		if (min == node->total_moves && min_moves_node->order > node->order)
			min_moves_node = node;
		else if (min > node->total_moves)
		{
			min = node->total_moves;
			min_moves_node = node;
		}
		node = node->next;
	}
	return (min_moves_node);
}

static void	finals_moves(t_stack **a, t_stack **b, const uint alen)
{
	t_stack	*node;
	uint	m2fa;
	uint	m2la;

	node = *a;
	m2fa = 0;
	while (node->order != 1)
	{
		node = node->next;
		m2fa++;
	}
	m2la = alen - m2fa;
	if (m2fa < m2la)
		while (m2fa--)
			ft_rotate(a, b, STACKA);
	else
		while (m2la--)
			ft_reverse_rotate(a, b, STACKA);
}

void	less_moves_to_order(t_stack_extended *a, t_stack_extended *b)
{
	t_stack	*node;

	while (b->len != 0)
	{
		node = less_moves_to_order_next(a, b);
		move_node_to_a(a->s, b->s, node);
		push_ext(a, b, STACKA);
	}
	finals_moves(a->s, b->s, a->len);
}
