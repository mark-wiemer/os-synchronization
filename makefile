# Mark Wiemer mww 9074356420
# Jenny Ye haengjung 9075878315

CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
LINE = "+w ++ff=unix" # convert line endings
IN_FILE = in.txt
OUT_FILE = out.txt
EXPECTED_FILE = expected.txt
SPACES = "+%s/\s\+$$//" "+w" # remove right-trailing whitespace
QUIT = "+q!"
SCAN_BUILD_DIR = scan-build-out
FILES = main.c \
	main.h \
	munch.c \
	munch.h \
	partner.txt \
	queue.c \
	queue.h \
	reader.c \
	reader.h \
	writer.c \
	writer.h
MARK_INFO = 1,Mark Wiemer,mwiemer2,mww,mwiemer2@wisc.edu,9074356420
JENNY_INFO = 2,Jenny Ye,hye35,haengjung,hye35@wisc.edu,9075878315

# Text appearance (color)
# https://misc.flogisoft.com/bash/tip_colors_and_formatting
NORMAL = \e[0m
LIGHT_GREEN = \e[92m
LIGHT_RED = \e[91m

all: main.o munch.o queue.o reader.o writer.o
	$(CC) -o $(EXE) main.o munch.o queue.o reader.o writer.o -lpthread

main.o: main.c main.h munch.h queue.h writer.h
	$(CC) $(WARNING_FLAGS) -c main.c

munch.o: munch.c main.h munch.h queue.h
	$(CC) $(WARNING_FLAGS) -c munch.c

queue.o: queue.c main.h queue.h
	$(CC) $(WARNING_FLAGS) -c queue.c

reader.o: reader.c main.h
	$(CC) $(WARNING_FLAGS) -c reader.c

writer.o: writer.c main.h queue.h
	$(CC) $(WARNING_FLAGS) -c writer.c

clean:
	rm -f $(EXE) $(OUT_FILE) *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

# convert line endings
unix:
	for file in $(FILES) makefile ; do \
		vim $(FILE) $(LINE) $(QUIT) ; \
	done

# remove trailing whitespace
spaces:
	for file in $(FILES) makefile ; do \
		vim $$file $(SPACES) $(QUIT) ; \
	done

test:
	echo "" > $(OUT_FILE)
	# redirect stdout and stderr to OUT_FILE
	# http://wiki.bash-hackers.org/syntax/redirection
	$(EXE) < $(IN_FILE) > $(OUT_FILE) 2>&1
	echo "The following may result in differing counts for blocks:"
	-diff $(OUT_FILE) $(EXPECTED_FILE)
	echo -e "$(LIGHT_GREEN)SUCCESS$(NORMAL)"

# add info to each file
info:
	for file in $(FILES) ; do \
		vim -c "1 s/^.*$$/\/\/ $(MARK_INFO)" -c "wq" $$file ;  \
		vim -c "2 s/^.*$$/\/\/ $(JENNY_INFO)" -c "wq" $$file ; \
	done
