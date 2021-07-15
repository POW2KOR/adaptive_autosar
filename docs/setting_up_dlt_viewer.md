# Setting up DLT-Viewer

steps to be followed for viewing the log in dlt-viewer
## On Host System

```
git clone https://github.com/GENIVI/dlt-viewer
cd dlt-viewer
```
install the packages for dlt-viewer

```
sudo apt install build-essential
sudo apt install qtcreator
sudo apt install qt5-default
sudo apt install libqt5serialport5-dev
```

Generate you dlt-viewer binary

```
mkdir build
cd build
```
Generates the makefile inside build folder and run it

```
qmake ../BuildDltViewer.pro
make
sudo make install
sudo ldconfig
```

Now finally viewing the log execute the binary

```
cd  release
./dlt-viewer
```

You can add on filters for ECU,Application ID,Context ID ,etc. Depending upon your need.

You can also export this log locally to your system by right cliking on log window and choose the right option of export like CSV or others.
