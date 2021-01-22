"""
Before running this file, please change the value of "name_of_input_file" to the name of the generated file from MATLAB.
Make sure that this script is in the same directory of the generated file from MATLAB.
"""
import os

#name of the input and output files
name_of_input_file="Pos.txt" 
name_of_output_h_file ='Pos.h'

#setting the path of the files
path=os.path.split(os.path.realpath(__file__))[0]
inputfile_path=os.path.join(path,name_of_input_file)
outputfile_path=os.path.join(path,name_of_output_h_file)

#open the input file as read mode
current_file = open(inputfile_path, "r",encoding='utf-8')

#read the number of lines of the input file
File_Contents = current_file.read()
Line_Information = File_Contents.split("\n")
Line_Information_Modified = [""]*(len(Line_Information))

#define the content which will be written in the output file
for i in range(len(Line_Information)):
    Line_Information_Modified[i] = "{" + Line_Information[i] + "}," + "\n"
firstline = "const int PosMat[" + str(len(Line_Information)) + "][6]=" + "\n"
secondline = "{" + "\n"
secondlastline = "};" + "\n"
lastline = "int line="+str(len(Line_Information))+";"

#create the output file in the same directory as the input file and write the content previously defined
new_file = open(outputfile_path, "w+")
new_file.write(firstline)
new_file.write(secondline)

for i in range(len(Line_Information)):
    new_file.write(Line_Information_Modified[i])

new_file.write(secondlastline)
new_file.write(lastline)