# simulation_of_movie_theatre

There is a ".c"-file with attached txt documents (Movie.txt and Ticket.txt)

Code is written in C language, cause I decided that C is more closer to me than C++. But C++ is more preferrable for this task, cause OOP is more implementable with this language. Considering deadline I decided to complete in manner of "Done is better than perfect".

It has to be compiled first and then run.

Check before that your sample files in the same directory with simul.c and then if your OS is Linux run "gcc simul.c -o test" and then run "./test". On Windows first run "gcc simul.c" then "simul".

Workflow explanation:

1) Reading attachedfiles and storing the data from them in local variables
2) Computing the maximum number of tamesteps (start time + duration of last movie)
3) Itterate timesteps and in each itteration check is there request for tickets
4) Checking is requested movie not started yet
5) Checking is available places more then requested places
6) Placing customers in the case request is proceed all checkings
7) In every itteration print to the terminal current status of movies and halls. Printing places status for the coming movies.
8) At the end check how many people missed the chanse to watch the movie

Features which is done in the code:

1) Created structs to map tickets, movies and halls with each other
2) Every created struct variables contains their identifications and status
3) Assumed that movies which will be played in the same hall will not overcome each other
4) max number of movies is 10 (can be changed in code to dynamic from static)
5) max number of requests for tickets is 100 (can be changed in code to dynamic from static)
