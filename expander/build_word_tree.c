/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_word_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:23:21 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 14:14:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_expansion_unit	*create_expansion_unit(const char *value)
// {
// 	t_expansion_unit	*new;

// 	new = (t_expansion_unit *)ft_calloc(1, sizeof(t_expansion_unit));
// 	if (!new)
// 		return (NULL);
// 	new->value = ft_strdup(value);
// 	new->can_expand = 1;
// 	return (new);
// }

// void	append_expansion_unit(t_expansion_unit **head, t_expansion_unit *new_unit)
// {
// 	t_expansion_unit	*last;

// 	if (!*head)
// 	{
// 		*head = new_unit;
// 		return ;
// 	}
// 	last = *head;
// 	while (last->next)
// 		last = last->next;
// 	last->next = new_unit;
// 	new_unit->next = NULL;
// }
t_tree_node	*create_tree_node(const char *value)
{
	t_tree_node	*new;

	new = (t_tree_node *)ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->can_expand = 1;
	new->parent = NULL;
	new->children = NULL;
	new->next_sibling = NULL;
	return (new);
}

t_tree_node	*get_last_child(t_tree_node *node)
{
	t_tree_node	*last;
	
	if (!node || !node->children)
		return (NULL);
	last = node->children;
	while (last && last->next_sibling)
		last = last->next_sibling;
	return (last);
}

// t_tree_node	*get_last_sibling(t_tree_node *node)
// {
// 	t_tree_node	*last;
	
// 	last = node->next_sibling;
// 	while (last && last->next_sibling)
// 		last = last->next_sibling;
// 	return (last);
// }

void append_child(t_tree_node **head, t_tree_node *new_node)
{
	t_tree_node	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->parent = NULL;
		return ;
	}
	last = get_last_child(*head);
	if (!last)
	{
		(*head)->children = new_node;
		new_node->parent = *head;
		return ;
	}
	last->next_sibling = new_node;
	new_node->next_sibling = NULL;
	new_node->parent = last->parent;
}

int		get_depth(t_tree_node *root)
{
	int	depth;

	depth = 0;
	while (root)
	{
		depth++;
		root = root->children;
	}
	return (depth);
}
	

// void	append_sibling(t_tree_node **head, t_tree_node *new_node)
// {
// 	t_tree_node	*last;

// 	if (!*head)
// 	{
// 		*head = new_node;
// 		new_node->parent = NULL;
// 		return ;
// 	}
// 	last = *head;
// 	while (last->next_sibling)
// 		last = last->next_sibling;
// 	last->next_sibling = new_node;
// 	new_node->next_sibling = NULL;
// 	new_node->parent = last->parent;
// }

int are_empty_quotes(const char *word)
{
	if (ft_strlen(word) == 2
	&& (word[0] == TK_D_QUOTE || word[0] == TK_S_QUOTE)
	&& word[1] == word[0])
		return (1);
	else
		return (0);
}

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

int	count_quotes(char *word)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (!word || *word == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] == TK_D_QUOTE || word[i] == TK_S_QUOTE)
			count++;
		i++;
	}
	return (count);
}

int	is_expansion_done(char *word)
{
	if (count_quotes(word) == 0)
		return (1);
	else if (are_empty_quotes(word))
		return (1);
	return (0);
}

// char	*expand_part(const char *word, char **env)
// {
// 	char	*expanded;
// 	char	*expanded_tmp;
// 	int		$_can_expand;
// 	int		end;
// 	int		len;

// 	printf("part = %s\n", word);
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
// char	*expand_part(const char *word, char **env)
// {
// 	char	*expanded;
// 	char	*expanded_tmp;
// 	int		$_can_expand;
// 	int		end;
// 	int		len;

