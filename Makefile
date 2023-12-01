
CC=g++
GLM_INCLUDE_DIR=

LDFLAGS=  -lm
CXXFLAGS= -W -I$(GLM_INCLUDE_DIR)
 

EXEC= Raycasting
SRC= camera.cpp bitmap.cpp Intersection.cpp Objet3D.cpp pixelmap.cpp Scene.cpp rayon.cpp main.cpp
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

Raycasting: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	 $(CC) -o $@ -c $< $(CXXFLAGS) 

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
