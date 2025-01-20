/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:36:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/20 21:32:10 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_loop(char *stop_word)
{
	char	*line;
	int		hd_fd;

	hd_fd = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (hd_fd == -1)
	{
		perror("pipe error");
		return ;
	}
	line = NULL;
	while (true)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strcmp(line, stop_word))
			break ;
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
	}
	close(hd_fd);
}
