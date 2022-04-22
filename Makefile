compile:
	gcc main.c -o WoW.out

compile_and_test1: compile
	./WoW.out chars_1.txt commands_1.txt

	