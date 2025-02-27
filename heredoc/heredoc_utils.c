/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:52 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 16:29:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /**
//  * this function removes the quotes from a string
//  * and returns 1 if the string was modified
//  * and 0 if it wasn't
//  */
int	count_segments(const char *str)
{
	int		i;
	int		segments;

	i = 0;
	segments = 0;
	while (str[i])
	{
		if (str[i] == TK_SPACE || str[i] == TK_DOLLAR
			|| str[i] == TK_S_QUOTE || str[i] == TK_D_QUOTE)
			segments++;
		i++;
	}
	return (segments);
}

char	*hd_expand_word(char *word, t_shell *shell)
{
	char	**split;
	char	*expanded;

	if (ft_strchr(word, TK_DOLLAR) == NULL)
		return (word);
	expanded = ft_strdup("");
	split = ft_split_heredoc(word);
	while (*split)
	{
		if (ft_strchr(*split, '$') != NULL)
			expanded = ft_strjoin(expanded, expand_word(*split, shell));
		else
			expanded = ft_strjoin(expanded, *split);
		split++;
	}
	return (expanded);
}

/**
 * return 1 if the variables inside of the heredoc need to expand
 * return 0 if they don't
 */
int	set_heredoc_expansion_flag(t_token *tokens)
{
	t_token	*current;
	int		need_expand;

	need_expand = 1;
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (current->next && current->next->type == WORD)
			{
				need_expand
					= (count_quotes(current->next->value) == 0);
				break ;
			}
		}
		current = current->next;
	}
	return (need_expand);
}

t_heredoc	*init_heredoc_struct(char *stop_word,
				char *hd_filename, t_shell **shell)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->stop_word = ft_strdup(stop_word);
	heredoc->filename = ft_strdup(hd_filename);
	heredoc->shell = shell;
	return (heredoc);
}
