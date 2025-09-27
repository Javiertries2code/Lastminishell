#include "../mini.h"


void handler_ct_slash(int signal){
    
}
void handler_ctrl_c(int signal){

}
void handler_ctrl_d(int signal){

}
void	set_handlers(t_data *data)
{
	struct sigaction	sa;

	sa.sa_handler = &handler_ct_slash;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &handler_ctrl_d;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}