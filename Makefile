address.exe:main.o contact.o file.o populate.o validation.o
	gcc -o address.exe main.o contact.o file.o populate.o validation.o

main.o:main.c
	gcc -c main.c 

contact.o:contact.c
	gcc -c contact.c 

file.o:file.c 
	gcc -c file.c 

populate.o:populate.c
	gcc -c populate.c 

validation.o:validation.c
	gcc -c validation.c 

clean : rm *.exe *.o
