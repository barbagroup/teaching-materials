##Installation

*  Give step-by-step instructions for installation. Ideally, there should be a set of commands on the website that the user can blindly run, and the program should be installed. We can iterate on these instructions via internal assessments. Try to be as thorough as possible and make no assumptions of the ability of the user. These should begin with cloning/downloading the repository and end with running a script that tests the installation.
*  Mention the OS version (e.g. Ubuntu 12.04) and compiler version (e.g. gcc-4.6, g++-4.7, nvcc-5.0) that you have tested the code with. If it works with multiple versions, mention all of them.
*  Mention all dependencies. Ideally, you should provide instructions on how to install those dependencies. If they are well known, it is sufficient to point to the installation instructions on the website of the dependencies. If you ran into problems yourself while following those instructions, it is very important to mention what they were, and how you fixed them [This happens more often than one would expect. And in most cases, we troubleshoot, find an answer, get it working for ourselves and forget about it].
*  Mention the specific versions of the dependencies that you used to compile your code. It is probably best to use stable versions of dependencies (unless you very badly need a feature that is available only on the development version). 
*  Mention what hardware you ran your code on. This is especially important for GPUs. If someone is using a C1060, then it does not support Compute Capability 2.0 (something that you may be assuming in your compile commands). Then you will need to ask the user to explicitly change the -arch option in the Makefile. You also need to be aware of the problem sizes in your sample cases. What is the size of the largest sample case present in your code repository? Will the user be able to fit it in her GPU?
*  If you are using environment variables, make sure to instruct the user to set them before compiling. For example, CUSP is one of my dependencies, and I need to include the directory while compiling my code. Instead of saying -I /path/to/cusp in the makefile, I can use -I $CUSP_DIR so that each user will not have to modify the makefile. But they do have to set CUSP_DIR before compiling.
*  Ideally, we should have a script that automates searching for dependencies. For example, a script could be run to check if a user has swig installed, and what version it is, and if not, request the user to install it. 
*  If the above is not feasible, we should have a set of commands that the user can run to check if they have the dependencies installed in a way that the Makefile will understand them. e.g. We can ask the user to run nvcc --version, to check if nvcc has been installed, and what version it is. There may also be cases when a user might have compiled a source to obtain the binaries, but the paths have not been set correctly. These checks ensure that the user has set up his executables and dependencies in a way that the makefile assumes.

##Tutorial

*  Include test cases in the code repository. e.g. Flow over a cylinder at Reynolds number 100. The more test cases, the better. Each test case should be able to showcase a different feature of your code, or different types of physical problems that can be solved.
*  Have a tutorial that guides the user from start to finish on how to run a sample test case.
*  Describe the organisation of the input files, how to run the code, and what output the user must expect. 
*  Include instructions to postprocess and visualise results. 
*  The tutorial must be simple, and serve the purpose of giving the user satisfaction that they are able to run a sample test case and see the results. It should be a quick way to demonstrate the capability of your code.
*  It is important that the user gets through the tutorial seamlessly. This will happen if the user is able to install the code without glitches, and has the right operating system and hardware and dependencies installed.
*  It's easy to forget that software like Python, NVCC or libraries like Matplotlib are dependencies, but we need to remember to mention them all. Python is installed by default in all Linux distributions, but Numpy, Matplotlib and Gnuplot are not. Another easily overlooked program is g++, which is not installed by default in Linux distributions.

##Documentation

*  Ideally, we should have a Programming Manual that documents the entire code.
*  At the very least, the code must be extensively commented. 
*  We must definitely have documentation that teaches the user how to run applications using the code. This means that we must describe in detail the organisation of the input files, the contents of the input file, the meanings of each option and what values they can take. Also mention units. (Is the length scale in angstrom units? Is the angle in radians or degrees? If they are non-dimensionalised, what are the reference values?)
*  If your code takes command line arguments, list all of them and the values they can take.
*  If you have python scripts, the argparse function is very useful for command line arguments, and it can be configured to display a help message listing the purpose of the script, the command line options and the default values. 
*  The documentation should also include a mention of all the scripts you have and their purposes. e.g. I have some scripts to generate certain types of bodies and meshes which will help the user create their own test cases.
*  Include detailed instructions for post-processing. What is the format of the output file (ASCII/Binary? HDF5/CSV? etc.)? What programs will be able to read it? Do you have any automatic scripts to generate visualisations/plots? What input options can those scripts take?
