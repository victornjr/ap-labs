CC       = gcc-8
CFLAGS   = -Wall
LDFLAGS  = -lm -fopenmp
OBJFILES = hello_par.o pi_spmd_simple.o  pi_spmd_final.o pi_loop.o  pi_mc_par.o matmul_par.o prod_cons_par.o
TARGET   = hello_par pi_spmd_simple pi_spmd_final pi_loop

all: $(TARGET)

logger:
	$(CC) $(CFLAGS) -c -o  $(LDFLAGS)

random:
	$(CC) $(CFLAGS) -c -o  $(LDFLAGS)

$(TARGET):  %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