// 	// printf("part = %s\n", word);
// 	expanded = ft_strdup(word);
// 	expanded_tmp = ft_strdup("");
// 	$_can_expand = 1;
// 	while (strcmp(expanded, expanded_tmp) != 0 && expanded && *expanded != '\0')
// 	{
// 		// free(expanded_tmp);
// 		expanded_tmp = ft_strdup(expanded);
// 		len = ft_strlen(expanded_tmp);
// 		end = len - 1;
// 		// free(expanded);
// 		if (expanded_tmp[0] == TK_D_QUOTE && expanded_tmp[end] == TK_D_QUOTE)
// 			expanded = ft_substr(expanded_tmp, 1, len - 2);
// 		else if (expanded_tmp[0] == TK_S_QUOTE && expanded_tmp[end] == TK_S_QUOTE)
// 		{
// 			expanded = ft_substr(expanded_tmp, 1, end - 1);
// 			return (expanded);
// 			// if (expanded_tmp[1] == '$')
// 			// 	$_can_expand = 0;
// 		}
// 		else if (expanded_tmp[0] == '$')
// 		{
// 			expanded = ft_strdup(getenv(expanded_tmp + 1));
// 			if (!expanded)
// 				return (ft_strdup(""));
// 		}
// 	}
// 	return (expanded);
// }

// char	*expand_word(char *word, char **env)
// {
// 	char *current_char;
// 	char *end_last_part;
// 	char *expanded;
// 	int len;
// 	// int can_expand;

// 	printf("word = %s\n", word);
// 	if (is_expansion_done(word) || !word || *word == '\0')
// 		return (word);
// 	// printf("count_quotes = %d\n", count_quotes(word));
// 	// if (count_quotes(word) == 0)
// 	// 	return (ft_strdup(word));
// 	// can_expand = 1;
// 	expanded = ft_strdup("");
// 	end_last_part = word - 1;
// 	current_char = word;
// 	while (*current_char != '\0')
// 	{
// 		if (*current_char == '\"' || *current_char == '\'')
// 		{
// 			if (current_char - end_last_part > 1)
// 			{
// 				expanded = ft_strjoin(expanded, ft_substr(end_last_part + 1, 0, current_char - end_last_part - 1));
// 			}
// 			// if (*current_char == '\'' && *(current_char + 1) == '$')
// 			// 	can_expand = 0;
// 			end_last_part = ft_strchr(current_char + 1, *current_char);
// 			if (!end_last_part)
// 				exit(1);
// 			len = end_last_part - current_char + 1;
// 			if (len > 2)
// 			{
// 				expanded = ft_strjoin(expanded, expand_part(ft_substr(current_char, 0, len), env));
// 			}
// 			current_char = end_last_part;
// 		}
// 		current_char ++;
// 	}
// 	if (current_char - end_last_part > 1)
// 	{
// 		expanded = ft_strjoin(expanded, expand_part(ft_substr(end_last_part + 1, 0, current_char - end_last_part + 1), env));
// 	}
// 	return (expand_word(expanded, env));
// }
/***
 * @note be careful this function is recursive
 */
