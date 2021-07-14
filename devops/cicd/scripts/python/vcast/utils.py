import logging
from typing import List, Optional


def write_list_to_text(
    out_filename: str, target: List[str], end_char: str = ""
) -> None:
    """Writes a given target list to the provided text file path"""
    with open(out_filename, "w") as f:
        for element in target:
            f.write(f"{element}{end_char}")


def setup_logging() -> None:
    """Provides the logging configuration for the module"""
    root = logging.getLogger()
    if root.handlers:
        for handler in root.handlers:
            root.removeHandler(handler)
    logging.basicConfig(format="%(asctime)s %(message)s", level=logging.INFO)
