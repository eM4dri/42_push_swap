/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_node_moves.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:29:58 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 17:50:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_movestoa
{
	uint	min;
	uint	moves;
	uint	moves_to_min;
}t_movestoa;

static void	reset_node_moves(t_stack *node)
{
	node->m2fa = 0;
	node->m2la = 0;
	node->m2fb = 0;
	node->m2lb = 0;
	node->total_moves = 0;
	node->moves_mode = NONE;
}

static void	update_min_moves_min(const uint order, t_movestoa *u)
{
	u->min = order;
	u->moves_to_min = u->moves -1;
}

static uint	moves_to_prepare_a(uint order, const t_stack *a_first)
{
	t_stack		*n;
	t_movestoa	u;

	n = (t_stack *)a_first;
	u.moves = 1;
	u.moves_to_min = 0;
	u.min = a_first->order;
	while (n->next != NULL)
	{
		if (u.min > n->order)
			update_min_moves_min(n->order, &u);
		if (n->order < order && order < n->next->order)
			return (u.moves);
		n = n->next;
		u.moves++;
	}
	if (u.min > n->order)
		update_min_moves_min(n->order, &u);
	if (n->order < order && order < a_first->order)
		return (0);
	return (u.moves_to_min);
}

static void	set_node_total_moves(t_stack *n)
{
	const uint	m2fa_m2lb = n->m2fa + n->m2lb;
	const uint	m2la_m2fb = n->m2la + n->m2fb;
	const uint	m2fd = greater_of(n->m2fa, n->m2fb);
	const uint	m2ld = greater_of(n->m2la, n->m2lb);

	if (m2fd <= m2ld && m2fd <= m2fa_m2lb && m2fd <= m2la_m2fb)
		n->moves_mode = M2FD;
	else if (m2ld <= m2fd && m2ld <= m2fa_m2lb && m2ld <= m2la_m2fb)
		n->moves_mode = M2LD;
	else if (m2fa_m2lb < m2la_m2fb)
		n->moves_mode = M2FA_M2LB;
	else
		n->moves_mode = M2LA_M2FB;
	n->total_moves = 0;
	n->total_moves += (M2FD == n->moves_mode) * m2fd;
	n->total_moves += (M2LD == n->moves_mode) * m2ld;
	n->total_moves += (M2FA_M2LB == n->moves_mode) * m2fa_m2lb;
	n->total_moves += (M2LA_M2FB == n->moves_mode) * m2la_m2fb;
}

void	calculate_node_moves(t_stack_extended *a, t_stack_extended *b)
{
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
