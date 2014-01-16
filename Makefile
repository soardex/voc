
default: all

TARGET=voc
CC=g++
RM=rm -f
CP_R=cp -r
RM_R=rm -rf
MKDIR_P=mkdir -p

OUTDIR=build
BINDIR=$(OUTDIR)/bin
OBJDIR=$(OUTDIR)/objects
RESDIR=$(OUTDIR)/assets
LUADIR=$(OUTDIR)/scripts
CNFDIR=$(OUTDIR)/configs
TSTDIR=$(OUTDIR)/tests

NCRDIR=ncres
INCDIR=
LIBDIR=
SRCDIR=voc

SRCS=\
	$(SRCDIR)/AppMain.cpp \
	$(SRCDIR)/EmperorSystem.cpp \
	$(SRCDIR)/SecondLife.cpp

OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
LIBS=-lm

CFLAGS=-g -Wall
LFLAGS=$(LIBS)

all: directories populate $(TARGET)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BINDIR)/$@ $^

directories: 
	$(MKDIR_P) $(OUTDIR)
	$(MKDIR_P) $(OBJDIR)
	$(MKDIR_P) $(OBJDIR)/$(SRCDIR)
	$(MKDIR_P) $(BINDIR)
	$(MKDIR_P) $(RESDIR)
	$(MKDIR_P) $(LUADIR)
	$(MKDIR_P) $(CNFDIR)
	$(MKDIR_P) $(TSTDIR)

populate:
	$(CP_R) $(NCRDIR)/assets $(OUTDIR)
	$(CP_R) $(NCRDIR)/configs $(OUTDIR)
	$(CP_R) $(NCRDIR)/scripts $(OUTDIR)

.PHONY: clean

clean:
	$(RM) $(OBJDIR)/*.o 
	$(RM) $(OBJDIR)/$(SRCDIR)/*.o 
	$(RM) $(BINDIR)/$(TARGET)
	$(RM_R) $(OUTDIR)

depend: $(SRCS)
	$(CC) -MD $(INCDIR) $^

# DO NOT DELETE THIS LINE -- make depends needs it

