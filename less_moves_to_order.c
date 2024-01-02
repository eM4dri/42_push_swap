/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_moves_to_order.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:29:58 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 16:58:44 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void reset_node_moves(t_stack *node){
	node->m2fa = 0;
	node->m2la = 0;
	node->m2fb = 0;
	node->m2lb = 0;
	node->total_moves = 0;
	node->moves_mode = NONE;
}

static uint moves_to_prepare_a(uint order, const t_stack *a_first){
	t_stack	*n;
	uint	min;
	uint	moves;
	uint	moves_to_min;

	n = (t_stack *)a_first;
	moves = 1;
	moves_to_min = 0;
	min = a_first->order;
	while (n->next != NULL)
	{
		if (min > n->order){
			min = n->order;
			moves_to_min = moves - 1;
		}
		if (n->order < order && order < n->next->order)
			return moves;
		n = n->next;
		moves++;
	}
	if (min > n->order){
		min = n->order;
		moves_to_min = moves - 1;
	}
	if (n->order < order && order < a_first->order)
		return 0;
	return moves_to_min;
}

static uint greater_of(const uint x, const uint y)
{
	if (x > y)
		return x;
	return y;
}

static void set_node_total_moves(t_stack *n)
{
	const uint	m2fa_m2lb = n->m2fa + n->m2lb;
	const uint	m2la_m2fb = n->m2la + n->m2fb;
	const uint	m2fD = greater_of(n->m2fa, n->m2fb);
	const uint	m2lD = greater_of(n->m2la, n->m2lb);

	if (m2fD <= m2lD && m2fD <= m2fa_m2lb && m2fD <= m2la_m2fb)
		n->moves_mode = M2FD;
	else if (m2lD <= m2fD && m2lD <= m2fa_m2lb && m2lD <= m2la_m2fb)
		n->moves_mode = M2LD;
	else if (m2fa_m2lb < m2la_m2fb)
		n->moves_mode = M2FA_M2LB;
	else
		n->moves_mode = M2LA_M2FB;
	n->total_moves = 0;
	n->total_moves += (M2FD == n->moves_mode) * m2fD;
	n->total_moves += (M2LD == n->moves_mode) * m2lD;
	n->total_moves += (M2FA_M2LB == n->moves_mode) * m2fa_m2lb;
	n->total_moves += (M2LA_M2FB == n->moves_mode) * m2la_m2fb;
}

static void calculate_node_moves(t_stack_extended *a, t_stack_extended *b){
	t_stack	*node;
	uint	m2fb;

	node = *b->s;
	m2fb = 0;
	while (node != NULL)
	{
		reset_node_moves(node);
		node->m2fb = m2fb;
		node->m2lb = b->len - m2fb;
		node->m2fa = moves_to_prepare_a(node->order, *a->s);
		node->m2la = a->len - node->m2fa;
		set_node_total_moves(node);
		node = node->next;
		m2fb++;
	}
}

static t_stack *less_moves_to_order_next(t_stack_extended *a, t_stack_extended *b){
	t_stack	*node;
	t_stack	*min_moves_node;
	uint	min;

	calculate_node_moves(a, b);
	node = *b->s;
	min_moves_node = node;
	min = node->total_moves;
	while (node != NULL)
	{
		if (min > node->total_moves)
		{
			min = node->total_moves;
			min_moves_node = node;
		} 
		else if (min == node->total_moves && min_moves_node->order > node->order)
			min_moves_node = node;
		node = node->next;
	}
	return min_moves_node;
}

void less_moves_to_order(t_stack_extended *a, t_stack_extended *b){
	t_stack	*node;
	int		m2fa;
	int		m2la;

	while (b->len != 0)
	{
		node = less_moves_to_order_next(a, b);
		move_node_to_a(a->s, b->s, node);
		push_ext(a, b, STACKA);
	}
	node = *a->s;
	m2fa = 0;
	while (node->order != 1)
	{
		node = node->next;
		m2fa++;
	}
	m2la = a->len - m2fa;
	if (m2fa < m2la)
	{
		while (m2fa--)
			ft_rotate(a->s, b->s, STACKA);
	}
	else
	{
		while (m2la--)
			ft_reverse_rotate(a->s, b->s, STACKA);
	}
}

