/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:36:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 16:12:59 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(i);
	filename = ft_strjoin("tmp_", tmp);
	filename = ft_strjoin(filename, "_heredoc.txt");
	i++;
	return (ft_strdup(filename));
}

/***
 * this function will loop to get the heredoc
 * and write it to a file
 * the file will be used as input for the command
 * @note we need the length of the line to remove the \n
 */
void	heredoc_loop(t_heredoc *heredoc)
{
	char	*line;
	int		hd_fd;
	size_t	len;

	hd_fd = open(heredoc->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (hd_fd == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: Failed to open heredoc file\n");
		return ;
	}
	while (true)
	{
		ft_putstr_fd(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!line || !ft_strcmp(line, heredoc->stop_word))
			break ;
		if ((*(heredoc->shell))->hd_must_expand)
			line = hd_expand_word(line, *(heredoc->shell));
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
	}
	close(hd_fd);
}
