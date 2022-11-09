PATH_TO_CRYPTO_PP = ./cryptopp
PATH_TO_BIN = ./bin

clean:
	rm ${PATH_TO_BIN}/*.out

build_all: clean build_lab2 build_lab3 build_lab4 build_lab5

build_lab2:
	g++ lab2.cpp -std=c++20 -pedantic -O2 -fpermissive -I ${PATH_TO_CRYPTO_PP} -L ${PATH_TO_CRYPTO_PP} -lcryptopp -o lab2.out
	mv lab2.out ${PATH_TO_BIN}/
build_lab3:
	g++ lab3.cpp -std=c++20 -pedantic -O2 -fpermissive -I ${PATH_TO_CRYPTO_PP} -L ${PATH_TO_CRYPTO_PP} -lcryptopp -o lab3.out
	mv lab3.out ${PATH_TO_BIN}/
build_lab4:
	g++ lab4.cpp -std=c++20 -pedantic -O2 -fpermissive -I ${PATH_TO_CRYPTO_PP} -L ${PATH_TO_CRYPTO_PP} -lcryptopp -o lab4.out
	mv lab4.out ${PATH_TO_BIN}/
build_lab5:
	g++ lab5.cpp -std=c++20 -pedantic -O2 -fpermissive -I ${PATH_TO_CRYPTO_PP} -L ${PATH_TO_CRYPTO_PP} -lcryptopp -o lab5.out
	mv lab5.out ${PATH_TO_BIN}/