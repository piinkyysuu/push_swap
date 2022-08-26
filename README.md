# push_swap
Push_swap is the second project in Hive Helsinki's algorithm branch. This project's aim is to introduce students to complexity of algorithms in general and sorting algorithms in specific. 

The task of this project is to sort a stack (**stack A**) of unique numbers in ascending order using an extra stack (**stack B**) and a set of operations.

## *Operations:*

- **sa**  : *swap a* - swap the first 2 elements at the top of stack a. Do nothing if there
is only one or no elements).

- **sb**  : *swap b* - swap the first 2 elements at the top of stack a. Do nothing if there
is only one or no elements).

- **ss**  : **sa** and **sb** at the same time.

- **ra**  : *rotate a* - shift up all elements of stack a by 1. The first element becomes
the last one.

- **rb**  : *rotate b* - shift up all elements of stack a by 1. The first element becomes
the last one.

- **rr**  : **ra** and **rb** at the same time.

- **rra** : *reverse rotate a* - shift down all elements of stack a by 1. The last element
becomes the first one.

- **rrb** : *reverse rotate b* - shift down all elements of stack a by 1. The last element
becomes the first one.

- **rrr** : **rra** and **rrb** at the same time.

- **pa**  : *push a* - take the first element at the top of b and put it at the top of a. Do
nothing if b is empty.

- **pb**  : *push b* - take the first element at the top of a and put it at the top of b. Do
nothing if b is empty.

## *Programs:*

### checker
This program will take arguments and format them into **stack A**. 

After that, checker will wait and read instructions from the standard output, each instruction will be followed by '\n'. 

Once done reading, checker will excute the instructions and display "OK" followed by '\n' if **stack A** is sorted ascendingly and **stack B** is empty. Otherwise, the program will display "KO" followed by '\n'. 

In case of error, program will display "Error" followed by '\n' on the standard error.

***Compile:*** `make checker`

***Usage:*** 

<img width="589" alt="Screenshot 2022-08-26 at 22 54 57" src="https://user-images.githubusercontent.com/25098095/186981552-1ae795c9-004d-4c47-b2af-5b7c8c127d57.png">


---

### push_swap

Different from checker, push_swap's aim is to produce as small amount of instructions as possible to solve **stack A**. 

***Approach:***

- After trying a couple of solutions, I had the idea to use Merge Sort as my main algorithm to solve this problem. I have implemented iterative and recursive merge sort, and finally decided to go with recursive version due to its speed and more ways to optimize.

- Problem with recursive merge sort is I only have two stacks at disposal, I need to make sure the size of the splitted stack and the container stack at all time.

- At the same time with the sort, I keep a copy of which numbers there are on the stack so I can make the least movement when merging the two stacks together. 

***Compile:*** `make push_swap`

***Usage:***

<img width="589" alt="Screenshot 2022-08-26 at 22 51 31" src="https://user-images.githubusercontent.com/25098095/186981200-ce15cd83-e883-4928-9419-14613844e4ba.png">

<img width="589" alt="Screenshot 2022-08-26 at 22 52 04" src="https://user-images.githubusercontent.com/25098095/186981146-d69c7ffb-4e4d-4e72-af19-79e8a44c2359.png">

