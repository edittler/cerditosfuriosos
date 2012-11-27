# Makefile de las dependencias de modelo del cliente

# CONFIGURACION
################
# Flags para el compilador C/C++ en modo ansi.
CXXFLAGS = -Wall -pedantic -pedantic-errors -std=c++98

# Flags para compilar con POSIX Threads
#CXXFLAGS += -pthread -lpthread

# Flag de inclusion de las librerias de gtkmm
#GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

# Si la compilacion se ejecuta en modo DEBUG, agrego los flags correspondientes
ifdef DEBUG
CXXFLAGS += -O0 -g
else
CXXFLAGS += -O3
endif

# Compilador C++ a usar
CXX = g++

# Archivos a compilar, excluyendo main y test
archivos = $(filter-out main.cpp test.cpp, $(wildcard *.cpp))

# Subdirectorio de inclusiones externas a agregar
SUBDIRSINCLUDE = ../../common/Box2D/include ../../common/communication ../../common/model

# Inclusion de las cabeceras de los subdirectorios
I-INCLUDES = $(addprefix -I, $(SUBDIRSINCLUDE))

# Binarios a generar
bin = $(archivos:.cpp=.o)

# Archivos a limpiar
robjs = $(wildcard *.o main test)

# Descomentar para ver los mensajes del compilador
#verbose = si

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  Compilando  $@"; $(occ)
CXX = @echo "  Compilando  $@"; $(ocxx)
RM =  @echo "  Limpiando"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif


# REGLAS
#########

all: binaries

binaries: $(bin)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GTKFLAGS) $(I-INCLUDES) -c $<
	
clean:
	$(RM); rm -f $(robjs)

.PHONY: clean all binaries
