LIBS= -lGL -lglfw -lGLEW 

EXTERNAL=lib/lodepng.h lib/lodepng.cpp  lib/shaderprogram.h lib/shaderprogram.cpp
HEADERS=model.hpp board.hpp chessman.hpp drawable.hpp chessPieces.hpp placement.hpp savedGame.hpp chess.hpp game.hpp app.hpp
FILES=main_file.cpp

main_file: $(FILES) $(HEADERS) $(EXTERNAL) 
	g++ -o main_file $(FILES) $(EXTERNAL) $(LIBS) -I.
