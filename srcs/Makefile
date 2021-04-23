# MY PERSONAL USE
# To check the differences between the srcs and the binus srcs

SRCS = $(shell find . -type f)
SRC = $(filter %.c, $(SRCS))

all:
	for src in $(SRC); do \
		diff $$src ../srcs_bonus/$$src | grep -v 'Updated' | wc -l | sed s/"       "// > diff; \
	done
