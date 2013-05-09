all: hello

hello: target6.o gpio.o wheel_controll.o serial.o sonar.o cd74ac153.o
	g++ target6.o gpio.o wheel_controll.o serial.o sonar.o cd74ac153.o -o hello

target6.o: target6.cpp
	g++ -c target6.cpp

gpio.o: gpio.cpp
	g++ -c gpio.cpp

wheel_controll.o: wheel_controll.cpp
	g++ -c wheel_controll.cpp

serial.o: serial.cpp
	g++ -c serial.cpp

sonar.o: sonar.cpp
	g++ -c sonar.cpp

cd74ac153.o: cd74ac153.cpp
	g++ -c cd74ac153.cpp

clean:
	rm -rf *.o hello