CC = tigcc
CFLAGS = -O2

all: xray.89z physics.89z hello.89z circles.89z

%.89z: %.c
	$(CC) $(CFLAGS) $<
