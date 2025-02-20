/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:02:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/20 16:58:19 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_standalone_redirections(t_token *tokens, t_shell **shell)
{
	t_token	*current;
	t_token	*next;
	t_token	*prev;
	int		tmp_fd;
	// t_token	*tmp;
	// int		tmp_fd2;

	current = tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if ((current->type == OUTFILE || current->type == APPEND)
			&& (!prev || prev->type != WORD)
			&& (next && next->type == WORD))
		{
			if (current->type == OUTFILE)
				tmp_fd = open(next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				tmp_fd = open(next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (tmp_fd < 0)
			{
				ft_putstr_fd(STDERR_FILENO, "bash: : open error\n");
				(*shell)->exit_status = OPEN_ERROR;
				return (NULL);
			}
			if (current->next->next)
				tokens = current->next->next;
			else
				tokens = NULL;
			current = tokens;
			if (current && current->next)
				next = current->next;
		}
		else if (current->type == INFILE
			&& (!prev || prev->type != WORD)
			&& (next && next->type == WORD))
		{
			if (access(next->value, F_OK) == -1)
			{
				ft_putstr_fd(STDERR_FILENO, "bash: ");
				ft_putstr_fd(STDERR_FILENO, next->value);
				ft_putstr_fd(STDERR_FILENO, ": No such file or directory\n");
				(*shell)->exit_status = OPEN_ERROR;
				return (NULL);
			}
			// else
			// {
			// 	tmp_fd2 = open(next->value, O_RDONLY);
			// 	if (tmp_fd2 < 0)
			// 	{
			// 		ft_putstr_fd(STDERR_FILENO, "bash: : open error\n");
			// 		(*shell)->exit_status = OPEN_ERROR;
			// 		return (NULL);
			// 	}
			// 	dup2(tmp_fd2, STDIN_FILENO);
			// 	close(tmp_fd2);
			// 	remove_token(&tokens, current);
			// 	remove_token(&tokens, next);
			// 	current = move_forward_n(prev, 3);
			// 	if (current && current->type == PIPE)
			// 	{
			// 		tmp = current;
			// 		current = move_forward_n(prev, 1);
			// 		remove_token(&tokens, tmp);
			// 	}
			// 	next = move_forward_n(prev, 4);
			// 	prev = move_forward_n(prev, 2);
			// 	continue ;
			// }
		}
		prev = current;
		current = next;
	}
	return (tokens);
}

// int	len_tokens_lst(t_token *tokens)
// {
// 	int		len;
// 	t_token	*current;

// 	len = 0;
// 	current = tokens;
// 	while (current)
// 	{
// 		len++;
// 		current = current->next;
// 	}
// 	return (len);
// }

