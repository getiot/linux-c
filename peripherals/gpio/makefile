all:
	gcc gpio_example.c -lgpiod -o gpio_example
	gcc libgpiod-led.c -lgpiod -o libgpiod-led
	gcc libgpiod-input.c -lgpiod -o libgpiod-input
	gcc libgpiod-event.c -lgpiod -o libgpiod-event

clean:
	rm gpio_example
	rm libgpiod-led libgpiod-input libgpiod-event
