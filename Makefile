PROG = tris.c
TRIS = tris

all: $(TRIS)

clean:
	@printf "\n\t" 
	rm -f tris
	@printf "\n"

$(TRIS): $(PROG)
	@gcc $(PROG) -w -o $(TRIS)
	@printf "\n\t%s\n\n" "exec it with \"./tris\""



#nosense makefile ik but ok