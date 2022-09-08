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

<img width="495" alt="checker_eg" src="https://user-images.githubusercontent.com/25098095/189168118-4a549b08-ea7d-4713-ae94-2b0e0d81d962.png">

---

### push_swap

Different from checker, push_swap's aim is to produce as small amount of instructions as possible to solve **stack A**. 

***Approach:***

- After trying a couple of solutions, I had the idea to use Merge Sort as my main algorithm to solve this problem. I have implemented iterative and recursive merge sort, and finally decided to go with recursive version due to its speed and more ways to optimize.

- Problem with recursive merge sort is I only have two stacks at disposal, I need to make sure the size of the splitted stack and the container stack known at all time.

- At the same time with the sort, I keep a copy of which numbers there are on the stack so I can make the least movement when merging the two stacks together. 

***Compile:*** `make push_swap`

***Usage:***

<img width="495" alt="push_swap_eg" src="https://user-images.githubusercontent.com/25098095/189168183-d29505d4-e854-4265-b15c-8552eb7219ea.png">

<img width="495" alt="push_swap_checker_eg" src="https://user-images.githubusercontent.com/25098095/189168229-2ef8f400-d9cb-4413-abea-76c6edc5214e.png">


## *Bonuses:*
There are two bonuses that I have done
- visualizer:

![new_med](https://user-images.githubusercontent.com/25098095/189178593-5c9a4c3f-573b-43d2-82cd-139d081933c8.gif)




- test_automate: automate test for a fast evaluation and testing. In this test, it will check:
  -   all the permutation of 3 number stack and 5 number stack. 
  -   check 100 and 500 number stack with 50 permutations of numbers
  -   it will present the worst case, the best case, the average amount of instructions and the score according to the evaluation form
  -   it will create a file called `test_case` to display which string of number was passed as command-line arguments for each case

***Configuration:***

From `bonus/config.py`
- For `automate_test.py`
  - `PUSH_SWAP_PATH` and `CHECKER_PATH` must be provided before executing 
- For `visualizer.py`
  - `pygame` must be installed. To install: `pip3 install pygame`
  - `PUSH_SWAP_PATH` must be provided before executing 
  - Optional: `SIZE` and `DELAY_TIME` can be changed

***Running program:***

To run either program, user need to be at the immediate directory where the progam is store
- `python3 automate_test.py`
- `python3 visualizer.py`


