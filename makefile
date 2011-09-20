SRC = main.cpp socket.cpp settings.cpp procquee.cpp tools.cpp

telnetd: $(SRC)
	g++ $(SRC) -o telnetd
	