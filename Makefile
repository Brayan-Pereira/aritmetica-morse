CC = gcc
CFLAGS = -Wall

SRC = src/morse_calculator.c src/main.c
OBJ = $(SRC:.c=.o)
EXEC = morse_calculator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run:
	./morse_calculator
