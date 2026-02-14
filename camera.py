# Made on 4th July 2023
# Python 3.10
# Use only in terminal (OSError otherwise)
# Idk if it's working cause my camera broke :(
# Edit 21.11.2024: I have a working camera now and I modified the code a lil bit so it's working!!!
# But I have no clue how to make image stable so maybe cya in 2025

import cv2
from PIL import Image
from sys import argv
from shutil import get_terminal_size as gts
from image import get_pixels_matrix, convert_pixels_to_symbols


def load_capture() -> cv2.VideoCapture:
	capture = cv2.VideoCapture(0)

	return capture


def prepare_frame(frame) -> str:
	color_coverted = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

	image = Image.fromarray(color_coverted)
	grayscaled_image = image.convert("L")

	size = grayscaled_image.size
	resized_image = grayscaled_image.resize((
		gts().columns,
		round(0.5 * gts().columns * size[1] / size[0])))

	pixels_matrix = get_pixels_matrix(resized_image)
	symbols_matrix = convert_pixels_to_symbols(pixels_matrix)

	return "".join(["".join(line) for line in symbols_matrix])


def play(capture: cv2.VideoCapture):
	while True:
		success, frame = capture.read()

		if success and frame is not None:
			frame_str = prepare_frame(frame)
			print(frame_str, end="\r")
		elif not success:
			pass  # break


def start() -> None:
	capture = load_capture()
	play(capture)


def main():
	if len(argv) == 1:
		start()


if __name__ == '__main__':
	main()
