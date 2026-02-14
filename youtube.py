# Fully made on 15th July 2023
# Python 3.10
# Use only in terminal (OSError otherwise)

from pytube import YouTube
from video import *
from progress_bars import YoutubeVideoProgressBar


def download_video(url) -> str:
	print()
	progress_bar = YoutubeVideoProgressBar()
	progress_bar.start()

	youtube_video = YouTube(url)
	youtube_video = youtube_video.streams.get_highest_resolution()
	youtube_video.download("./static/videos/downloaded")

	progress_bar.done()

	return youtube_video.default_filename


def main():
	if len(argv) == 2:
		file_name = download_video(argv[1])
		make(file_name, video_location="static/videos/downloaded")
	else:
		clear_console()
		while True:
			file_name = download_video(input("YouTube video URL > "))
			make(file_name, video_location="static/videos/downloaded")


if __name__ == '__main__':
	main()
