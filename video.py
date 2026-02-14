# Started on 25th June 2023
# Finished on 26th June 2023
# Python 3.10
# Use only in terminal (OSError otherwise)
# Originally supports MP4 videos

import cv2

from image import *
from time import sleep
from progress_bars import VideoFramesProgressBar
# from time import time


def load_video(video_path: str) -> cv2.VideoCapture:
    video = cv2.VideoCapture(video_path)
    # video.set(cv2.CAP_PROP_FPS, 20)

    return video


def prepare_frame(frame) -> str:
    color_coverted = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    image = Image.fromarray(color_coverted)
    grayscaled_image = image.convert("L")

    size = grayscaled_image.size
    resized_image = grayscaled_image.resize((
        get_terminal_size().columns,
        round(0.5 * get_terminal_size().columns * size[1] / size[0])))

    pixels_matrix = get_pixels_matrix(resized_image)
    symbols_matrix = convert_pixels_to_symbols(pixels_matrix)

    return "".join(["".join(line) for line in symbols_matrix])


def make_frames(video: cv2.VideoCapture) -> list:
    frames = []
    frames_n = int(video.get(cv2.CAP_PROP_FRAME_COUNT))

    progress_bar = VideoFramesProgressBar()
    progress_bar.start()

    frame_n = 0
    while True:
        success, frame = video.read()

        if success and frame_n % 2 == 0:
            frames.append(prepare_frame(frame))
        elif not success:
            break

        frame_n += 1
        progress_bar.update(frame_n / frames_n, frame_n)

    progress_bar.done(frames_n)
    return frames


def play_video(frames: list, fps: int) -> None:
    clear_console()

    # last_second_time = time()
    delay = 1 / fps

    for index, frame in enumerate(frames):
        # if index != 0 and index % fps == 0:
        #     delay -= (1 - time() + last_second_time) / fps
        #     last_second_time = time()
        print(frame)
        sleep(max(delay, 0))

    if input("Replay? ('y' or 'n') ") == "y":
        play_video(frames, fps)


def make(video_name: str, video_location: str = "static/videos", new_line: bool = False) -> None:
    if new_line:
        print()
    video = load_video(f"{video_location}/{video_name}")
    fps = video.get(cv2.CAP_PROP_FPS)
    frames = make_frames(video)
    video.release()
    print()
    input(f"The video '{video_location}/{video_name}' is ready. Press enter to start")
    play_video(frames, fps)


def main():
    if len(argv) == 2:
        make(argv[1], new_line=True)
    else:
        clear_console()
        while True:
            make(input("File name > "), new_line=True)


if __name__ == '__main__':
    main()
