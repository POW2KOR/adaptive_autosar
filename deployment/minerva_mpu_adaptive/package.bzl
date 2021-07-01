"""
Defining the release version string
"""

# The Vector amsrswpkg_generator tool does not support SemVer fully (for
# example, it doesn't support pre-release tags), so we can't use them.
VERSION = "0.4.0"

VERSION_MAJOR = VERSION.split(".")[0]
VERSION_MINOR = VERSION.split(".")[1]
VERSION_PATCH = VERSION.split(".")[2]

# The correct SW partnumber is A10000000001
# Since currently is limited to 10 characters, as workaround two 0 are cut
SW_PARTNUMBER = "A100000001"
