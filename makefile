OBJ=calc.o
SRC=calc.c

OUT=calc

LIBS=

FLAGS= -c -g

.PHONEY: all install clean profile

all: $(OUT)

$(OUT): $(OBJ)
	gcc -o $@ $^ $(LIBS)
	@rm -rf out.txt && echo 'Removed: out.txt'

.c.o:
	gcc $< -o $@ $(FLAGS)

install: $(OUT)

profile: all
	@valgrind --leak-check=full ./$(OUT)

clean:
	@rm -rf $(OBJ) && echo 'Removed: $(OBJ)'
	@rm -rf $(OUT) && echo 'Removed: $(OUT)'
	@rm -rf out.txt && echo 'Removed: out.txt'