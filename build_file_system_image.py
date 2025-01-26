from web.build.build_web import build_web

Import("env")

def before_build_filesystem(source, target, env):
    print("Running custom scripts before building filesystem")
    build_web()
    return

env.AddPreAction("buildfs", before_build_filesystem)