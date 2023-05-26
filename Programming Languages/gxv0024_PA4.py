#Name George Vo
#ID: 1001360024
#Date: December 1st, 2021
#OS and Python used: Windows 11 with Python 3.9.9

inputfile = open("./input.txt","r")
depth  = 0
blockComment = 0
for line in inputfile:
    slashcounter = 0
    quoteCounter = 0
    previousChar = ""

    print(str(depth)+" " +line)
    for character in line:
        if character == "{" and quoteCounter == 0 and blockComment == 0:
            depth = depth + 1
        elif character == "}" and quoteCounter == 0 and blockComment == 0:
            depth = depth - 1
        elif character == "/" and slashcounter == 0 and blockComment ==0:
            slashcounter = 1
        elif character == "/" and slashcounter == 1 and blockComment ==0:
            clashcounter = 0
            break
        elif character == '"' and quoteCounter == 0:
            quoteCounter = 1
        elif character == '"' and quoteCounter == 1:
            quoteCounter = 0
        elif character == "/" and previousChar =="*":
            blockComment = 0
        elif character == "*" and previousChar == "/":
            blockComment = 1
        previousChar = character
if depth > 0:
    print("Error: Expected '}', but found EOF. Please check your braces.")
elif depth < 0:
    print("Error: Expected '{', but found EOF. Please check your braces.")
