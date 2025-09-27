#include "../mini.h"

/**
 * @brief Adds a new environment variable to the linked list.
 *
 * Splits the string `envp` by '=' into key and value.
 * If `env_head` has no key yet, it initializes it.
 * Otherwise, creates and appends a new element at the end of the list.
 *
 * @param env_head Pointer to the head of the environment list.
 * @param envp A string in the form "KEY=VALUE".
 */
static void	add_env_element(t_env *env_head, char *envp)
{
    t_env	*new_element;
    t_env	*tmp;
    char	**key_value;

    tmp = env_head;
    while (tmp->next)
        tmp = tmp->next;
    key_value = ft_split(envp, '=');
      if (!key_value || !key_value[0])
    {
        free_split(key_value);
        return ;
    }
    if (!env_head->key)
    {
        env_head->key = ft_strtrim(key_value[0], " \t\n\v\f\r");
        env_head->value = ft_strtrim(key_value[1], " \t\n\v\f\r");
        free_split(key_value);
    }
    else
    {
        new_element = ft_calloc(1, sizeof(t_env));
        new_element->key = key_value[0];
        new_element->value = key_value[1];
        tmp->next = new_element;
        free(key_value);
    }
}
/**
 * @brief Copies the system environment into a linked list.
 *
 * Iterates over the `envp` array and adds each entry to the `env_head` list.
 *
 * @param env_head Pointer to the head of the environment list.
 * @param envp Array of environment strings ("KEY=VALUE").
 */
void	copy_env(t_env *env_head, char **envp)
{
	while (*envp)
	{
		add_env_element(env_head, *envp);
		envp++;
	}
}
