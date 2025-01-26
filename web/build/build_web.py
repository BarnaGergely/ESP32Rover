# https://opensource.perlig.de/rcssmin/
# https://github.com/ndparker/rcssmin

# https://github.com/mankyd/htmlmin
# https://pypi.org/project/htmlmin/

# https://pypi.org/project/jsmin/
# https://github.com/tikitu/jsmin/

import gzip
import os
import rcssmin

try:
    import rcssmin
except ImportError:
    print("rcssmin not found. Install it using 'pip install rcssmin'")

input_folder = "web/src"
output_folder = "data"
temp_folder = "web/build/.temp"

def build_web():
    print("Building web page")

    # Minify CSS and 

    print(f"Web page built and saved to {}")
    return