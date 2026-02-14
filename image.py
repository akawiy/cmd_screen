# Made on 25th June 2023
# Python 3.10
# Use only in terminal (OSError otherwise)
# Originally supports JPG and PNG images

from PIL import Image
from os import system as syscmd, get_terminal_size
from platform import system as platform_
from sys import argv


def clear_console() -> None:
    syscmd("cls" if platform_().lower() == "windows" else "clear")


def chunk(arr: list, n: int) -> list:
    for i in range(0, len(arr), n):
        yield arr[i:i + n]


def load_and_prepare_image(image_name: str) -> Image:
    image = Image.open(f"static/images/{image_name}", "r")
    grayscaled_image = image.convert("L")

    size = grayscaled_image.size
    resized_image = grayscaled_image.resize((
        get_terminal_size().columns,
        round(0.5 * get_terminal_size().columns * size[1] / size[0])))
    
    return resized_image


def get_pixels_matrix(image: Image) -> list:
    pixels_array = list(image.getdata())
    pixels_matrix = list(chunk(pixels_array, image.size[0]))
    
    return pixels_matrix


def convert_pixels_to_symbols(pixels_matrix: list) -> list:
    symbols = " .,-~:;=!*#$@"
    symbol_brightness = 256 / len(symbols)
    symbols_matrix = list([
        list([
            symbols[int(pixel / symbol_brightness)]
            for pixel in line])
        for line in pixels_matrix])

    return symbols_matrix


def print_image(symbols_matrix: list) -> None:
    # for line in symbols_matrix:
    #     print("".join(line))
    print("".join(["".join(line) for line in symbols_matrix]))


def make(image_name: str) -> None:
    image = load_and_prepare_image(image_name)
    pixels_matrix = get_pixels_matrix(image)
    symbols_matrix = convert_pixels_to_symbols(pixels_matrix)
    clear_console()
    print_image(symbols_matrix)


def main() -> None:
    if len(argv) == 2:
        make(argv[1])
    else:
        clear_console()
        while True:
            make(input("File name > "))


if __name__ == '__main__':
    main()
