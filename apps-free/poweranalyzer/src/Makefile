CC=$(CROSS_COMPILE)gcc
RM=rm

OBJECTS=main.o fpga.o worker.o dsp.o house_kp.o calib.o

FFT_DIR=./external/kiss_fft
FFT_OBJECTS=$(FFT_DIR)/kiss_fft.o $(FFT_DIR)/kiss_fftr.o
FFT_INC=-I$(FFT_DIR)


INCLUDE=$(FFT_INC)

CFLAGS+= -Wall -Werror -g -fPIC $(INCLUDE)
LDFLAGS=-shared

CONTROLLER = ../controllerhf.so

all: $(CONTROLLER)


$(FFT_OBJECTS):
	$(MAKE) -C $(FFT_DIR)

$(CONTROLLER): $(FFT_OBJECTS) $(OBJECTS)
	$(CC) -o $(CONTROLLER) $(OBJECTS) $(FFT_OBJECTS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) -f $(OBJECTS)
	$(MAKE) -C $(FFT_DIR) clean
