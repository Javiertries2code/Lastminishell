
minishell$ hola >> | Adios << >>
linea commands[0]-hola >> 
linea commands[1]- Adios << >>

CURRENT hola    op7
                                NEXT    >>      op3


CURRENT,
op      3       value   >>

ERROR REDIRECTIONS FOUND
gonna exit cheack token comands
FOUND ERROR FROM MAIN

==60954== Invalid read of size 8
==60954==    at 0x10B6F4: free_split_tripoint (exiting.c:136)
==60954==    by 0x1098DF: main (main.c:79)
==60954==  Address 0x4b77fc0 is 0 bytes inside a block of size 24 free'd
==60954==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60954==    by 0x10B7A0: free_split (exiting.c:164)
==60954==    by 0x10B7F4: free_command_info (errors.c:16)
==60954==    by 0x10B8D7: return_error (errors.c:36)
==60954==    by 0x10BA63: check_tokens_comands (errors.c:104)
==60954==    by 0x10BAC5: command_errors (errors.c:127)
==60954==    by 0x109894: main (main.c:72)
==60954==  Block was alloc'd at
==60954==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60954==    by 0x1095F5: ft_calloc (kloc.c:7)
==60954==    by 0x109C24: ft_split_quotes (split_quotes.c:175)
==60954==    by 0x10981B: main (main.c:61)
==60954== 
==60954== Invalid free() / delete / delete[] / realloc()
==60954==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==60954==    by 0x10B70A: free_split_tripoint (exiting.c:142)
==60954==    by 0x1098DF: main (main.c:79)
==60954==  Address 0x4b77fc0 is 0 bytes inside a block of size 24 free'd
==60954==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)