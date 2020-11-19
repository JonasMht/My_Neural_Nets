#Variables projet
TARGET = nn_exe
DATE = $(shell date +"d%dm%mY%Y_H%HM%MS%S")

VERSION = 2.5.9

CC = g++

.PHONY: release
release: all

.PHONY: debug
debug: all

#debug
debug:CFLAGS = -Wall
debug:CFLAGS += -std=c11 -pedantic -pedantic-errors
debug:CFLAGS += -Wall -Wextra
debug:LDFLAGS = #ex -lm

#Release
release:CFLAGS = 
release:LDFLAGS = 

# repertoires
INCLDIR = include
SRCDIR = src
DEPDIR = dep
OBJDIR = obj
BINDIR = bin
DISTDIR = dist
DOCDIR = docs
GRIDIR = grilles

# Fichiers
SRCS = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCLDIR)/*.h)
# Ne marche que dans un répertoire "plat"
# SRCS = $(shell find . -type f -name "*.c")
# Pour trouver les sources dans une arborescence de fichiers.
DEPS = $(patsubst $(SRCDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
BIN = $(BINDIR)/$(TARGET)


.PHONY: all
all: dir $(BIN)

.PHONY: dir # Crée les dossiers s'ils n'éxistent pas déja.
dir:
	@mkdir -p $(INCLDIR) $(SRCDIR) $(DEPDIR) $(OBJDIR) $(BINDIR) $(DISTDIR)


$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DEPDIR)/%.d $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(SRCDIR)/$*.cpp \
	-c -o $(OBJDIR)/$*.o \
	-I $(INCLDIR) \
	$(CFLAGS) \
	-MMD \
	-MT "$(DEPDIR)/$*.d $(OBJDIR)/$*.o" \
	-MF $(DEPDIR)/$*.d \


.PHONY: run # dit que cette cible n'est pas un fichier
run:
	./$(BINDIR)/$(TARGET) "grilles/grilleAlpha.txt"

.PHONY: cr # dit que cette cible n'est pas un fichier
cr: release # compile and run
	make run
	

.PHONY: dist # dit que cette cible n'est pas un fichier
dist: # créer une distribution des ".tar.xz" avec les codes sources et le doxyfile uniquement
	tar -cJf "$(DISTDIR)/MehtaliJonas-GoL-$(VERSION).tar.xz" $(SRCS) $(HEADERS) $(DOCDIR) $(GRIDIR) makefile Doxyfile README.md
	tar -clzmaf "$(DISTDIR)/MehtaliJonas-GoL-$(VERSION).tar.lzma" $(SRCS) $(HEADERS) $(DOCDIR) $(GRIDIR) makefile Doxyfile README.md


.PHONY: clean # dit que cette cible n'est pas un fichier
clean:
	@rm -rf $(DEPDIR)/** $(OBJDIR)/** $(BINDIR)/**

.PHONY: git_send # dit que cette cible n'est pas un fichier
git_send:
	make clean
	git add $(SRCS) $(HEADERS) $(DOCDIR) $(GRIDIR) makefile Doxyfile README.md
	git commit $(SRCS) $(HEADERS) $(DOCDIR) $(GRIDIR) makefile Doxyfile README.md -m "$(DATE) -V$(VERSION)"
	git push

.PHONY: docs # dit que cette cible n'est pas un fichier
docs:
	@doxygen

# amélioration : ajouter une option debug et release