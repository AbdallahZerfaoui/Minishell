#include "../minishell.h"

char	*get_env_value(const char *keyword, char **env)
{
	int		i;
	char	*value;
	int		keyword_len;

	i = 0;
	keyword_len = ft_strlen(keyword);
	while (env[i])
	{
		if (ft_strncmp(env[i], keyword, keyword_len) == 0)
		{
			value = ft_strdup(env[i] + keyword_len + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int count_expansion_chars(char *word)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\"' || word[i] == '\'')
		{
			count++;
			i++;
			// while (word[i] && word[i] != word[i - 1])
			// 	i++;
		}
		else if (word[i] == '$')
		{
			count++;
			i++;
			// while (word[i] && ft_isalnum(word[i]))
			// 	i++;
		}
		else
			i++;
	}
	return (count);
}

char	*expand_part(const char *word, char **env)
{
	char	*expanded;
	char	*expanded_tmp;
	int		$_can_expand;
	int		end;
	int		len;

	expanded = ft_strdup(word);
	expanded_tmp = ft_strdup("");
	$_can_expand = 1;
	while (strcmp(expanded, expanded_tmp) != 0 && expanded && *expanded != '\0')
	{
		free(expanded_tmp);
		expanded_tmp = ft_strdup(expanded);
		len = ft_strlen(expanded_tmp);
		end = len - 1;
		// free(expanded);
		if (expanded_tmp[0] == '\"' && expanded_tmp[end] == '\"')
			expanded = ft_substr(expanded_tmp, 1, len - 2);
		if (expanded_tmp[0] == '\'' && expanded_tmp[end] == '\'')
		{
			expanded = ft_substr(expanded_tmp, 1, end - 1);
			if (expanded_tmp[1] == '$')
				$_can_expand = 0;
		}
		if (expanded_tmp[0] == '$' && $_can_expand)
		{
			expanded = ft_strdup(get_env_value(expanded_tmp + 1, env));
			if (!expanded)
				return (ft_strdup(""));
		}
	}
	return (expanded);
}

char	*expand_word(char *word, char **env)
{
	char *current_char;
	char *end_last_part;
	char *expanded;
	int len;
	int can_expand;

	printf("count_expansion_chars = %d\n", count_expansion_chars(word));
	printf("word = %s\n", word);
	if (count_expansion_chars(word) == 0)
		return (ft_strdup(word));
	can_expand = 1;
	expanded = ft_strdup("");
	end_last_part = word - 1;
	current_char = word;
	while (*current_char != '\0')
	{
		if (*current_char == '\"' || *current_char == '\'')
		{
			if (current_char - end_last_part > 1)
			{
				expanded = ft_strjoin(expanded, ft_substr(end_last_part + 1, 0, current_char - end_last_part - 1));
			}
			// if (*current_char == '\'' && *(current_char + 1) == '$')
			// 	can_expand = 0;
			end_last_part = ft_strchr(current_char + 1, *current_char);
			if (!end_last_part)
				exit(1);
			len = end_last_part - current_char + 1;
			if (len > 2)
			{
				expanded = ft_strjoin(expanded, expand_part(ft_substr(current_char, 0, len), env));
			}
			current_char = end_last_part;
		}
		current_char ++;
	}
	if (current_char - end_last_part > 1)
	{
		expanded = ft_strjoin(expanded, expand_part(ft_substr(end_last_part + 1, 0, current_char - end_last_part + 1), env));
	}
	return (expand_word(expanded, env));
}

int main(int argc, char **argv, char **env)
{
	// char *word = "\"$USER\"USER 'hello' abdallah zerfaoui";
	// char *word = "\"$USER\"USER\"123\"";
	char *word = "\"$HOME\"abdallahzerfaoui\'$USER\'";
	char *expanded = expand_word(word, env);
	if (!expanded)
		printf("expanded = NULL\n");
	printf("expanded = %s\n", expanded);
	return (0);
}

// ""$HOME"adaljalsdjsaldj'$US'"