SERVER = server
CLIENT = client
CC = cc
CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror

SERVER_SRC = server.c utils/ft_putnbr.c
CLIENT_SRC = client.c utils/ft_atoi.c utils/is_digit.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
     
all: $(SERVER) $(CLIENT) $(CLIENT_2)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER)         

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT)      

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re