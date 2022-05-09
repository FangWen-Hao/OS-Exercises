PROG := Q6-33
SRCS := Q6-33.c

CC      := gcc
CFLAGS  := -Wall -Wextra -Werror  -lpthread
LDFLAGS :=

OBJS   = $(SRCS:.c=.o)
DEPS   = $(SRCS:.c=.d)

.PHONY: all
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

	rm -f $(OBJS) $(DEPS)

.PHONY: clean cleaner
clean:
	rm -f $(OBJS) $(DEPS)

cleaner: clean
	rm -rf $(PROG)
