/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:14:54 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/05 12:56:00 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Order desc length 3 stack 
* @param stack	stack
* @param mode	mode
*/
void	reverseorder3(t_stack **stack, int mode)
{
	int		first;
	int		second;
	int		third;
	t_stack	*aux;

	while (1)
	{
		aux = *stack;
		first = aux->nbr * -1;
		second = aux->next->nbr * -1;
		third = aux->next->next->nbr * -1;
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

/**
 * * Get nececesary moves to get next number
* @param stack	stack
* @param nbr	number
* @param len	stack len
*/
static int	get_next_move_default(t_stack *stack, int nbr, int len)
{
	int	first;
	int	last;
	int	i;

	i = 0;
	first = 0;
	last = -len;
	while (stack != NULL)
	{
		if (stack->order == nbr)
		{
			first = i;
			last = (len - i) * -1;
		}
		stack = stack->next;
		i++;
	}
	if (first <= (last * -1))
		return (first);
	return (last);
}

/**
 * * Order asc a returning intructions on out 
* @param a	stack 1
* @param b	stack 2
*/
void	orderbydefault(t_stack **a, t_stack **b)
{
	int	len;
	int	move;
	int	next;

	next = 0;
	move = 0;
	len = get_stack_len(*a);
	while (len)
	{
		move = get_next_move_default(*a, ++next, len--);
		while (move > 0 && move--)
			ft_rotate(a, b, STACKA);
		while (move < 0 && move++)
			ft_reverse_rotate(a, b, STACKA);
		ft_push(a, b, STACKB);
	}
	while (next--)
		ft_push(a, b, STACKA);
}
