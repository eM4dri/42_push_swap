/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:17 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 19:27:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>
# define MAX_INT 2147483647

enum e_move_stack{
	STACKA,
	STACKB,
	BOTHSTACKS
};

enum e_moves_mode{
	NONE,
	M2FD,
	M2LD,
	M2FA_M2LB,
	M2LA_M2FB
};

typedef struct s_chunk_size
{
	int	min;
	int	mid;
	int	max;
	int	size;
}t_chunk_sizes;
typedef struct s_stack
{
	int				nbr;
	uint			pos;
	uint			order;
	uint			m2fa;
	uint			m2la;
	uint			m2fb;
	uint			m2lb;
	uint			total_moves;
	short			moves_mode;
	struct s_stack	*next;
}t_stack;
typedef struct s_stack_extended
{
	t_stack	**s;
	uint	len;
}t_stack_extended;

int		parse_nbr(char *s_nbr, t_stack **stack);
void	ft_swap(t_stack **a, t_stack **b, int mode);
void	ft_push(t_stack **a, t_stack **b, int mode);
void	push_ext(t_stack_extended *a, t_stack_extended *b, int mode);
void	ft_rotate(t_stack **a, t_stack **b, int mode);
void	ft_reverse_rotate(t_stack **a, t_stack **b, int mode);
void	print_stack(t_stack *node);
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
