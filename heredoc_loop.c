/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:36:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/11 14:23:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(i);
	filename = ft_strjoin("tmp_", tmp);
	filename = ft_strjoin(filename, "_heredoc.txt");
	// filename = ft_strjoin_all("tmp_", tmp, "_heredoc.txt", NULL);
	i++;
	return (ft_strdup(filename));
}

void	heredoc_loop(char *stop_word, char *hd_filename)
{
	char	*line;
	int		hd_fd;
	// char	*hd_filename;

	// hd_filename = generate_heredoc_filename();
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
