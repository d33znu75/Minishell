/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:01:43 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:14:39 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_split
{
	char	**result;
	char	*current;
	size_t	count;
	size_t	len;
	size_t	i;
	int		in_single_quote;
	int		in_double_quote;
}	t_split;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_free_list_chars(char **list);
char	*ft_skip_spaces(char *str);
bool	ft_isspace(int c);
char	**ft_split2(char const *s, char c);
char	*ft_strndup(char *src, size_t n);
char	**ft_multi_split(char *s);
bool	is_special_operator(char *s);
bool	is_delimiter(char c);
int		word_length(char *s);
void	*free_memory(char **result, int length);
void	ft_err(char *str1, char *str2, char *str3, int fd);
int		ft_atoi2(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
void	*ft_malloc(int size, int free);
char	**ft_split_q(const char *str, char delimiter);
int		ft_strcmp(const char *str1, const char *str2);
#endif