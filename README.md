# Manage-Jerry
Inspired by Rick and Morty

At first I will explain shortly what the code does:
The main received a file that contains details about planets and jerries.
Then, I scan the file and collect the details to 2 arrays - planets and jerries. Any cell in the array contains a pointer to struct (planet/jerry).
Eventually, the user can use it to many functions. 

Now, let's talk about the moduls:
- Defs.h: This file is for me; to make the returned values easy to understand and act accordingly.
- Jerry.h: This module defines  objects type and set all the functions in jerry.c.
- Jerry.c: This file contains all the functions jerry need. Here we create all the structs and connect between them. Also, we got here print functions and free function for every struct.

Finally, the main:
In this part we manage all the jerries we got, and also could change things inside in order to the user wish - add/delete a physical characteristic, print by planet, and more... 
