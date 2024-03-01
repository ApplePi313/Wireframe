build: 
	g++ -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz \
	-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-6 -pthread \
	-lfreetype \
	-Ilib -Iheaders -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl src/*.cpp src/glad.c \
	src/*/*.cpp -o bin/out

run:
	./bin/out
