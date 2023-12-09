file = open("input.txt", "r",encoding="utf8")

lines = file.read().split("\n")

file.close()

deltas = [[0,1], [0,-1], [1, 0], [1,1],[1,-1], [-1, 0],[-1,1], [-1,-1]]


# A list of all the numbers adjacent to a givin gear "*" {"y-x1-x2"}
gearNumberSets = []

# bounds
maxY = len(lines)
maxX = len(lines[0]) 

# generate a number coordinate "y-x1-x2" from a givin x,y
def getNumberFromCoordinate(x,y):
    if x < 0 or y < 0 or x >=maxX or y >= maxY: 
        return None
    char =  lines[y][x] 
    if not char.isdigit():
        return None
    
    
    temp = char
    x1=x
    while True:
        if x1-1 < 0:
            break
        temp =  lines[y][x1-1]
        if not temp.isdigit():
            break
        x1-=1
    
    temp = char
    x2=x
    while True:
        if x2+1 >=maxX:
            break
        temp =  lines[y][x2+1]
        if not temp.isdigit():
            break
        x2+=1
    
    return f"{y}-{x1}-{x2}"



for  y, line in enumerate(lines):
    for x, char in enumerate(line):
        if(char == "*"):
            numberCoordinates = set()
            for dx, dy in deltas:
                s = getNumberFromCoordinate(x+dx,y+dy)
                if s:
                    numberCoordinates.add(s)
            if len(numberCoordinates) == 2:
                gearNumberSets.append(numberCoordinates)

nums = []

for numbers in gearNumberSets: 
    ratio = 1
    for numStr in numbers:
        y, x1, x2 = numStr.split("-")
        ratio *= int(lines[int(y)][int(x1):int(x2)+1])
    nums.append(ratio)

print(sum(nums))
