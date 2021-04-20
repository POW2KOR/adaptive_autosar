"""
Script used to gather all the needed tools for building the docker image.
The script SHALL be ran from the root folder.

Usage:
- download all the dependencies (Artifactory authentification needed)
python3 collect_deps.py

- skip the dependencies from the internet (Artifactory authentification needed)
python3 collect_deps.py -i

- skip the dependencies from the Artifactory
python3 collect_deps.py -a
"""

import sys
import argparse
import os.path
import urllib.request
import urllib.error
import shutil
import hashlib
import getpass
from enum import Enum
import json

artifactory = "https://artifact.swf.daimler.com/"

# create argument parser
arg_parser = argparse.ArgumentParser(
    prog="collect_deps",
    usage="%(prog)s [options]",
    description="Collect dependencies for docker image",
)

# add arguments
arg_parser.add_argument(
    "-i", action="store_false", help="Don't download dependencies from the internet"
)
arg_parser.add_argument(
    "-a", action="store_false", help="Don't download dependencies from artifactory"
)


class HashAlgo(Enum):
    NONE = 0
    SHA256 = 1
    SHA1 = 2
    MD5 = 3


# parse arguments
args = arg_parser.parse_args()


def getFileHash(file, algo):
    BUF_SIZE = 65536  # read in 64kb chunks!
    calcHash = None

    if algo == HashAlgo.SHA256:
        calcHash = hashlib.sha256()
    elif algo == HashAlgo.SHA1:
        calcHash = hashlib.sha1()
    elif algo == HashAlgo.MD5:
        calcHash = hashlib.md5()
    else:
        raise Exception("Unsupported Hash algorithm " + str(algo))
        return calcHash

    with open(file, "rb") as f:
        while True:
            data = f.read(BUF_SIZE)
            if not data:
                break
            calcHash.update(data)

    return calcHash.hexdigest()


def downloadPackage(remote, localFile, expectedHash=None, user=None, password=None):

    if not os.path.isfile(localFile):
        localPath = os.path.dirname(localFile)
        if not os.path.exists(localPath):
            try:
                os.makedirs(localPath)
            except OSError:
                print("Failed to create base directory: %s" % localPath)
                sys.exit(1)
            else:
                print("Base directory %s created successfully" % localPath)

        print("Downloading " + localFile + " ...")

        request_param = urllib.request.Request(remote)
        if user != None and password != None:

            # Create a password manager
            manager = urllib.request.HTTPPasswordMgrWithDefaultRealm()
            manager.add_password(None, remote, user, password)

            # Create an authentication handler using the password manager
            auth = urllib.request.HTTPBasicAuthHandler(manager)

            # Create an opener that will replace the default urlopen method on further calls
            opener = urllib.request.build_opener(auth)
            urllib.request.install_opener(opener)

        try:
            with urllib.request.urlopen(request_param) as response, open(
                localFile, "wb"
            ) as out_file:
                shutil.copyfileobj(response, out_file)

            print("Downloading " + localFile + " finished.")

        except urllib.error.HTTPError as exception:
            print(exception)
            return False

    if expectedHash != None:
        calcHash = getFileHash(localFile, HashAlgo.SHA256)
        if calcHash != None:
            if calcHash.upper() != expectedHash.upper():
                print("Hash mismatch for " + localFile)
                print("Expected  : " + expectedHash.upper() + " vs.")
                print("Calculated: " + calcHash.upper())
                return False
            else:
                print("Hash for " + localFile + ": matches")
        else:
            print("Failed to generate SHA256 hash for file " + localFile)
            return False

    return True


def downloadArtifactoryFiles():

    with open("./configuration/tools.json", "r") as myFile:
        data = myFile.read()
    myFile.close()
    tools_artifactory = json.loads(data)

    download = False
    for tool in tools_artifactory["files"]:
        if not os.path.isfile(tool["target"]):
            download = True
            break
        else:
            print("Local File " + tool["target"] + " already exists.")

    if not download:
        return True

    user = input("Username:")
    passwd = getpass.getpass("Password for " + user + ":")

    ret = True

    for tool in tools_artifactory["files"]:
        if not downloadPackage(
            (artifactory + tool["pattern"]), tool["target"], user=user, password=passwd
        ):
            print("Downloading " + tool["target"] + " failed!")
            ret = False
    return ret


ret = 0

if args.i:
    with open("./configuration/tools_web.json", "r") as myFile:
        data = myFile.read()
    myFile.close()
    tools_web = json.loads(data)
    for tool in tools_web["files"]:
        fileHash = tool["props"].split("=")[1]
        if not downloadPackage(tool["pattern"], tool["target"], fileHash):
            print("Downloading " + tool["pattern"] + " failed!")
            ret = 1

if args.a:
    if not downloadArtifactoryFiles():
        ret = 1
