file = open("input.txt", "r",encoding="utf8")

lines = file.read().split("\n")

file.close()



# A list of all the numbers in the grid: {y: y, start: (x1,x2)}
numberCoordinates = []

# get all numbers coordinates
for  y, line in enumerate(lines):
    coordinate = { "y": y }
    for x, char in enumerate(line):
        if(char.isdigit()): 
            if (coordinate.get("start") is not None):
                coordinate['end'] = x
            else: 
                coordinate['start'] = x
                coordinate['end'] = x
        else:
            if coordinate.get("start") is not None:
                numberCoordinates.append(coordinate)
            coordinate={"y": y}


deltas = [[0,1], [0,-1], [1, 0], [1,1],[1,-1], [-1, 0],[-1,1], [-1,-1]]

# bounds
maxY = len(lines)
maxX = len(lines[0]) 


def isSymbol(x,y):
    if x < 0 or y < 0 or x >=maxX or y >= maxY: 
        return False
    char =  lines[y][x] 
    if char.isdigit() or char == ".":
        return False
    return True

nums = []

def checkCoordinate(coordinate):
    ans = ""
    valid = False
    y = coordinate["y"]

    # Adds the number to nums if at least on digit is adjacent to a symbol
    for x in range(coordinate["start"],coordinate['end']+1):
        for dx, dy in deltas:
            if isSymbol(x+dx, y+dy):
                valid = True 
        ans+=lines[y][x]
    if valid:
        nums.append(int(ans))

for c in numberCoordinates: 
    checkCoordinate(c)

print(sum(nums))
