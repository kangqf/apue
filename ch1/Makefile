errorfile = ../apue/error.c

all : 1_1_ls 1_2_nobufio 1_3_bufio 1_4_uid_gid 1_5_shell 1_6_error
	
1_1_ls : 1_1_ls.c
	gcc 1_1_ls.c $(errorfile) -o 1_1_ls
	
1_2_nobufio : 1_2_nobufio.c
	gcc 1_2_nobufio.c $(errorfile) -o 1_2_nobufio
	
1_3_bufio : 1_3_bufio.c
	gcc 1_3_bufio.c $(errorfile) -o 1_3_bufio

1_4_uid_gid : 1_4_uid_gid.c
	gcc 1_4_uid_gid.c $(errorfile) -o 1_4_uid_gid

1_5_shell : 1_5_shell.c
	gcc 1_5_shell.c $(errorfile) -o 1_5_shell
	
1_6_error : 1_6_error.c
	gcc 1_6_error.c $(errorfile) -o 1_6_error
	
.PHONY : clean
clean:
	rm *.exe *.o
