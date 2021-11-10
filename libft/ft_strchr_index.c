int	ft_strchr_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i])
		return (i);
	return (-1);
}
