/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:15:55 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 15:44:20 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

char	**ft_lsttoarr(t_list *lst)
{
	int		i;
	int		len;
	char	**arr;

	i = 0;
	len = ft_lstsize(lst);
	arr = malloc((len + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = lst->content;
		lst = lst->next;
		i++;
	}
	arr[len] = NULL;
	return (arr);
}

char	**split_cmd(char *s)
{
	t_list	*lst;
	char	*buffer;
	bool	in_quotes;
	char	*start;

	lst = NULL;
	in_quotes = false;
	start = s;
	while (*s)
	{
		if ((*s == ' ' && !in_quotes) || *(s + 1) == '\0')
		{
			buffer = ft_substr(start, 0, s - start + (*(s + 1) == '\0'));
			if (ft_strncmp(buffer, "\'", ft_strlen(buffer)) == 0
				|| ft_strncmp(buffer, "\"", ft_strlen(buffer)) == 0)
				ft_lstadd_back(&lst, ft_lstnew(buffer));
			else
				ft_lstadd_back(&lst, ft_lstnew(ft_strtrim(buffer, "\'\"")));
			start = s + 1;
		}
		else if (*s == '\'' || *s == '\"')
			in_quotes = !in_quotes;
		s++;
	}
	return (ft_lsttoarr(lst));
}
