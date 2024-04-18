CC         := cc
CFLAGS     := -c -Wall -DDEBUG
LDFLAGS    :=
SOURCES    := ls.c
OBJECTS    := ${SOURCES:.c=.o}
EXECUTABLE := ls

all: ${SOURCES} ${EXECUTABLE}

$(EXECUTABLE): ${OBJECTS}
		${CC} ${LDFLAGS} ${OBJECTS} -o $@

.c.o:
		${CC} ${CFLAGS} $< -o $@

clean: ${OBJECTS} ${EXECUTABLE}
		rm -rf ${OBJECTS} ${EXECUTABLE}
