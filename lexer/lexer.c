/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:52:45 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 20:37:29 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_type(const char *str)
{
	if (str[0] == TK_PIPE)
		return (PIPE);
	else if (str[0] == TK_LESS)
		return (INFILE);
	else if (str[0] == TK_GREATER)
		return (OUTFILE);
	else
		return (WORD);
}

t_token	*array2linked_list(char **array)
{
	t_token			*head;
	t_token			*new;
	size_t			i;
	t_token_type	type;

	i = 0;
	head = NULL;
	while (array[i])
	{
		type = get_type(array[i]);
		// printf("array[%zu] = %s\n", i, array[i]);
		new = create_token(array[i], type);
		if (!new)
			return (NULL);
		// printf("value = %s\n", new->value);
		append_token(&head, new);
		i++;
	}
	return (head);
}

t_token	*lexer(const char *line)
{
	char	**splited_line;
	t_token	*tokens;

	if (!line)
		return (NULL);
	splited_line = lex_split(line);
	// printf("splited_line[0] = %s\n", splited_line[0]);
	tokens = array2linked_list(splited_line);
	return (tokens);
}

int main(void)
{
	t_token	*tokens;
	// char	*line = "cat<\"input file\">\"output file\" | <\"cat\">file | <ls -la | grep \".txt\" | sort | wc -l > output.txt";
	char *line = "ls -la << grep \".txt\" >> sort | wc -l > output.txt";

	tokens = lexer(line);
	while (tokens)
	{
		printf("value = %s	-	", tokens->value);
		printf("type = %d\n", tokens->type);
		tokens = tokens->next;
	}
	return (0);
}
