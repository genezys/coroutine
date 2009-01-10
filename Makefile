TARGET=coroutine
OBJECTS=Fiber.Posix.o Test.o

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET)
