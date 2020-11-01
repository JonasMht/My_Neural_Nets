TARGET = nn_exe
DATE := $(shell date +"%m/%d/%Y at %H:%M:%S")


CC = g++
CFLAGS = -Wall

CFLAGS += -std=c11 -pedantic -pedantic-errors
CFLAGS += -Wall -Wextra -Werror

# repertoires
INCLDIR = include
SRCDIR = src
DEPDIR = dep
OBJDIR = obj
BINDIR = bin
DISTDIR = dist
SAVDIR = saves

# Fichiers
SRCS = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCLDIR)/*.h)
# Ne marche que dans un répertoire "plat"
# SRCS = $(shell find . -type f -name "*.cpp")
# Pour trouver les sources dans une arborescence de fichiers.
DEPS = $(patsubst $(SRCDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
BIN = $(BINDIR)/$(TARGET)

.PHONY: all
all: dir $(BIN)

.PHONY: dir # si les dossiers n'existent pas, créez les
dir:
	@mkdir -p $(INCLDIR) $(SRCDIR) $(DEPDIR) $(OBJDIR) $(BINDIR) $(DISTDIR) $(SAVDIR)


$(BIN): $(OBJS)
	$(CC) -o $@ $^

$(DEPDIR)/%.d $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(SRCDIR)/$*.cpp \
	-c -o $(OBJDIR)/$*.o \
	-I $(INCLDIR) \
	-MMD \
	-MT "$(DEPDIR)/$*.d $(OBJDIR)/$*.o" \
	-MF $(DEPDIR)/$*.d


.PHONY: run # dit que cette cible n'est pas un fichier
run:
	./$(BINDIR)/$(TARGET)

.PHONY: cr # dit que cette cible n'est pas un fichier
cr: # compile and run
	@make all
	@make run
	

.PHONY: dist # dit que cette cible n'est pas un fichier
dist: # créer une distribution des ".tar.xz" avec les codes sources et le doxyfile uniquement
	tar -cJf $(DISTDIR)/archive.tar.xz $(SRCS) $(HEADERS) makefile


.PHONY: clean # dit que cette cible n'est pas un fichier
clean:
	@rm -rf $(DEPDIR)/** $(OBJDIR)/** $(BINDIR)/** $(DISTDIR)/**

.PHONY: git_send # dit que cette cible n'est pas un fichier
git_send:
	make clean
	git add *
	git commit -a -m "Automatic commit & push, $(DATE)"
	git push

# amélioration : prendre en compte les changements dans les header