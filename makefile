CC = gcc
CFLAGS = -g
POSTFLAGS = -lreadline
DEPS = structs.h tree.h parser.h fastLookup.h
OBJ = fastLookup.c parser.c tree.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(POSTFLAGS)
fs: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(POSTFLAGS)
clean:
	rm -f *.o fs
