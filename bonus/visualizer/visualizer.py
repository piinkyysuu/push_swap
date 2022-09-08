import random
import pygame
from instructions import *
import subprocess
pygame.font.init()

import sys
sys.path.insert(0, '..')
from config import PUSH_SWAP, SIZE, DELAY_TIME

WIN_WIDTH, WIN_HEIGHT = 950, 580
WIN = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGHT))

STACK_FONT = pygame.font.SysFont('roboto', 35)

STACK_DISPLAY_WIDTH = 450
STACK_DISPLAY_HEIGHT = 500

COLOR_NUMBER = 14

MARGIN_TOP = 50
MARGIN_LEFT = 20
GAP_BETWEEN = 10


FPS = 60

WIDTH = STACK_DISPLAY_WIDTH / SIZE
HEIGHT = int((STACK_DISPLAY_HEIGHT / SIZE))
ALPHA = (COLOR_NUMBER - 1) / SIZE
if SIZE <= 5:
	HEIGHT = HEIGHT // 3
	WIDTH = WIDTH // 2
elif SIZE <= (COLOR_NUMBER - 1):
	ALPHA = 1

pygame.display.set_caption("Push_Swap Visualizer")

def draw_window(stack_a, stack_b):
	WIN.fill((35, 32, 35))
	order = 0
	stack_a_text = STACK_FONT.render("STACK A", 1, (255, 255, 255))
	stack_b_text = STACK_FONT.render("STACK B", 1, (255, 255, 255))
	WIN.blit(stack_a_text, (MARGIN_LEFT, 20))
	WIN.blit(stack_b_text, (MARGIN_LEFT + STACK_DISPLAY_WIDTH + GAP_BETWEEN, 20))
	for s in stack_a:
		draw_rect = pygame.Rect(MARGIN_LEFT, (order * HEIGHT) + MARGIN_TOP, (WIDTH * s[1]), HEIGHT)
		order += 1
		pygame.draw.rect(WIN, s[0], draw_rect)
	order = 0
	for s in stack_b:
		draw_rect = pygame.Rect(460 + MARGIN_LEFT, order * HEIGHT + MARGIN_TOP, (WIDTH * s[1]), HEIGHT)
		order += 1
		pygame.draw.rect(WIN, s[0], draw_rect)
	pygame.display.update()

def combine_list(color_pallete, number_list):
	alpha = 0
	index = 0
	new = []
	order = 0
	for number in number_list:
		new_number = []
		if alpha >= 1:
			alpha = 0
			index += 1
		first_color = color_pallete[index]
		second_color = pygame.Color((255, 255, 255))
		if index < 13:
			second_color = color_pallete[index + 1]
		new_color = pygame.Color.lerp(first_color, second_color, alpha)
		alpha += ALPHA
		order += 1
		new_number.append(new_color)
		new_number.append(order)
		new_number.append(number)
		new.append(new_number)
	return new

def excutePrograms(args):
	data = subprocess.Popen([PUSH_SWAP, args], stdout=subprocess.PIPE)
	output = data.stdout.read()
	data.stdout.close()
	output = list(output.decode("utf-8").split("\n"))
	output.pop()
	return output

def main():
	clock = pygame.time.Clock()
	run = True
	number_list = list(range(1, SIZE + 1))
	color_pallete = [
						pygame.Color(250, 224, 228),
						pygame.Color(247, 202, 208),
						pygame.Color(249, 190, 199),
						pygame.Color(251, 177, 189),
						pygame.Color(255, 153, 172),
						pygame.Color(255, 133, 161),
						pygame.Color(255, 112, 150),
						pygame.Color(255, 92, 138),
						pygame.Color(255, 71, 126),
						pygame.Color(255, 10, 84),
						pygame.Color(201, 24, 74),
						pygame.Color(164, 19, 60),
						pygame.Color(128, 15, 47),
						pygame.Color(89, 13, 34),
					]
	stack_a = combine_list(color_pallete, number_list)
	stack_b = []
	random.shuffle(stack_a)
	new = ' '.join(str(x[2]) for x in stack_a)
	output = excutePrograms(new)
	output_len = len(output)
	print(output_len)
	x = 0
	while run:
		clock.tick(FPS)
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run = False
		draw_window(stack_a, stack_b)
		if x < output_len:
			instructions(output[x], stack_a, stack_b)
			x += 1
		pygame.time.delay(DELAY_TIME)
	pygame.quit()

if __name__ == "__main__":
	main()