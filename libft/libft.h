/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:22:08 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/11 21:49:56 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isalnum(int a);
int			ft_isalpha(int a);
int			ft_isascii(int a);
int			ft_isdigit(int d);
int			ft_isprint(int p);
int			ft_tolower(int l);
int			ft_toupper(int u);
// MEMORY //
void		*ft_memset(void *str, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_calloc(size_t num, size_t size);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
// PRINT //
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
// STRING //
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
char		*ft_strdup(const char *src);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);;
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
// LIST //
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//FT_PRINTF//
int			ft_conversion(va_list args, const char type);
int			ft_printf(const char *str, ...);
// Conversion functions*
int			print_char(char c);
int			print_str(char *str);
int			print_ptr(unsigned long long ptr);
int			print_nbr(int n);
int			print_unsigned(unsigned int n);
int			print_hex(unsigned int num, const char type);
int			print_percent(void);
// Helper functions*
int			hex_len(unsigned int num);
void		put_hex(unsigned int num, const char type);
int			ptr_len(uintptr_t num);
void		put_ptr(uintptr_t num);
int			num_len(unsigned int num);
char		*unsigned_itoa(unsigned int n);
void		put_str(char *str);

//GET_NEXT_LINE//
char		*get_next_line(int fd);
// Helper functions*
static int	read_and_concat(int fd, char **remain, char *buffer);
static char	*extract_line(char **remain);
static char	*handle_remain(char **remain, char *line);
static char	*read_line(int fd, char **remain, char *buffer);

#endif