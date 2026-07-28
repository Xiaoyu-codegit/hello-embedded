TARGET = led

$(TARGET): $(TARGET).c
	arm-none-linux-gnueabihf-gcc -static -o $(TARGET) $(TARGET).c
	scp $(TARGET) debian@192.168.137.2:/home/debian/

clean:
	rm -f $(TARGET)