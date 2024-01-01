/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_moves_to_order.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:29:58 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/01 23:47:13 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

enum e_moves_mode{
	NONE,
	M2FD,
	M2LD,
	M2FA_M2LB,
	M2LA_M2FB
};

static void reset_node_moves(t_stack *node){
	node->m2fa = 0;
	node->m2la = 0;
	node->m2fb = 0;
	node->m2lb = 0;
	node->total_moves = 0;
	node->moves_mode = NONE;
}

static __u_int moves_to_prepare_a(int order, const t_stack *a_first){
	t_stack	*n;
	int 	min;
	__u_int	moves;

	n = (t_stack *)a_first;
	moves = 1;
	min = a_first->order;
	while (n->next != NULL)
	{
		if (min > n->order)
			min = n->order;
		if (n->order < order && order < n->next->order)
			return moves;
		n = n->next;
		moves++;
	}
	if (n->order < order && order < a_first->order)
		return 0;
	moves = 0;
	n = (t_stack *)a_first;
	while (n != NULL)
	{
		if (n->order == min)
			return moves;
		moves++;
	}
	return MAX_INT;
}

static __u_int greater_of(const __u_int x, const __u_int y)
{
	if (x > y)
		return x;
	return y;
}

static void set_node_total_moves(t_stack *n)
{
	const __u_int	m2fa_m2lb = n->m2fa + n->m2lb;
	const __u_int	m2la_m2fb = n->m2la + n->m2fb;
	const __u_int	m2fD = greater_of(n->m2fa, n->m2fb);
	const __u_int	m2lD = greater_of(n->m2la, n->m2lb);

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
	printf("m2fb %u\tm2lb %u\tm2fa %u\tm2la %u\tmoves %u\t"\
	, n->m2fb, n->m2lb, n->m2fa, n->m2la, n->total_moves);
	printf("m2fD %u\tm2lD %u\tm2fa_m2lb %u\tm2la_m2fb %u\t\n"\
	, m2fD, m2lD, m2fa_m2lb, m2la_m2fb);
}

static void less_moves_to_order2(t_stack **a, const size_t a_len, t_stack **b, const size_t b_len){
	t_stack	*node;
	__u_int	m2fb;

	node = *b;
	m2fb = 0;
	while (node != NULL)
	{
		reset_node_moves(node);
		node->m2fb = m2fb;
		node->m2lb = b_len - m2fb;
		node->m2fa = moves_to_prepare_a(node->order, *a);
		node->m2la = a_len - node->m2fa;
		set_node_total_moves(node);
		node = node->next;
		m2fb++;
	}
}

void less_moves_to_order(t_stack_extended *a, t_stack_extended *b){

	// (void)a;
	// (void)b;

	// while (b->len != 0)
	// {
		less_moves_to_order2(a->s, a->len, b->s, b->len);

	// }
}
