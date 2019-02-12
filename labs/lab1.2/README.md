# Lab 1.2 - PTY/PTY Broadcaster

This program serves as a Broadcaster of custom messages for all connected users in the Linux machine. So a user can call the program and add some text and it will be broadcasted to the rest of the users.

In order to compile the program you need to do the next thing:
		gcc broadcast.c -o broadcast

After that just run the broadcast program and add some text as argument:
		./broadcast This is the message to be broadcasted

Then each user should receive the message.
