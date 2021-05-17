## Python Script to Register the software details
import os
import sys
import getopt
from datetime import datetime

## Extract the commit ID from command line argument
generated_html_file_default = "MPUPackageReport"
## For getting the docker image
docker = ""
options, value = getopt.getopt(sys.argv[1:], "o:d:", ["output=", "docker="])
for opt, arg in options:
    if opt in ("-o", "--output"):
        generated_html_file_default = arg
    elif opt in ("-d", "--docker"):
        docker = arg
generated_html_file = generated_html_file_default + ".html"

## Get the current date and time for the generation of the
#  report.
current_date_and_time = datetime.now()
current_date_and_time_str = current_date_and_time.strftime("%d/%m/%Y %H:%M:%S")

# Describe here the HTML Page
html_page = """
<!DOCTYPE html>
<html>
<head>
<style>
table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
}
td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}
tr:nth-child(even) {
  background-color: #dddddd;
}
</style>
</head>
<body>
<h1> <p style="color :orange;" > MPU Docker Package List Report</p></h1>
"""
# Update the description
description = (
    "<h3>This page contains the list of packages available in the MPU Docker.</h3>"
)
## Docker tag information to be updated on the generated html file
docker_tag = '<h3>Report refers to the MPU docker tag : <i><p style="color :DodgerBlue;" >{}</p></i>'.format(
    generated_html_file_default
)
## docker location
docker_location = '<h3>Command to pull docker - <i><p style="color :DodgerBlue;" > docker pull {}</p></i>'.format(
    docker
)
# Update the date and time of generation of report
date_and_time_heading = "<h3>Generated On - {}</h3>".format(current_date_and_time_str)
# This is the head row of the table
head_row = """
<table>
  <tr>
    <th>SNo</th>
    <th>Package</th>
    <th>Version</th>
  </tr>
"""
## Declare here the empty row, this will get filled with the package details
package_row = ""
package_count = 1
# Packages list
packages = []
# Creating the List for the package installed using apt-get or dpkg
os.system(" dpkg -l > packageDocker.txt")
with open("packageDocker.txt", "r+", encoding="utf-8") as package_file:
    for line in package_file:
        if "ii" in line:
            res = line.split()
            packages.append({"name": res[1], "version": res[2]})
# Creating the List for the package installed using the Python.
os.system(" pip3 list > PythonPackageDocker.txt")
with open("PythonPackageDocker.txt", "r+", encoding="utf-8") as package_file:
    for line in package_file:
        if "Package" in line or "--" in line:
            continue
        res = line.split()
        packages.append({"name": res[0], "version": res[1]})
packages_display = []
for index, package in enumerate(packages):
    row_string = "<tr><td>{i}</td><td>{p[name]}</td><td>{p[version]}</td></tr>".format(
        i=index + 1, p=package
    )
    packages_display.append(row_string)

html_page = (
    html_page
    + description
    + docker_tag
    + docker_location
    + date_and_time_heading
    + head_row
    + "".join(packages_display)
    + "</body></html>"
)
# Write the data to the "MPUPackageReport.html"
with open(generated_html_file, "w") as html_file:
    html_file.write(html_page)

# Clean up: Remove the temperary file storing the package details.
os.system(" rm -rf packageDocker.txt")
os.system(" rm -rf PythonPackageDocker.txt")
