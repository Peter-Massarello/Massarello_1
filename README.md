Name: Peter Massarello

FUNCTIONS USED:
---------------------------------------------------------------------------------------------

print_env():\n
	-Uses a while loop to gather entire count of name=value pairs in environ.
	-Iterates to the count generated above and prints out name=value pairs.

help_menu():
	-Prints out help menu with printf statements.

check_for_pair():
	-Uses a char buffer to hold the current argument being given to it.
	-Checks to see if buffer string has a '=', if it does, return true.

check_for_system_call:
	-System calls and uses perror with a errno of 3 if system call fails.

i_option:
	-Iterates through all of argc and uses check_for_pair and check_for_system_call.
	-Allocates newEnv array and once finished, sets environ to newEnv.

check_if_new:
	-Iterates though all name=value pairs in environ.
	-Strcpys the string and then uses strtok to gather the key at the delimiter.
	-If the given key matches any key in environ returns false, otherwise returns true.

update_env:
	-Gathers the count of arguments of both environ and argv.
	-Combines those counts and allocates newEnv to the proper size.
	-Then allocates all arguments from environ to newEnv
	-Then goes through all arguments in argv checking to see if they are pairs or calls.
	-If name=value pair, then add to newEnv, otherwise test the system call.

no_i_args:
	-Checks to see if no -i arguments are given by checking the count of argv.

--------------------------------------------------------------------------------------------

GOAL OF PROJECT:
--------------------------------------------------------------------------------------------

The goal of this homework is to become familiar with the enviorment in hoare
while practicing system calls. You will also demonstrate your proficiency in the use of
'perror' and 'getopt' in this submission. This excercise 2.12 is in your text by Robbins.

--------------------------------------------------------------------------------------------

PROBLEMS I HAD:
--------------------------------------------------------------------------------------------
This project was very rough to say the least. While I do have experience in C++, my experience
in C is nothing compared to that. I feel like I had to learn a lot of this own my own, or
through help of friends. I tried looking at Microsoft Teams but much of what was on there
confused me as well. While I have used getopt before in my 2750 class, all the parts
that came with getopt like optind, optarg, etc I have never used before. Same with
malloc, realloc, etc.

I also had trouble fully understanding the projects in its enitirety. There were many times 
where I was confused on the prompt and started writing a program that, while it worked, was
incorrect for the project. You can see this from my massive adds and deletes in my git
history.

After going into an SI session though I was able to understand this project MUCH more. My
main issue was having a combined confusion of what I need to do and how I would do it. But 
once I knew what I had to do, learning how to do it came much easier. It took me nearly four
days to get the -i part working and by the time I did, it was actually an incorrect way
of implimenting it. But after that SI session, I was able to finish the project the next day.

The only issue I think this program still has is if you type ./doenv -i and give it no args.
I wanted to have it quit out but it still prints the enviornment. Other than that I believe
everything works.

--------------------------------------------------------------------------------------------

I hope for next assignments we get more practice going into them so the stress of trying
to finish this won't be as high.I will also be at the SI sessions.
