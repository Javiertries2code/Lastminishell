#leaks Final
==138266== 3 bytes in 3 blocks are definitely lost in loss record 1 of 67
==138266==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==138266==    by 0x11018E: ft_strtrim (in /home/havr/Desktop/LastMini/mini/minishell)
==138266==    by 0x109916: empty (in /home/havr/Desktop/LastMini/mini/minishell)
==138266==    by 0x109AFD: do_the_thing (in /home/havr/Desktop/LastMini/mini/minishell)
==138266==    by 0x10F921: main (in /home/havr/Desktop/LastMini/mini/minishell)

# MiniShell
Academic project consisting in reacreating partially the behaviour of a shell

## Perfeccionar

-	

## Error handling

-	Triple redir
-	Mejorar comandos inexistentes

## Implementar

-	Señales para el builtin exit

## Liberar

-	Liberar env_expr

## Leaks

-	Leaks en get_cmd_path()