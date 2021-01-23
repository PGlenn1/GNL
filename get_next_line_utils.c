#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *s1, char *s2)
{
	int i;
	int s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s2[i])
	{
		s1[s1_len + i] = s2[i];
		i++;
	}
	s1[s1_len + i] = 0;
	return (s1);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char *s3;

	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	*s3 = '\0';
	ft_strcat(ft_strcat(s3, s1), s2);
	return (s3);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*s1_dup;

	i = 0;
	len = ft_strlen(s1);
	if (!(s1_dup = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = 0;
	return (s1_dup);
}
