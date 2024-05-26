# Variables
SRCDIR := sources
INCDIR := headers
BINDIR := binaires
CC := gcc
CFLAGS := -Wall -Wextra -I$(INCDIR)

# Liste des fichiers source
SOURCES := $(wildcard $(SRCDIR)/*.c) main.c

# Liste des fichiers objet
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SOURCES))

# Nom de l'exécutable
EXECUTABLE := main

# Règle par défaut
all: $(EXECUTABLE)

# Règle pour générer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Règle pour générer les fichiers objet
$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(BINDIR)/*.o $(EXECUTABLE)
