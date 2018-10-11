# Mark Wiemer mww 9074356420
# Jenny Ye haengjung 9075878315

CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
LINE = "+w ++ff=unix" # convert line endings
SPACES = "+%s/\s\+$$//" "+w" # remove right-trailing whitespace
QUIT = "+q!"
FILES = main.c \
	main.h \
	partner.txt \
	queue.c \
	queue.h
MARK_INFO = Mark Wiemer mww 9074356420
JENNY_INFO = Jenny Ye haengjung 9075878315

# Text appearance (color)
# https://misc.flogisoft.com/bash/tip_colors_and_formatting
NORMAL = \e[0m
LIGHT_GREEN = \e[92m
LIGHT_RED = \e[91m

all: main.o queue.o
	$(CC) -o $(EXE) main.o queue.o

main.o: main.c queue.h
	$(CC) $(WARNING_FLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(WARNING_FLAGS) -c queue.c

clean:
	rm $(EXE) *.o

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
	$(EXE)
	echo -e "$(LIGHT_GREEN)SUCCESS$(NORMAL)"

# add info to each file
info:
	for file in $(FILES) ; do \
		vim -c "1 s/^.*$$/\/\/ $(MARK_INFO)" -c "wq" $$file ;  \
		vim -c "2 s/^.*$$/\/\/ $(JENNY_INFO)" -c "wq" $$file ; \
	done
