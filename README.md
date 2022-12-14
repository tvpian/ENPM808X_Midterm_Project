# ROBOBUTLER (ENPM808X: Midterm Project)

<!-- [![Build Status](https://github.com/tvpian/ENPM808X_Midterm_Project/workflows/Github-CI/badge.svg)](https://github.com/tvpian/ENPM808X_Midterm_Project/actions) -->
<!-- ![Build Status](https://github.com/tvpian/ENPM808X_Midterm_Project/actions/workflows/c-cpp.yml/badge.svg?event=push) -->
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/tvpian/ENPM808X_Midterm_Project/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/tvpian/ENPM808X_Midterm_Project/actions/workflows/c-cpp.yml)
[![Coverage Status](https://coveralls.io/repos/github/tvpian/ENPM808X_Midterm_Project/badge.svg)](https://coveralls.io/github/tvpian/ENPM808X_Midterm_Project)

## Authors

**Design Keeper:** Yashveer Jain 

**Navigator:** Pavan Mantripragada 

**Driver:** Tharun V. Puthanveettil

## Overview
In recent years, because of covid pandemic, there are problems related to  the shortage of staff, and maintaining the social distancing norm in restaurant, and it becomes challenging for a restaurant business to sustain. So, to mitigate the problem we introduce the "Robo-Butler". Robo-butler is a cost-efficient fully autonomous robot that serves food to the customers' table from the kitchen in a restaurant with minimal contact thereby ensuring maximum hygiene. It localizes and track human motion to prevent potential collisions which are possible in a social environment like at the restaurants.

## Note
The code coverage percentage is below 80%. This is because the the test application is unable to find the model configuration files in the repository and also access the live camera feed. However, if the project is cloned and executed as per the [instructions](#Instructions) given below with appropriate [dependencies](#Dependencies) in a local system, the coverage percentage rise above 80%. Find the image attached for reference.
![](data/Coverage_Report.png)


## Quadchart 

![](Quadchart/Quadchart.png)


## UML Class Diagram 

![](UML/revise_2/ClassDiagram.png)

## UML Activity Diagram 

![](UML/revise_2/activityDiagram.png)

## Dependencies
* Install OpenCV version = 4.2

## Instructions
* [Model weights](https://st1.zoom.us/web_client/8csbj6s/html/externalLinkPage.html?ref=https://drive.google.com/file/d/10LKegakpldy-KNNN1zl_M3s7F14WGNPB/view?usp=share_link)
* [Model config](https://st1.zoom.us/web_client/8csbj6s/html/externalLinkPage.html?ref=https://drive.google.com/file/d/1jXfmzGIRXfWdBBpmB_3xWiswqf6ikvaX/view?usp=sharing)
* [Class names](https://st1.zoom.us/web_client/8csbj6s/html/externalLinkPage.html?ref=https://drive.google.com/file/d/1xfHsqlJLQrt4Lozf6Ggnio5qj4Hl9XN9/view?usp=sharing)
Note : 
    - all the files must be present in the `model_utils` dir.

## Standard install via command-line
```
git clone --recursive https://github.com/tvpian/ENPM808X_Midterm_Project.git
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Generating Documentation
```
cd <path to repository>/docs
doxygen
```
## Running cpplint and cppcheck
```
cd <path to repository>
run_cpplint.sh
run_cppcheck.sh
```

## Product Backlog
Click [here](https://docs.google.com/spreadsheets/d/153fBiMFGLif_XUhouHLDlejJ7nZ2Hm-PPDNQ9VNdo48/edit?usp=sharing)

## Sprint 1 Planning and Review
Click [here](https://drive.google.com/drive/folders/1odQl_gm7s2Q0kgg9PrKhJjkwfva-8mNq?usp=sharing) to find sprint 1 planning and review

## Sprint 2 Planning and Review
Click [here](https://drive.google.com/drive/folders/1GB3ihzXtfeo95vwSo6-8V6kUSB9s3I92?usp=sharing) to find sprint 2 planning and review

## Submission Video

### Phase 0
Click [here](https://drive.google.com/drive/folders/1OGrv_k7kIViHYJe9wSSLsaUbflmXJ6Xp?usp=sharing) to go to the folder containing the video

### Phase 1
Click [here](https://drive.google.com/file/d/1J_7hdJ3Lzeyr3CzfL9PiiMlyiiKA-co0/view?usp=sharing) to view the update video

### Phase 2
Click [here](https://drive.google.com/drive/folders/1lvscV5N_c1DWpnAtPZIAcLvEZgbgcCXA?usp=sharing) to view the submission video
