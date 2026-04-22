all:
	gcc *.c -o password_manager -lssl -lcrypto
clean:
	rm password_manager
