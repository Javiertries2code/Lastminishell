#include "../mini.h"

//int		sig = 0;

void	handler_ct_slash(int signal)
{
	(void)signal;
	print("handle slash  does nothing aparently");
	print("not in father not in son");
	return ;
}

void	handle_heredoc_ctrl_c(int signal)
{
	print("handle heredoc, pending");
	// TODO pending handler heredoc
	// TODO pending handler heredoc
	// ain sure what i gotta do to be honest.
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED-HEREDOC\n", 0);
	rl_redisplay();
}
void	handler_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED, I do Exit, but gotta be rmoved\n", 0);
	rl_redisplay();
	//remove exit
	exit(0);
}

void	set_handlers()
{
	struct sigaction sa;

	sa.sa_handler = &handler_ct_slash;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

}