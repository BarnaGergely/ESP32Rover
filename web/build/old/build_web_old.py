import os
from .htmlmerger_cli import merge

input_folder = "web/src"
output_folder = "data"

file_name = "index.html"

def build_web():
    print("Building web page")

    minify_files()
    merge_files()
    compress_files()
   
    return

def merge_files():
    print("Merging web files")

     # if output_folder is not exist, create it
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # if output folder allready contains file, remove it
    if os.path.exists(f"{output_folder}/{file_name}"):
        os.remove(f"{output_folder}/{file_name}")

    # if File_name is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}"):
        print(f"File {input_folder}/{file_name} not found")
        return

    merge(f"{input_folder}/{file_name}", f"{output_folder}/{file_name}")

def minify_files():
    print("Minifying web files")
    return

def compress_files():
    print("Compressing web files")
    return