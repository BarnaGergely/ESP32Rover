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
    compressed_html = compress_file()
    save_to_header_file("src/index_html.h")
    convert_to_c_array_and_save_to_header_file(compressed_html, "src/index_html_gz.h")
    

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
        minified_js = jsmin.jsmin(js)
        #minified_js = js # uncomment it to disable minify

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

    # if file is not exist in input folder, return
    if not os.path.exists(f"{temp_folder}/{file_name}.html"):
        print(f"File {temp_folder}/{file_name}.html not found")
    return

def compress_file():
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
    return compressed_html

def save_to_header_file(output_file):
    print("Saving HTML to header file")

    # if file is not exist in input folder, return
    if not os.path.exists(f"{temp_folder}/{file_name}.html"):
        print(f"File {temp_folder}/{file_name}.html not found")
        return
    
    with open(f"{temp_folder}/{file_name}.html", "r") as f:
        html = f.read()

    header_content = f'const char index_html[] PROGMEM = R"rawliteral({html})rawliteral";'

    with open(output_file, "w") as f:
        f.write("// This file is generated by `build_file_system_image.py`. Do not edit it. Run Build Filesystem Image to update it.\n")
        f.write("// Source Files: `web/src/index.html` and its dependencies\n")
        f.write(header_content)
        print(f"HTML as header saved to {output_file}")
    return

def convert_to_c_array_and_save_to_header_file(byte_array, output_file):
    print("Converting data to C-style byte array")
    # c_array = ', '.join(f'0x{byte:02X}' for byte in byte_array)
    c_array = ', '.join('0x{:02X}'.format(b) for b in byte_array)

    c_array = f"const char index_html_gz[] = {{\n    {c_array}\n}};"

    with open(output_file, "w") as f:
        f.write("// This file is generated by `build_file_system_image.py`. Do not edit it. Run Build Filesystem Image to update it.\n")
        f.write("// Source Files: `web/src/index.html` and its dependencies\n")
        f.write(c_array)
    print(f"C-style byte array saved to {output_file}")
    return