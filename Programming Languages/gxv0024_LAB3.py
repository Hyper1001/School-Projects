#Name George Vo
#ID: 1001360024
#Date: November 12, 2021
#OS used: Windows 11

import os #import statement
file = open("./input_RPN.txt","r") #opens file for reading.
while True: #will run until false (never happens)
    line = file.readline() #reads next line of the file
    if not line: #if nothing is there then stop the while loop.
        break
    tokens = line.split() #split each input into an array of strings
    stack = [] #build stack to put values in
    for token in tokens: #iterates through every element in array
        if token != "+" and token != "-" and token != "/" and token !="*": #checks if element is an operator
            stack.append(int(token)) #adds integer to stack
        else:
            b = stack.pop() #pops second operand
            a = stack.pop() #pops first operand
            if token=="+": #if operator is a plus then append a+b
                stack.append(a+b)
            elif token=="-": #if operator is a minus then append a-b
                stack.append(a-b)
            elif token=="/": #if operator is a divide then perform a/b, turn it into an integer, then append it.
                stack.append(int(a/b))
            else: #assumes that it is a multiplication operator, so append a*b
                stack.append(a*b)
    print(line.strip()) #prints RPN equation so we can have a reference.
    #At this point, the stack should only contain one value which should be the answer.
    print("Answer - %d\n"%stack.pop()) #We can pop the stack to get the answer and print it.
