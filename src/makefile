message = ./message/message.cpp ./message/messageType.cpp
utils = ./utils/utils.cpp
ricart-agrawala = ./ricart-agrawala/ricart-agrawala.cpp
test = ./test.cpp
all =  $(utils) $(message) $(ricart-agrawala) $(test)

main: clean debug
	g++ $(all)

clean:
	rm -f main

debug:
	echo "Compiling project"