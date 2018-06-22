CXX=gcc
CFLAGS=
LIBS=
OBJ = main.o  \
parser.o 

all: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o dynamic $(LIBS)

clean:
	rm *.o && rm dynamic

%.o: %.c
	$(CXX) $(CFLAGS) -c $<
