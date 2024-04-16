CC         := cc
CFLAGS     := -c -Wall
LDFLAGS    :=
SOURCES    := pwd.c
OBJECTS    := ${SOURCES:.c=.o}
EXECUTABLE := pwd

all: ${SOURCES} ${EXECUTABLE}

$(EXECUTABLE): ${OBJECTS}
		${CC} ${LDFLAGS} ${OBJECTS} -o $@

.c.o:
		${CC} ${CFLAGS} $< -o $@

clean: ${OBJECTS} ${EXECUTABLE}
		rm -rf ${OBJECTS} ${EXECUTABLE}
