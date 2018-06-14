DEPS = alugueres.h clientes.h ficheiros.h guitarras.h ui.h
OBJ = main.o alugueres.o clientes.o ficheiros.o guitarras.o ui.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
