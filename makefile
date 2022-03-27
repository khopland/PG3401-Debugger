INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -Wall
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

_DEPS = pgdbglog.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o pgdbglog.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lib: $(OBJS)
	ar rcs pgdbglog.a $(OBJDIR)/pgdbglog.o $(INCLDIR)/pgdbglog.h
	ranlib pgdbglog.a

test: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ *.a