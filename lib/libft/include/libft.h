/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:52:36 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/17 19:32:24 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//CONSTANTES DO PRINTF
# define BASE16_L "0123456789abcdef"
# define BASE16_U "0123456789ABCDEF"

//CONSTANTES DO GET_NEXT_LINE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define MAX_FD 4096

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

//ESTRUTURA PARA AS TAGS DO PRINTF
typedef struct tag_parameter
{
	int		flags[256];
	int		width;
	int		digits;
	int		decplaces;
	char	tag;
}	t_params;

typedef unsigned long	t_ul;

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_isupper(int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isdigit(int c);
int		ft_isalldigits(char *str);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_countdec(long n_long);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
long	ft_atoi(const char *nptr);
char	*ft_char_to_byte(unsigned char c);
int		ft_byte_to_char(char *byte);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_toupper(int c);
int		ft_tolower(int c);
//--------------------------------------------------------//
//---------------------FT_PRINTF--------------------------//
//--------------------------------------------------------//
int		ft_printf(int fd, const char *format, ...);
int		ft_putnbr_hexabase_fd(t_ul nbr, char *base, int fd);
int		ft_printnbr_fd(long nbr, t_params params, int fd);
int		ft_print_s_fd(char *s, t_params params, int fd);
int		ft_printnbr_base_fd(t_ul nbr, t_params params, char *base, int fd);
int		ft_printchar_fd(char c, t_params params, int fd);
int		ft_print_p_fd(t_ul p, t_params params, int fd);
//--------------------------------------------------------//
//--------------------GET_NEXT_LINE-----------------------//
//--------------------------------------------------------//
char	*get_next_line(int fd);
#endif