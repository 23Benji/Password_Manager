Makefile:password run

password:
	gcc -o PasswordManager main.c 2> /dev/null

run:
	./PasswordManager

clean:
	rm PasswordManager

cleanall:
	rm PasswordManager *.o