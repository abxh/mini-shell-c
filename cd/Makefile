CC         := cc
CFLAGS     := -c -Wall -DDEBUG
LDFLAGS    :=
SOURCES    := cd.c
OBJECTS    := ${SOURCES:.c=.o}
EXECUTABLE := cd

all: ${SOURCES} ${EXECUTABLE}

$(EXECUTABLE): ${OBJECTS}
		${CC} ${LDFLAGS} ${OBJECTS} -o $@

.c.o:
		${CC} ${CFLAGS} $< -o $@

clean: ${OBJECTS} ${EXECUTABLE}
		rm -rf ${OBJECTS} ${EXECUTABLE}
