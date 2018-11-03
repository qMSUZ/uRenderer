GCC = gcc

CCFLAGS = -I.
LIBS    = -lm


DESTDIR = ./

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))


all: testmain testmaingfx

testmain: $(OBJECTS)
	$(GCC) -o testmain testmain.o color.o imagebuf.o vecmat.o wobj.o -lm
	
testmaingfx: $(OBJECTS)
	$(GCC) -o testmaingfx testmaingfx.o color.o imagebuf.o vecmat.o wobj.o -lm

$(OBJECTS): %.o: %.c
	$(GCC) -c $(CCFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f testmain testmaingfx
	rm -f *.exe
	rm -f *.tga