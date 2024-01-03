/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:17 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/03 16:08:25 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include "libft.h"
# define MAX_INT 2147483647
# define NO_ERROR 0

enum e_moves_allowed{
	UKNOWN,
	PA,
	PB,
	SA,
	SB,
	RRA,
	RRB,
	RRR,
	RA,
	RB,
	RR
};

typedef struct s_stack
{
	int				nbr;
	uint			pos;
	uint			order;
	struct s_stack	*next;
}t_stack;

int		parse_nbr(char *s_nbr, t_stack **stack);
void	ft_move(int move, t_stack **a, t_stack **b);

#endif
