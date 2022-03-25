import sys
def getPath(dict, target):
    """
    Construct path from node pair consist of node and its parent.
    """
    sol = []
    curr = target # de
    count = 0
    while curr != None:# loop intil parent if node is nill i.e, it is source state
        sol.append(curr)
        if(curr != "None"):
            maze[int(curr[0])][int(curr[1])]="0" # represent path with 0
            count+=1
        curr = dict.get(curr) # get parent of current node
    return count

def MoveGen(neighbours,node):
    """
    Take input node and return all the possible neighbouring states in the order of DOWN > UP > RIGHT > LEFT.
    """
    if(node[0] < len(maze)-1): # check if node is inside along horizontally
        temp = maze[node[0]+1][node[1]]
        if( temp != "+" and temp != "-" and temp != "|" and temp != "0"): # check if its valid state
            neighbours.append((node[0]+1,node[1])) #Down

    if(node[0] > 0):# check if node is inside along vertically
        temp = maze[node[0]-1][node[1]]
        if( temp != "+" and temp != "-" and temp != "|" and temp != "0"):# check if its valid state
            neighbours.append((node[0]-1,node[1])) #Up

    if(node[1] < len(maze[0])-1):# check if node is inside along horizontally
        temp = maze[node[0]][node[1]+1]
        if( temp != "+" and temp != "-" and temp != "|" and temp != "0"):# check if its valid state
            neighbours.append((node[0],node[1]+1)) #Right

    if(node[1] > 0): # check if node is inside along vertically
        temp = maze[node[0]][node[1]-1]
        if( temp != "+" and temp != "-" and temp != "|" and temp != "0"):# check if its valid state
            neighbours.append((node[0],node[1]-1)) #Left

    return neighbours

def GoalTest(node):
    """
    Check whether node is Goal state or not.
    """
    if(maze[node[0]][node[1]]=='*'):
        return True

def bfs(node):
    """
    Run BFS Algorithm on State space search
    """
    queue = [] # queue for to be explored state
    visited = []# list for all the visited node
    queue.append(node)
    visited.append(node)
    parent = {node:'None'} # dictionary for creating parent child pair
    while queue: # loop untill all the state are explored
        s = queue.pop(0) # removing explored state
        node = s
        if node not in visited: # not visited node
            visited.append(node)
        if(GoalTest(node)):# check for goal state
            count = getPath(parent,node)
            print(len(visited))# print number of visited state
            out.write(str(len(visited))+"\n")
            print(count)# print length of path
            out.write(str(count)+"\n")
            break
        neighbours = []
        neighbours = MoveGen(neighbours,node)# get neighbours of current state
        for neighbour in neighbours:
            if neighbour not in list(parent.keys()):
                parent[neighbour] = node # set parent
                queue.append(neighbour) # append in queue for to be explored



def dfs(node):
    """
    Run DFS Algorithm on State space search
    """
    c=0 # counter for state visited
    visited = [node] # storing visited node
    stack = [node] # stack for node to be explored
    parent = {node:'None'} # dictionary for creating parent child pair
    while stack: # loop untill all the state are explored
        node = stack[-1]
        stack.pop() # removing explored state
        c+=1
        if(GoalTest(node)): # check for goal state
            count = getPath(parent,node) # Construct path
            print(c)# print number of visited state
            print(count) # print length of path
            out.write(str(c)+"\n")
            out.write(str(count)+"\n")
            break
        neighbours = []
        neighbours = reversed(MoveGen(neighbours,node)) # get neighbours of current state
        for neighbour in neighbours:
            if neighbour not in visited: # not visited node
                if neighbour not in list(parent.keys()):
                    parent[neighbour] = node
                stack.append(neighbour)
                visited.append(neighbour)

def bounded_dfs(node,depth):
    """
    Run DFS upto maximun depth allowed.
    """
    global success
    global count
    count += 1 # count for explored state
    global parent
    if GoalTest(node):# check whether node is goal state or not
        success = True
        print(count) # print number of visited state
        c = getPath(parent,node) # constuct path
        print(c) # print length of path
        out.write(str(count)+"\n")
        out.write(str(c)+"\n")
        return
    if mazed[node[0]][node[1]][1]-1==depth: #  checking maximum depth allowed
        return
    neighbours = []
    neighbours = MoveGen(neighbours,node) # finding neighbours
    for neighbour in neighbours:
        if success:
            break
        if mazed[neighbour[0]][neighbour[1]][1] == -1: # not visited node
            if neighbour not in list(parent.keys()):# assigning parent
                parent[neighbour] = node
            temp = list(mazed[neighbour[0]][neighbour[1]]) #updating distance
            temp[1] = mazed[node[0]][node[1]][1] + 1
            mazed[neighbour[0]][neighbour[1]] = (temp[0],temp[1])
            bounded_dfs(neighbour,depth) #exploring child recursively
        elif mazed[neighbour[0]][neighbour[1]][1] > mazed[node[0]][node[1]][1] + 1: # checking for better path
            temp = list(mazed[neighbour[0]][neighbour[1]]) # updating parents
            temp[1] = mazed[node[0]][node[1]][1] + 1
            mazed[neighbour[0]][neighbour[1]] = (temp[0],temp[1])
            bounded_dfs(neighbour,depth) # exploring child recursively


def dfid(node):
    """
    DFID algorithm
    """
    global success
    global count
    depth = 0
    if GoalTest(node): #check if source is goal state
        count = 1
        mazed[node[0]][node[1]][1][1] = 1
        success = True
    while not success: #iteratively run bounded dfs algorithm
        depth += 1
        for i in range(0,len(mazed)): #reassign mazed before every iteration
            for j in range(0,len(mazed[0])):
                mazed[i][j] = (mazed[i][j][0],-1)
        temp = list(mazed[node[0]][node[1]])
        temp[1] = 1
        mazed[node[0]][node[1]] = (temp[0],temp[1])
        bounded_dfs(node,depth)

out = open("output.txt", "w")

file = open(sys.argv[1], "r")    # opening input file
input = file.read()
input = input.strip()
maze=[]
mazed=[]
Algo_Code = int(input[0])
input = input[2:].split("\n")
for i in input:
    maze.append(list(i))
    t = [(x,-1) for x in list(i)]
    mazed.append(t)

# initializing variable
count=0
success = False
pc_loc = (0,0) #source state
parent = {pc_loc:'None'}
if(Algo_Code == 0): # run bfs
    bfs(pc_loc)
elif(Algo_Code == 1):# run dfs
    dfs(pc_loc)
else: # run dfid
    dfid(pc_loc)
for i in range(0,len(maze)):#print final maze with path
    print("".join(maze[i]))
    out.write("".join(maze[i])+"\n")
