Import("env")
import os
import gzip
from web.build.htmlmerger_cli import merge

try:
    import rcssmin
except ImportError:
    print("rcssmin not found. Installing rcssmin...")
    env.Execute("$PYTHONEXE -m pip install rcssmin")

try:
    import htmlmin
except ImportError:
    print("htmlmin not found. Installing htmlmin...")
    env.Execute("$PYTHONEXE -m pip install htmlmin")

try:
    import jsmin
except ImportError:
    print("jsmin not found. Installing jsmin...")
    env.Execute("$PYTHONEXE -m pip install jsmin")

input_folder = "web/src"
output_folder = "data"
temp_folder = "web/build/.temp"
minify_folder = f"{temp_folder}/minified"
file_name = "index"

def before_build_filesystem(source, target, env):
    print("Running custom scripts before building filesystem")
    build_web()
    return

env.AddPreAction("buildfs", before_build_filesystem)

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

    # Minify JS
    print("Minifying JS")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.js"):
        print(f"File {input_folder}/{file_name}.js not found")
        return

    with open(f"{input_folder}/{file_name}.js", "r") as f:
        js = f.read()
        #minified_js = jsmin.jsmin(js)
        minified_js = js

        with open(f"{minify_folder}/{file_name}.js", "w") as f:
            f.write(minified_js)

    # Minify HTML
    print("Minifying HTML")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{input_folder}/{file_name}.html"):
        print(f"File {input_folder}/{file_name}.html not found")
        return

    with open(f"{input_folder}/{file_name}.html", "r") as f:
        html = f.read()
        minified_html = htmlmin.minify(html, remove_comments=True, remove_empty_space=True)

        with open(f"{minify_folder}/{file_name}.html", "w") as f:
            f.write(minified_html)
    return

def merge_files():
    print("Merging web files")

    # if File_name is not exist in input folder, return
    if not os.path.exists(f"{minify_folder}/{file_name}.html"):
        print(f"File {minify_folder}/{file_name} not found")
        return

    merge(f"{minify_folder}/{file_name}.html", f"{temp_folder}/{file_name}.html")
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
    print(f"Compressed HTML saved to {output_folder}/{file_name}.html.gz")
    return