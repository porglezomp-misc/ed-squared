edsq: main.c string_util.c string_util.h
	gcc -o edsq -g main.c string_util.c

RunTest: test.c string_util.c string_util.h
	gcc -o RunTest test.c string_util.c

test: RunTest
	./RunTest
