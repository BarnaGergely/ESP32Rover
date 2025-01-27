
# This script is used to build web page for Arduino by minifying, merging, and compressing web files

# Library documentations:
# https://opensource.perlig.de/rcssmin/
# https://github.com/ndparker/rcssmin

# https://github.com/mankyd/htmlmin
# https://pypi.org/project/htmlmin/

# https://pypi.org/project/jsmin/
# https://github.com/tikitu/jsmin/

import gzip
import os

from .htmlmerger_cli import merge
import rcssmin
import htmlmin
import jsmin



def build_web():
    print("Building web page")

    # if output_folder is not exist, create it
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # if temp_folder is not exist, create it
    if not os.path.exists(temp_folder):
        os.makedirs(temp_folder)

    minify_files()
    merge_files()
    compress_files()

    print(f"Web page built and saved to {temp_folder}/{file_name}.html.gz")
    return

def minify_files():
    print("Minifying web files")

    # if minify_folder is not exist, create it
    if not os.path.exists(minify_folder):
        os.makedirs(minify_folder)

    # Minify CSS
    print("Minifying CSS")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.css"):
        print(f"File {input_folder}/{file_name}.css not found")
        return

    with open(f"{input_folder}/{file_name}.css", "r") as f:
        css = f.read()
        minified_css = rcssmin.cssmin(css)

        with open(f"{minify_folder}/{file_name}.css", "w") as f:
            f.write(minified_css)
        print("CSS minified")

    # Minify JS
    print("Minifying JS")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.js"):
        print(f"File {input_folder}/{file_name}.js not found")
        return

    with open(f"{minify_folder}/{file_name}.js", "r") as f:
        js = f.read()
        minified_js = jsmin.jsmin(js)

        with open(f"{minify_folder}/{file_name}.js", "w") as f:
            f.write(minified_js)
        print("JS minified")

    # Minify HTML
    print("Minifying HTML")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.html"):
        print(f"File {input_folder}/{file_name}.html not found")
        return

    with open(f"{minify_folder}/{file_name}.html", "r") as f:
        html = f.read()
        minified_html = htmlmin.minify(html, remove_comments=True, remove_empty_space=True)

        with open(f"{minify_folder}/{file_name}.html", "w") as f:
            f.write(minified_html)
        print("HTML minified")
    return

def merge_files():
    print("Merging web files")

    # if File_name is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.html"):
        print(f"File {input_folder}/{file_name} not found")
        return

    merge(f"{minify_folder}/{file_name}.html", f"{temp_folder}/{file_name}")
    return

def compress_files():
    print("Compressing web files")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{temp_folder}/{file_name}.html"):
        print(f"File {temp_folder}/{file_name}.html not found")
        return
    
    with open(f"{temp_folder}/{file_name}.html", "rb") as f:
        html = f.read()
        compressed_html = gzip.compress(html)

        with open(f"{output_folder}/{file_name}.html.gz", "wb") as f:
            f.write(compressed_html)
        print("HTML compressed")

    return