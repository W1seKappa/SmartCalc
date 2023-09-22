flags = -Wall -Werror -Wextra
prefix = ../build/

.PHONY: all clean rebuild 
 

all: $(prefix)graph



$(prefix)graph:
	gcc  $(flags) graph.c calculating.c expression_parser.c stack_double.c stack_string.c -o$(prefix)graph
clean:
	rm -rf $(prefix)graph
rebuild: clean all