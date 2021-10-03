.PHONY:gcc, run, test
gcc:
	arm-linux-gnueabihf-gcc $(name).s -o $(name)
run:
	qemu-arm -L /usr/arm-linux-gnueabihf/ ./$(name)
test:
	arm-linux-gnueabihf-gcc $(name).s -lm -o $(name)
	qemu-arm -L /usr/arm-linux-gnueabihf/ ./$(name)