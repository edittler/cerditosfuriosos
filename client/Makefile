# Makefile del Cliente

# CONFIGURACION
################
# Instruccion make con flag para ocultar el salto a otros directorios.
MAKE = make --no-print-directory

# Nombre del ejecutable principal.
main_target = main

# Flags para el compilador C/C++ en modo ansi.
CXXFLAGS = -Wall -pedantic -pedantic-errors -std=c++98

# Flags para compilar con POSIX Threads
#CXXFLAGS += -pthread -lpthread

# Flag de inclusion de las librerias de gtkmm
GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

# Si la compilacion se ejecuta en modo DEBUG, agrego los flags correspondientes
ifdef DEBUG
CXXFLAGS += -g -O0
else
CXXFLAS += -O3
endif

# Subdirectorio de dependencias externas a compilar
SUBDIRS = ../common/communication ../common/model ../common/parser ../common/thread controlador core modelo vista/menues vista/modelo

# Subdirectorio de inclusiones externas a agregar
SUBDIRSINCLUDE = ../common/Box2D/include ../common/communication ../common/parser ../common/thread ../common/model controlador core modelo vista/modelo

# Declaracion de objetos externos
EXTERNOBJS =$(foreach path, $(SUBDIRS), $(addsuffix .o, $(basename  $(wildcard $(path)/*.cpp))))

# Compilador C++ a usar
CXX = g++

# Inclusion de las cabeceras de los subdirectorios
I-SUBDIRS = $(addprefix -I, $(SUBDIRSINCLUDE))

# Directorio de la liberia de Box2D
BOX2DLIBDIR = ../common/Box2D/lib

# Flag de inclusion de librerias
BOX2DFLAG = -L$(BOX2DLIBDIR) -lBox2D

# Binarios a generar
bin = $(archivos:.cpp=.o)

# Archivos a limpiar
robjs = $(wildcard *.o $(main_target) test)

# Descomentar para ver los mensajes del compilador
#verbose = si

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =       @echo "  Compilando  $@"; $(occ)
CXX =      @echo "  Compilando  $@"; $(ocxx)
CCDEPEND = @echo "  Compilando dependencias externas"
RM =       @echo "  Limpiando"; $(orm)
LD =       @echo "  LD  $@"; $(old)
endif


# REGLAS
#########

all: main

subdirs:
	$(CCDEPEND)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

main: subdirs
	$(CXX) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp $(GTKFLAGS) $(BOX2DFLAG) -o $(main_target)

test: make_subs
	$(CXX) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM); rm -f $(robjs)

.PHONY: all
