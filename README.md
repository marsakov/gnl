# get_next_line

A C function that reads any valid file line by line until the end.


### What is get_next_line?

get_next_line is an individual project that basically reads a file line by line.

Disclaimer: *There are so many easier methods of doing this by using standard C functions. But the goal here is to be able to do it by using any functions from my libft and only the standard functions `read`, `malloc` and `free`.*

So it makes the project harder. But you can also use functions from your personal library.

After finishing this project, you'll definitely learn some more about static variables, pointers, arrays, linked lists, dynamic memory allocation and file manipulation.


### How do I use it?

I added a main file called **main.c**, it takes a file name as an argument, opens it and passes the file descriptor (fd) to get_next_line until get_next_line returns -1 or 0.

**Note:** get_next_line returns -1, 0, 1 depending on wether an error has occurred, the reading has been completed or a line has been read respectively.

Alright, so first of all, download/clone this repo:

	git clone https://github.com/marsakov/gnl.git
	
Get into it and build the library:
	
	cd gnl
	make -C libft/

Give it some time to compile all the files.

Build the executable:
	
	gcc -Wall -Wextra -Werror -I./libft/includes/ -L./libft -lft -o gnl get_next_line.c main.c

-I tells the compiler where your library header files are. `./libft/includes/` in this case

-L tells it where your library resides. `./libft` here

-l takes the name of your library. This is the set of characters that come after `lib` in your library name.

**NOTE:** -L and -l might look a little bit too much, you could replace those flags with `libft/libft.a` if you want.

Alright, the last command created a `gnl` executable in your directory. Now test it with:

	./gnl examples/example

It should read the whole file to you. Kinda like a basic `cat` implementation.
