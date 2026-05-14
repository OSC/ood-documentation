#!/usr/bin/env python3

# Usage examples:
#   python tasks.py --help
#   python tasks.py build
#   python tasks.py spellcheck
#   python tasks.py open


import argparse
import os
import platform
import shutil
import subprocess
import sys

IMAGE = "ohiosupercomputer/ood-doc-build:v3.1.0"
PROJECT_DIR = os.path.dirname(os.path.abspath(__file__))


def is_windows() -> bool:
    return platform.system().lower().startswith("win")

def is_codespace() -> bool:
    return (os.getenv('CODESPACES') == 'true')

def exists(program: str) -> bool:
    # Cross-platform check if a program exists in PATH
    return shutil.which(program) is not None


def docker_available() -> bool:
    return exists("docker")


def podman_available() -> bool:
    return exists("podman")


def run_cmd() -> list:
    """Compose the container runtime command list analogous to Rakefile's run_cmd."""
    mount_arg = f"{PROJECT_DIR}:/doc"

    if podman_available():
        return [
            "podman",
            "run",
            "--rm",
            "-it",
            "-v",
            mount_arg,
            IMAGE,
        ]
    if docker_available():
        cmd = [
            "docker",
            "run",
            "--rm",
            "-it",
            "-v",
            mount_arg,
        ]
        cmd.append(IMAGE)
        return cmd

    raise RuntimeError(
        "Cannot find any suitable container runtime to build. Need 'podman' or 'docker' installed."
    )


def _print_and_exec(full_cmd: list) -> int:
    print(" ".join(full_cmd))
    proc = subprocess.Popen(full_cmd)
    proc.wait()
    return proc.returncode


def cmd_build(_args) -> int:
    """Build docs using container (docker/podman)."""
    try:
        cmd = run_cmd() + [
            "make",
            "html",
        ]
    except RuntimeError as e:
        print(str(e), file=sys.stderr)
        return 1
    return _print_and_exec(cmd)


def cmd_spellcheck(_args) -> int:
    """Spellcheck documentation using container (docker/podman)."""
    try:
        cmd = run_cmd() + [
            "make",
            "spellcheck",
        ]
    except RuntimeError as e:
        print(str(e), file=sys.stderr)
        return 1
    return _print_and_exec(cmd)


def cmd_open(_args) -> int:
    """Open built documentation in browser."""
    index_path = os.path.join(PROJECT_DIR, "build", "html", "index.html")
    if is_windows():
        try:
            os.startfile(index_path)  # type: ignore[attr-defined]
            return 0
        except OSError as e:
            print(f"Failed to open {index_path}: {e}", file=sys.stderr)
            return 1
    if is_codespace():
        return _print_and_exec(["python", "-m", "http.server", "8000", "--directory", "build/html"])
    if shutil.which("xdg-open"):
        return subprocess.call(["xdg-open", index_path])
    if shutil.which("open"):
        return subprocess.call(["open", index_path])

    print(
        "Could not find a suitable opener (xdg-open/open). Open this file manually: "
        + index_path,
        file=sys.stderr,
    )
    return 1


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Tasks for building and managing documentation",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    sub = parser.add_subparsers(dest="command")

    p_build = sub.add_parser("build", help="Build documentation using container")
    p_build.set_defaults(func=cmd_build)

    p_spell = sub.add_parser("spellcheck", help="Spellcheck documentation using container")
    p_spell.set_defaults(func=cmd_spellcheck)

    p_open = sub.add_parser("open", help="Open built documentation HTML in browser")
    p_open.set_defaults(func=cmd_open)

    return parser


def main(argv=None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    # Default behavior similar to Rakefile default task: show available tasks
    if not getattr(args, "command", None):
        parser.print_help()
        return 0

    func = getattr(args, "func", None)
    if func is None:
        parser.print_help()
        return 2

    return int(func(args) or 0)


if __name__ == "__main__":
    sys.exit(main())
