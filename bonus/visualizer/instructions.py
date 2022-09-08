import random

def swap(stack):
	stack_len = len(stack)
	if stack_len <= 1:
		return
	node = stack.pop(1)
	stack.insert(0, node)

def rotate(stack):
	stack_len = len(stack)
	if stack_len <= 1:
		return
	node = stack.pop(0)
	stack.append(node)

def reverse_rotate(stack):
	stack_len = len(stack)
	if stack_len <= 1:
		return
	node = stack.pop(stack_len - 1)
	stack.insert(0, node)

def push(stack_a, stack_b):
	stack_a_len = len(stack_a)
	if stack_a_len <= 0:
		return ;
	node = stack_a.pop(0)
	stack_b.insert(0, node)

def instructions(op, stack_a, stack_b):
	if op == "sa":
		swap(stack_a)
	elif op == "sb":
		swap(stack_b)
	elif op == "ss":
		swap(stack_a)
		swap(stack_b)
	elif op == "ra":
		rotate(stack_a)
	elif op == "rb":
		rotate(stack_b)
	elif op == "rr":
		rotate(stack_a)
		rotate(stack_b)
	elif op == "rra":
		reverse_rotate(stack_a)
	elif op == "rrb":
		reverse_rotate(stack_b)
	elif op == "rrr":
		reverse_rotate(stack_a)
		reverse_rotate(stack_b)
	elif op == "pb":
		push(stack_a, stack_b)
	elif op == "pa":
		push(stack_b, stack_a)

