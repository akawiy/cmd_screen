from os import get_terminal_size
from time import time


class VideoFramesProgressBar:
	def __init__(self) -> None:
		self.last_percent = 0
		# self.symbols = " ▏▎▍▌▋▊▊▉▉█"
		self.symbols = " " * 5 + "\u258c" * 5 + "\u2588"
		self.start_time = None

	def start(self) -> None:
		self.start_time = time()
		self.update(0, 0)

	def update(self, percent: [int, float], frame_n: int) -> None:
		percent *= 100
		self.last_percent = percent
		if percent > 0:
			time_left = (time() - self.start_time) / percent * (100 - percent)
			msg = f"Loading frames  /  " \
				  f"[{self.get_loading_bar(percent)}] / {round(percent, 1)}%  /  " \
				  f"{frame_n} frames loaded  /  " \
				  f"{round(time_left, 1)} seconds left"
		else:
			msg = f"Loading frames..."
		print(msg + " " * (get_terminal_size().columns - len(msg) - 1), end="\r")

	def get_loading_bar(self, percent: [int, float]) -> str:
		return ''.join([self.get_symbol(round(percent - j * 10)) for j in range(10)])

	def get_symbol(self, index: int) -> str:
		if index <= 0:
			return " "
		return self.symbols[index] if index < 10 else self.symbols[10]

	def done(self, total_frames):
		total_time = time() - self.start_time
		msg = f"Successfully loaded {total_frames} frames in {round(total_time, 1)} seconds  /  " \
			  f"[{self.symbols[-1] * 10}] 100%"
		print(msg + " " * (get_terminal_size().columns - len(msg) - 1))


class YoutubeVideoProgressBar:
	def __init__(self) -> None:
		self.last_percent = 0
		# self.symbols = " ▏▎▍▌▋▊▊▉▉█"
		self.symbols = " " * 5 + "\u258c" * 5 + "\u2588"
		self.start_time = None

	def start(self) -> None:
		self.start_time = time()
		self.update(0)

	def update(self, percent: [int, float]) -> None:
		percent *= 100
		self.last_percent = percent
		if percent > 0:
			time_left = (time() - self.start_time) / percent * (100 - percent)
			msg = f"Downloading video from YouTube  /  " \
				  f"[{self.get_loading_bar(percent)}] / {round(percent, 1)}%  /  " \
				  f"{round(time_left, 1)} seconds left"
		else:
			msg = f"Downloading video from YouTube..."
		print(msg + " " * (get_terminal_size().columns - len(msg) - 1), end="\r")

	def get_loading_bar(self, percent: [int, float]) -> str:
		return ''.join([self.get_symbol(round(percent - j * 10)) for j in range(10)])

	def get_symbol(self, index: int) -> str:
		if index <= 0:
			return " "
		return self.symbols[index] if index < 10 else self.symbols[10]

	def done(self):
		total_time = time() - self.start_time
		msg = f"Successfully downloaded video from YouTube in {round(total_time, 1)} seconds  /  " \
			  f"[{self.symbols[-1] * 10}] 100%"
		print(msg + " " * (get_terminal_size().columns - len(msg) - 1))