t_tree_node	*build_word_tree(char *word, char **env)
{
	char *current_char;
	char *end_last_part;
	char *sub_word;
	int len;
	static int inside_d_quotes;
	t_tree_node *root;
	t_tree_node *new_node;

	root = create_tree_node(word);
	if (!root)
		exit(1);
	if (!word || *word == '\0') // i have removed the condition are_empty_quotes(word)
		return (NULL);
	else if (are_empty_quotes(word))
	{
		return (create_tree_node(""));
	}
	else if (ft_strlen(word) >= 2 && word[0] == TK_BACK_SLASH
		&& (word[1] == word[0] || word[1] == TK_DOLLAR))
	{
		new_node = create_tree_node(ft_substr(word, 0, 2));
		if (new_node)
			append_child(&root, new_node);
		new_node = build_word_tree(word + 2, env);
		if (new_node)
			append_child(&root, new_node);
	}
	else if (is_expansion_done(word))
	{
		return (create_tree_node(word));
	}
	else if (count_quotes(word) == 0 && ft_strlen(word) > 0)
	{
		return (create_tree_node(word));
	}
	current_char = word;
	while (*current_char != '\0')
	{
		if (*current_char == TK_D_QUOTE)
		{
			inside_d_quotes = !inside_d_quotes;
		}
		// printf("current_char = %c - inside quotes = %d\n", *current_char, inside_d_quotes);
		if (*current_char == TK_D_QUOTE
			|| (*current_char == TK_S_QUOTE && !inside_d_quotes))
		{
			end_last_part = ft_strchr(current_char + 1, *current_char);
			if (!end_last_part)
				return (NULL);
			len = end_last_part - current_char - 1; // we remove the quotes
			sub_word = ft_substr(current_char + 1, 0, len);
			if (ft_strcmp(sub_word, word) != 0
				&& *current_char == TK_D_QUOTE
				&& sub_word && *sub_word != '\0')
			{
				// printf("sub_word = *%s*\n", sub_word);
				// new_node = create_tree_node(sub_word);
				new_node = build_word_tree(sub_word, env);
				if (new_node)
				{
					append_child(&root, new_node);
				}
			}
			else if (*current_char == TK_S_QUOTE && !inside_d_quotes)
			{
				new_node = create_tree_node(sub_word);
				if (new_node)
				{
					new_node->can_expand = 0;
					append_child(&root, new_node);
				}
			}
			else if (*current_char == TK_S_QUOTE && inside_d_quotes)
			{
				sub_word = ft_substr(current_char, 0, len + 2); // we keep the s quotes
				new_node = create_tree_node(sub_word);
				if (new_node)
				{
					append_child(&root, new_node);
				}
			}
			current_char = end_last_part;
			if (*end_last_part == TK_D_QUOTE)
				inside_d_quotes = !inside_d_quotes;
		}
		else //normal word
		{
			len = 0;
			while (*current_char != TK_D_QUOTE
				&& (*current_char != TK_S_QUOTE || inside_d_quotes)
				&& *current_char != '\0')
			{
				len++;
				current_char++;
			}
			sub_word = ft_substr(current_char - len, 0, len);
			if (!sub_word)
				exit(1);
			// printf("sub_word = %s word %s len = %d\n", sub_word, word, len);
			if (ft_strcmp(sub_word, word) != 0)
			{
				new_node = build_word_tree(sub_word, env);
				if (new_node)
					append_child(&root, new_node);
			}
			if (current_char > word && !inside_d_quotes)
				current_char --;
		}
		current_char ++;
	}
	// print_tree(root, 0, 1);
	return (root);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_tree_node *root;
// 	// char *word = "\"$USER\"USER 'hello' abdallah zerfaoui";
// 	// char *word = "\"$USER\"USER\"123\"";
// 	// char *word = "\"$HOME\"abdallahzerfaoui\'$USER\'";
// 	// char *word = "\"\"$USER\"USER 'hello'\" abdallah zerfaoui";	//doesnt work
// 	// char *word = "\"\'\'$USER\'USER\' \'hello\'\"";
// 	// char *word = "\"$USER\"USER '$hello' abdallah zerfaoui \'parent \"$child\" parent\'";
// 	char *word = "\"$USER\"USER '$hello' abdallah zerfaoui \"parent \'$child\' parent\"";
// 	// root = create_tree_node(word);
// 	char *expanded = NULL;
// 	root = build_word_tree(word, env);
// 	process_nodes(root);
// 	merge_tree_nodes(root, &expanded);
// 	// root = create_tree_node(word);
// 	// root->children = create_tree_node("abdallah");
// 	// root->children->next_sibling = create_tree_node("zerfaoui");
// 	// if (root)
// 	// 	printf("root = %s\n", root->value);
// 	// while (root)
// 	// {
// 	// 	printf("root = %s\n", root->value);
// 	// 	root = root->children;
// 	// }
// 	print_tree(root, 0, 1);
// 	printf("expanded = *%s*\n", expanded);
// 	// while (root)
// 	// {
// 	// 	printf("root : %s\n", root->value);
// 	// 	while (root->children)
// 	// 	{
// 	// 		printf("%s *", root->children->value);
// 	// 		root->children = root->children->next_sibling;
// 	// 	}
// 	// 	printf("\n");
// 	// 	root = root->next_sibling;
// 	// }
// 	// print_tree_wrapper(root);
	
// 	// if (!expanded)
// 	// 	printf("expanded = NULL\n");
// 	// printf("original_word = %s\n", word);
// 	// printf("expanded = %s\n", expanded);
// 	return (0);
// }

// ""$HOME"adaljalsdjsaldj'$US'"