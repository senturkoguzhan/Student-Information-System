output: main.o administrator.o lecturer.o student.o classroom.o
	g++ main.o administrator.o lecturer.o student.o classroom.o -o output
	./output
main.o: main.cpp
	g++ -c main.cpp
lecturer.o: lecturer.cpp lecturer.h
	g++ -c lecturer.cpp
administrator.o: administrator.cpp administrator.h
	g++ -c administrator.cpp
student.o: student.cpp student.h
	g++ -c student.cpp
classroom.o: classroom.cpp classroom.h
	g++ -c classroom.cpp
clean: 
	rm -rf *o output main administrator lecturer student classroom