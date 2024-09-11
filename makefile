Makefile:password run

password:
	gcc -o PasswordManager main.c

run:
	./PasswordManager

clean:
	rm PasswordManager

cleanall:
	rm PasswordManager *.o