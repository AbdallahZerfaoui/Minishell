/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:04:38 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/30 20:36:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_env_value(const char *keyword, char **env)
// {
// 	int		i;
// 	char	*value;
// 	int		keyword_len;

// 	i = 0;
// 	keyword_len = ft_strlen(keyword);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], keyword, keyword_len) == 0)
// 		{
// 			value = ft_strdup(env[i] + keyword_len + 1);
// 			if (!value)
// 				return (NULL);
// 			return (value);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*expand_word(const char *word, char **env)
// {
// 	char	*expanded;
// 	char	*expanded_tmp;
// 	int		$_can_expand;
// 	int		end;
// 	int		len;

// 	expanded = ft_strdup(word);
// 	expanded_tmp = ft_strdup("");
// 	$_can_expand = 1;
// 	while (strcmp(expanded, expanded_tmp) != 0 && expanded && *expanded != '\0')
// 	{
// 		free(expanded_tmp);
// 		expanded_tmp = ft_strdup(expanded);
// 		len = ft_strlen(expanded_tmp);
// 		end = len - 1;
// 		// free(expanded);
// 		if (expanded_tmp[0] == '\"' && expanded_tmp[end] == '\"')
// 			expanded = ft_substr(expanded_tmp, 1, len - 2);
// 		if (expanded_tmp[0] == '\'' && expanded_tmp[end] == '\'')
// 		{
// 			expanded = ft_substr(expanded_tmp, 1, end - 1);
// 			if (expanded_tmp[1] == '$')
// 				$_can_expand = 0;
// 		}
// 		if (expanded_tmp[0] == '$' && $_can_expand)
// 		{
// 			expanded = ft_strdup(get_env_value(expanded_tmp + 1, env));
// 			if (!expanded)
// 				return (ft_strdup(""));
// 		}
// 	}
// 	return (expanded);
// }

// t_token	*expand(t_token *tokens, char **env)
// {
// 	t_token	*head;
// 	t_token	*new;
// 	t_token	*tmp;

// 	head = NULL;
// 	while (tokens)
// 	{
// 		if (tokens->type == WORD && tokens->need_expand)
// 		{
// 			new = create_token(expand_word(tokens->value, env), WORD);
// 			if (!new)
// 				return (NULL);
// 			append_token(&head, new);
// 		}
// 		else
// 		{
// 			new = create_token(ft_strdup(tokens->value), tokens->type);
// 			if (!new)
// 				return (NULL);
// 			append_token(&head, new);
// 		}
// 		tmp = tokens;
// 		tokens = tokens->next;
// 		free(tmp->value);
// 		free(tmp);
// 	}
// 	return (head);
// }
