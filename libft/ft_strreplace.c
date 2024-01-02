/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:54:30 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/05 19:50:28 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*recursive_str_replace(const char *str, char const *oldset, \
	char const *newset, size_t index)
{
	char	*strnstr;
	char	*out;
	size_t	new_index;

	strnstr = ft_strnstr(&str[index], oldset, ULONG_MAX);
	if (strnstr != 0)
	{
		new_index = strnstr - str;
		out = recursive_str_replace(str, oldset, newset, \
			new_index + ft_strlen(oldset));
		out = ft_strjoin_freedouble(ft_strdup(newset), out);
		out = ft_strjoin_freedouble(ft_substr(str, index, \
			new_index - index), out);
		return (out);
	}
	else
		return (ft_strdup(&str[index]));
}

/**
 * * Returns a new string in which all occurrences of a specified string
 * * in the current instance are replaced with another specified string.
 * @param str		string to modify
 * @param oldset	string to be replaced.
 * @param newset	string to replace all occurrences of oldValue
*/
char	*ft_strreplace(const char *str, char const *oldset, char const *newset)
{
	char	*out;
	char	*strnstr;

	if (!str || !oldset || !newset)
		return (NULL);
	out = NULL;
	if (*oldset != '\0')
	{
		strnstr = ft_strnstr(str, oldset, ULONG_MAX);
		if (strnstr != 0)
			out = recursive_str_replace(str, oldset, newset, 0);
	}
	if (!out)
		out = ft_strdup(str);
	return (out);
}
