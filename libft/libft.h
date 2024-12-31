/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:01:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 22:30:57 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../collector/garbage_collector.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

// Functions of libc (23)
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n_bytes);
void				*ft_memmove(void *dst, const void *src, size_t n_bytes);
size_t				ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t				ft_strlcat(char *dst, const char *src, size_t dst_size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *block1, const void *block2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nitems, size_t size);
char				*ft_strdup(const char *s);
char				*ft_delsep(char *str); // from khnichou

// Addictional functions (11)
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int value);
char				*ft_strmapi(char const *s, char (*func)(unsigned int,
							char));
void				ft_striteri(char *s, void (*func)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif