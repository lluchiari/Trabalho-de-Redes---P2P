FILE=P2P_LP
PATH_DIR=~/Documents/Trabalho Redes/Codigos/Atual/

all: compile
	@gcc $(FILE).o menu.o myserver.o mylist.o functions.o -o $(FILE) -lpthread -Wall

compile: $(FILE).c menu.c myserver.c mylist.c functions.c
	@gcc -c functions.c
	@gcc -c menu.c
	@gcc -c myserver.c -lpthread
	@gcc -c mylist.c
	@gcc -c $(FILE).c -lpthread -I./

run: $(FILE)
	@./$(FILE)

clean:
	@rm *.o 
	@rm $(FILE)

send:
	scp -P 22200 /home/lluchiari/Documents/Trabalho\ Redes/Codigos/Atual/Hosts.txt   gen11@cosmos.lasdpc.icmc.usp.br:/home/gen11/code/V3
