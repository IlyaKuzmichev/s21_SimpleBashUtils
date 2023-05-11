.PHONY: all clean

all: build1 build2

build1:
	cd cat && $(MAKE)

build2:
	cd grep && $(MAKE)

clean:
	cd cat && $(MAKE) clean
	cd grep && $(MAKE) clean
