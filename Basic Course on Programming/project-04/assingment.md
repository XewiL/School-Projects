In this project you will implement a simple prototype for a program that can be used to handle a list of things/jobs/chores/etc that have some sort of level of urgency attached to them. For example one might have the following chores to do:
Urgency 	Chores
Extremely urgent 	(priority level 3) 	do tomorrow's homework,
empty the stinking garbage bin,
feed the goldfish,
buy toilet paper
Normal urgency 	(priority level 2) 	pay the electricity bill,
vacuum,
wash dishes
Low urgency 	(priority level 1) 	play videogames,
have a party,
learn to parachute

The idea is that the chores in the higher priority levels must be finished before the chores in the lower levels. If there are multiple chores in particular priority level, they must be finished in the order there were added to the level's chore list i.e. in FIFO (first in first out) order.

The number of priority levels might vary. In a list of houseworks like above three levels is probably enough. But there are situations in which more or less levels would work better. This hints to the directions that the priority list implemented in this project should probably allow the user to specify how many separate levels of priorities the list has.

Your job in this project is to implement:
    a data structure that allows an easy manipulation of the priority lists as explained above and
    a simple command line (textual) user interface for testing the data structure in question.

The special requirements for this project

As always this project has some special requirements that must be fullfilled for the program to achieve a passing grade. Following is the list of these requirements:

    You are not allowed to use any STL containers (vector, deque, list, set, map, multiset, multimap, array, or any other even if not listed here) in your program. All the data structures that are used to store the chore list information must be dynamic and self implemented. You have two choices: linked lists or dynamic arrays (or any combination of those).

    You can use string library to store textual information (i.e. the chore descriptions etc.).

    All the dynamic memory your program allocates with new must be released with delete before the program ends. As a matter of fact there should be no kind of memory management issues in your program.

    To achieve this you should test your program with valgrind memory analyzer. It can be accessed in Qt Creator through Top Menu » Analyze » Valgrind Memory Analyzer.

    Your program should run without any complains from valgrind.

    Pay attention to your programming style:
        Name your variables, functions (including their parameters), datatypes, and constants with clear and descriptive names.
        Divide your program into sensible and logical modules.
        Indent your code lines logically.
        Comment your program clearly. Especially there should be a comment in front of every function and method definition describing its purpose, parameters, and possible return value. 

    Working in groups is no longer allowed in this project. This does not mean that you are not allowed to talk about your projects with your friends, but it does mean that you should not share or even show your code to anyone else. And vice versa, you shouldn't look someone else's code even if they try to show it to you.

    Your program must pass the public pretest otherwise it will automatically fail.