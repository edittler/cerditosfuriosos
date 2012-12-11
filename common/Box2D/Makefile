# Makefile de la libreria Box2D

# CONFIGURACION
################
# Instruccion make con flag para ocultar el salto a otros directorios.
MAKE = make --no-print-directory

# Directorio donde se almacena la libreria
LIB = lib

# Nombre de la libreria.
TARGET = $(LIB)/libBox2D.a

# Flags para la generacion de la libreria
AR = ar r

# Flags para el compilador C/C++ en modo ansi.
CXXFLAGS = -c

# Flags para compilar con POSIX Threads
#CXXFLAGS += -pthread -lpthread

# Flag de inclusion de las librerias de gtkmm
#GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

# Si la compilacion se ejecuta en modo DEBUG, agrego los flags correspondientes
ifdef DEBUG
CXXFLAGS += -g -O0
else
CXXFLAS += -O3
endif

# Subdirectorio de dependencias externas a compilar
SUBDIRS = source/Box2D/Collision source/Box2D/Collision/Shapes source/Box2D/Common source/Box2D/Dynamics source/Box2D/Dynamics/Contacts source/Box2D/Dynamics/Joints source/Box2D/Rope

# Subdirectorio de inclusiones externas a agregar
SUBDIRSINCLUDE = include/Box2D include/Box2D/Collision include/Box2D/Collision/Shapes include/Box2D/Common include/Box2D/Dynamics include/Box2D/Dynamics/Contacts include/Box2D/Dynamics/Joints include/Box2D/Rope

# Declaracion de objetos externos
EXTERNOBJS =$(foreach path, $(SUBDIRS), $(addsuffix .o, $(basename  $(wildcard $(path)/*.cpp))))

# Compilador C++ a usar
CXX = g++

# Inclusion de las cabeceras de los subdirectorios
I-SUBDIRS = $(addprefix -I, $(SUBDIRSINCLUDE))

archivos = $(wildcard *.cpp)

# Binarios a generar
bin = $(archivos:.cpp=.o)

# Archivos a limpiar
robjs = $(wildcard *.o $(TARGET))

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
	@echo "  Creando libreria libBox2D.a"
	@$(AR) $(TARGET) $(EXTERNOBJS)

test: make_subs
	$(CXX) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM); rm -f $(robjs)

.PHONY: all
