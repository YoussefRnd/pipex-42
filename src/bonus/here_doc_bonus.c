/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:36:19 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 19:13:59 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

bool	is_here_doc(char **args)
{
	if (!ft_strncmp(args[1], "here_doc", 8))
		return (true);
	return (false);
}

void	here_doc(t_pipe *p)
{
	int		fd;
	char	*buffer;

	fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		error("Error opening here_doc file");
	while (true)
	{
		ft_putstr_fd("heredoc> ", 1);
		buffer = get_next_line(0);
		if (ft_strncmp(buffer, p->args[2], ft_strlen(buffer) - 1) == 0)
			break ;
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	free(buffer);
	close(fd);
	p->in_fd = open("/tmp/.here_doc", O_RDONLY);
	if (p->in_fd == -1)
	{
		unlink("/tmp/.here_doc");
		error("Error opening here_doc file");
	}
	unlink("/tmp/.here_doc");
}
