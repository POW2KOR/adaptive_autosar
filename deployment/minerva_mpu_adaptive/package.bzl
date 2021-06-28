"""
Defining the release version string
"""

# The Vector amsrswpkg_generator tool does not support SemVer fully (for
# example, it doesn't support pre-release tags), so we can't use them.
VERSION = "0.4.0"

VERSION_MAJOR = VERSION.split(".")[0]
VERSION_MINOR = VERSION.split(".")[1]
VERSION_PATCH = VERSION.split(".")[2]

SW_PARTNUMBER = "0123456789"
