import os
import gzip
import io
import subprocess
import sys

try:
    from webassets import Environment, Bundle
    import htmlmin
except ImportError:
    print("webassets or filters not found, installing...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "webassets", "htmlmin", "cssmin", "jsmin"])

from webassets import Environment, Bundle
import htmlmin

input_folder = "web/src"
output_folder = "data"
file_name = "index.html"

def build_web():
    print("Building web page")

    # Create an environment
    env = Environment(directory=input_folder, url='/static')

    # Define the bundles
    css_bundle = Bundle('index.css', filters='cssmin')
    js_bundle = Bundle('index.js', filters='jsmin')

    # Build the bundles in memory
    with open(os.path.join(input_folder, 'index.html'), 'r') as html_file:
        html_content = html_file.read()
    html_content = htmlmin.minify(html_content)
    
    css_content = ''.join([content[1] for content in css_bundle.resolve_contents(env)])
    js_content = ''.join([content[1] for content in js_bundle.resolve_contents(env)])

    # Combine the contents
    combined_content = f"{html_content}\n<style>{css_content}</style>\n<script>{js_content}</script>"

    # Ensure the output folder exists
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Gzip the combined content in memory
    gzip_buffer = io.BytesIO()
    with gzip.GzipFile(fileobj=gzip_buffer, mode='wb') as f_out:
        f_out.write(combined_content.encode('utf-8'))

    # Write the gzipped content to a file
    gzip_file_path = os.path.join(output_folder, f"{file_name}.gz")
    with open(gzip_file_path, 'wb') as f_out:
        f_out.write(gzip_buffer.getvalue())

    print(f"Web page built and saved to {gzip_file_path}")