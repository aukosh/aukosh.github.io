all: the_proof clean
my_math.o: my_math.cpp
	 g++ -w -c my_math.cpp
list_arith.o: list_arith.cpp
	g++ -w -c list_arith.cpp
propeller.o: propeller.cpp
	g++ -w -c propeller.cpp
net.o: net.cpp
	g++ -w -c net.cpp
proof.o: proof.cpp
	g++ -w -c proof.cpp

the_proof: my_math.o list_arith.o propeller.o net.o proof.o
	g++ -w my_math.o list_arith.o propeller.o net.o proof.o -o the_proof

clean: 
	rm *.o