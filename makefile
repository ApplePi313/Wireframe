build: 
	g++ -Ilib -Iheaders -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl src/*.cpp src/glad.c src/*/*.cpp -o bin/out

run:
	./bin/out
