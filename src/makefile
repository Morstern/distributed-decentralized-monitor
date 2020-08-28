message = ./message/message.cpp ./message/messageType.cpp
monitor = ./monitor/monitor.cpp
utils = ./utils/utils.cpp
ricart-agrawala = ./ricart-agrawala/ricart-agrawala.cpp
test = ./tests/test_ricart_agrawala.cpp ./tests/test_monitor.cpp ./tests/test_message.cpp
main = ./main.cpp
all =  $(utils) $(message) $(monitor) $(ricart-agrawala) $(test) $(main)
libraries = -lzmq -pthread

main: clean debug
	g++ $(all) $(libraries)

clean:
	rm -f main

debug:
	echo "Compiling project"