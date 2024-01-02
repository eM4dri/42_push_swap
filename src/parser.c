/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:08 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 16:25:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Validates if the nbr exist already in the stack
* @param nbr    nbr to process
* @param stack	stack
*/
static int	exists(int nbr, t_stack *stack)
{
	while (stack != NULL)
	{
		if (stack->nbr == nbr)
			return (1);
		stack = stack->next;
	}
	return (0);
}

/**
 * * Validates string contents INT within range
* @param s_nbr  string to process
*/
static int	valid_range_int(const char *s_nbr)
{
	long	l;
	long	is_signed;

	l = 0;
	is_signed = (long)(s_nbr[0] == '-');
	while (*s_nbr != '\0' && !ft_isspace(*s_nbr) && l < MAX_INT)
	{
		if (ft_isdigit(*s_nbr))
			l = l * 10 + *s_nbr - '0';
		s_nbr++;
	}
	if (l > MAX_INT + is_signed)
		return (0);
	return (1);
}

/**
 * * Validates allowed characters(INT) & return size string read
 * * Acept just one char as sign
* @param s_nbr  string to process
*/
static int	check_nbr(char *const_s_nbr)
{
	char	*s_nbr;

	s_nbr = (char *)const_s_nbr;
	if (!(ft_isdigit(s_nbr[0])) && \
	!(ft_isdigit(s_nbr[1]) && (s_nbr[0] == '-' || s_nbr[0] == '+')))
		return (0);
	if (*s_nbr == '-' || *s_nbr == '+')
		s_nbr++;
	while (*s_nbr != '\0' && !ft_isspace(*s_nbr))
	{
		if (!ft_isdigit(*s_nbr))
			return (0);
		s_nbr++;
	}
	return (s_nbr - const_s_nbr);
}

/**
 * * Add new nbr into stack at back
 * * Set position and order considering the rest of items
* @param stack	stack
* @param nbr	new number to link
*/
static void	ft_lstadd_back_nbr(t_stack **stack, int nbr)
{
	t_stack	*aux;
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	new->nbr = nbr;
	new->pos = 1;
	new->order = 1;
	new->next = NULL;
	if (*stack == NULL)
		*stack = new;
	else
	{
		aux = *stack;
		aux->order += (aux->nbr > new->nbr);
		new->order += (new->nbr > aux->nbr);
		while (new->pos++ && aux->next != NULL)
		{
			aux = aux->next;
			aux->order += (aux->nbr > new->nbr);
			new->order += (new->nbr > aux->nbr);
		}
		aux->next = new;
	}
}

/**
 * * Parse nbr & add this to the back of the stack
 * * Ignore ISSPACE(3) at beginning
* @param s_nbr  string to process
* @param stack	stack
*/
int	parse_nbr(char *s_nbr, t_stack **stack)
{
	int	nbr;
	int	read;

	while (ft_isspace(*s_nbr))
		s_nbr++;
	read = check_nbr(s_nbr);
	if (!read)
		return (0);
	if (!valid_range_int(s_nbr))
		return (0);
	nbr = ft_atoi(s_nbr);
	if (exists(nbr, *stack))
		return (0);
	ft_lstadd_back_nbr(stack, nbr);
	s_nbr += read;
	while (ft_isspace(*s_nbr))
		s_nbr++;
	if (*s_nbr != '\0')
		return (parse_nbr(s_nbr, stack));
	return (1);
}
