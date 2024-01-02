/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_node_to_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:48:58 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 17:11:03 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_m2la_m2fb(t_stack **a, t_stack **b, t_stack *n)
{
	while (n->m2fb > 0)
	{
		ft_rotate(a, b, STACKB);
		n->m2fb--;
	}
	while (n->m2la > 0)
	{
		ft_reverse_rotate(a, b, STACKA);
		n->m2la--;
	}
}

static void	move_m2fa_m2lb(t_stack **a, t_stack **b, t_stack *n)
{
	while (n->m2fa > 0)
	{
		ft_rotate(a, b, STACKA);
		n->m2fa--;
	}
	while (n->m2lb > 0)
	{
		ft_reverse_rotate(a, b, STACKB);
		n->m2lb--;
	}
}

static void	move_m2ld(t_stack **a, t_stack **b, t_stack *n)
{
	while (n->m2lb > 0 && n->m2la > 0)
	{
		ft_reverse_rotate(a, b, BOTHSTACKS);
		n->m2lb--;
		n->m2la--;
	}
	while (n->m2lb > 0)
	{
		ft_reverse_rotate(a, b, STACKB);
		n->m2lb--;
	}
	while (n->m2la > 0)
	{
		ft_reverse_rotate(a, b, STACKA);
		n->m2la--;
	}
}

static void	move_m2fd(t_stack **a, t_stack **b, t_stack *n)
{
	while (n->m2fb > 0 && n->m2fa > 0)
	{
		ft_rotate(a, b, BOTHSTACKS);
		n->m2fb--;
		n->m2fa--;
	}
	while (n->m2fb > 0)
	{
		ft_rotate(a, b, STACKB);
		n->m2fb--;
	}
	while (n->m2fa > 0)
	{
		ft_rotate(a, b, STACKA);
		n->m2fa--;
	}
}

void	move_node_to_a(t_stack **a, t_stack **b, t_stack *n)
{
	if (n->moves_mode == M2FD)
		move_m2fd(a, b, n);
	else if (n->moves_mode == M2LD)
		move_m2ld(a, b, n);
	else if (n->moves_mode == M2FA_M2LB)
		move_m2fa_m2lb(a, b, n);
	else if (n->moves_mode == M2LA_M2FB)
		move_m2la_m2fb(a, b, n);
}
