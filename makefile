CC = gcc
CFLAGS = -g
POSTFLAGS = -lreadline
DEPS = LLNode.h structs.h
OBJ = fastlookup.c parser.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(POSTFLAGS)
fs: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(POSTFLAGS)
clean:
	rm -f *.o fs

# fs: fastlookup.o parser.o
# 	gcc -o fs fastlookup.o parser.o

# fastlookup.o: fastlookup.c
# 	gcc -c fastlookup.c

# parser.c: parser.c
# 	gcc -c parser.c
