import sys
import copy
from queue import PriorityQueue
import time

class State:
    """
    Class model to represent a state.
    """
    def __init__(self,stack1,stack2,stack3):
        self.stack1 = stack1
        self.stack2 = stack2
        self.stack3 = stack3
        self.parent = None
        self.heuristic = None

    def allstack(self):
        return [self.stack1,self.stack2,self.stack3]

    def Print(self):
        print(self.stack1)
        print(self.stack2)
        print(self.stack3)

    def __eq__(self, other):
        if not isinstance(other, State):
            return NotImplemented
        return self.stack1 == other.stack1 and self.stack2 == other.stack2 and self.stack3 == other.stack3

    def __lt__(self, other):
        return None

def MoveGen(state):
    neighbours=[]
    if state.stack1:
        new_state = copy.deepcopy(state) # create a copy of state
        temp = new_state.stack1.pop()    #remove top element
        new_state.stack2.append(temp)    #add in other stack to get a new state
        neighbours.append(new_state)    # add this new state in neighbour
        new_state = copy.deepcopy(state)# create a copy of state
        temp = new_state.stack1.pop()#remove top element
        new_state.stack3.append(temp)#add in other stack to get a new state
        neighbours.append(new_state)# add this new state in neighbour
    if state.stack2:
        new_state = copy.deepcopy(state)# create a copy of state
        temp = new_state.stack2.pop()#remove top element
        new_state.stack1.append(temp)#add in other stack to get a new state
        neighbours.append(new_state)# add this new state in neighbour
        new_state = copy.deepcopy(state)# create a copy of state
        temp = new_state.stack2.pop()#remove top element
        new_state.stack3.append(temp)#add in other stack to get a new state
        neighbours.append(new_state)# add this new state in neighbour
    if state.stack3:
        new_state = copy.deepcopy(state)# create a copy of state
        temp = new_state.stack3.pop()#remove top element
        new_state.stack1.append(temp)#add in other stack to get a new state
        neighbours.append(new_state)# add this new state in neighbour
        new_state = copy.deepcopy(state)# create a copy of state
        temp = new_state.stack3.pop()#remove top element
        new_state.stack2.append(temp)#add in other stack to get a new state
        neighbours.append(new_state)# add this new state in neighbour
    return neighbours

def GoalTest(state,goal_state):
    """
    compare state with goal state check if their stacks are equal.
    """
    if state.stack1 != goal_state.stack1:
        return False
    if state.stack2 != goal_state.stack2:
        return False
    if state.stack3 != goal_state.stack3:
        return False
    return True

def heuristic1(state,goal_state):
    h = 0 #initialize heuristic
    for stack, goal_stack in zip(state.allstack(),goal_state.allstack()):#parallel loop through state and goal state stacks of block
        for block in stack: # loop through inside a stack
            index_in_goal = None
            try:
                index_in_goal = goal_stack.index(block) # find index of block in goal stack
                index = stack.index(block) # find index of block in current stack
                if index == 0 and index_in_goal==0: #boundary case if they are on table
                    h+=1
                elif index-1>=0 and stack[index-1] == goal_stack[index_in_goal-1]: #if theu are correctly on top of block
                    h+=1
                else:
                    h-=1
            except: # if a goal stack does not have that block
                h-=1
    return h

def heuristic2(state,goal_state):
    h = 0 #initialize heuristic
    for stack, goal_stack in zip(state.allstack(),goal_state.allstack()):#parallel loop through state and goal state stacks of block
        index = 0
        flag = False
        for block in stack:
            try:# if a goal stack have  block
                g = goal_stack[index]
            except:# if a goal stack does not have block
                g = None
            if flag == True:#if structure below is incorrect
                h-=1*(index+1)
            elif block == g and flag!=True:#if on correct structure
                h+=1*(index+1)
            else: #if on incorrect structure
                h-=1*(index+1)
                flag = True
            index+=1
    return h

def heuristic3(state,goal_state):
    h = 0  #initialize heuristic
    for stack, goal_stack in zip(state.allstack(),goal_state.allstack()):#parallel loop through state and goal state stacks of block
        index = 0
        flag = False
        for block in stack:
            try:# if a goal stack have  block
                g = goal_stack[index]
            except:# if a goal stack does not have block
                g = None
            if flag == True:#if structure below is incorrect
                h-=1*(len(stack)-index)
            elif block == g and flag!=True:#if on correct structure
                h+=1*(len(stack)-index)
            else:#if on incorrect structure
                h-=1*(len(stack)-index)
                flag = True
            index+=1
    return h

def notVisited(state,explored,open):
    for s in explored:# check in explored
        if s.stack1 == state.stack1 and s.stack2 == state.stack2 and s.stack3 == state.stack3:
            return False
    for (h,s) in open:# check in open
        if s.stack1 == state.stack1 and s.stack2 == state.stack2 and s.stack3 == state.stack3:
            return False
    return True # return true if not visited

def getPath(path,state):
    path.append(state)
    if state.parent == None:#base case
        return
    else:
        getPath(path,state.parent)# recursively find path

def bfs(start_state,goal_state):#best first search
    open = PriorityQueue()
    explored=[] #visidted states
    h = heuristic3(goal_state,goal_state)-heuristic3(start_state,goal_state) # calculate heuristics
    open.put((h,start_state))
    while not open.empty():
        h,state = open.get() # get head element from priority queue
        explored.append(state)
        if GoalTest(state,goal_state):# check for goal state
            path=[]
            getPath(path,state)
            out.write("No. of states in path: "+str(len(path))+"\n")
            out.write("No. of explored states: "+str(len(explored))+"\n")
            for i in reversed(path):
                for s in i.allstack():
                    out.write(str(s)+"\n")
                out.write("\n")
            return True
        for neighbour in MoveGen(state):# find neighbours
            if notVisited(neighbour,explored,open.queue):
                h = heuristic3(goal_state,goal_state)-heuristic3(neighbour,goal_state)
                neighbour.parent = state # set parent
                open.put((h,neighbour))
    return False

def hillclimbing(start_state,goal_state):#hillclimbing search
    next_state=[]
    h = heuristic3(goal_state,goal_state)-heuristic3(start_state,goal_state)# calculate heuristics
    start_state.heuristic = h
    next_state.append(start_state)
    local_maxima = False
    while not local_maxima:
        state = next_state[-1]
        if GoalTest(state,goal_state):# check for goal state
            path=[]
            getPath(path,state)
            out.write("No. of state in path: "+str(len(path))+"\n")
            out.write("No. of explored state: "+str(len(next_state))+"\n")
            for i in reversed(path):
                for s in i.allstack():
                    out.write(str(s)+"\n")
                out.write("\n")
            return True
        min = state
        for neighbour in MoveGen(state):# find neighbours
            h = heuristic3(goal_state,goal_state)-heuristic3(neighbour,goal_state)
            neighbour.parent = state
            neighbour.heuristic = h
            if neighbour.heuristic < min.heuristic:
                min = neighbour
        next_state.append(min) # set minimum heuristic valued state
        if min == state:
            local_maxima = True
    path=[]
    getPath(path,state) # get path trravelled if stuck on local maxima
    out.write("No. of state in path: "+str(len(path))+"\n")
    out.write("No. of explored state: "+str(len(next_state))+"\n")
    for i in reversed(path):
        for s in i.allstack():
            out.write(str(s)+"\n")
        out.write("\n")
    out.write("stuck in local maxima")
    return False

#read input
file = open(sys.argv[1], "r")
algo_code = file.readline().strip()
stack1 = list(file.readline().strip().split())
stack2 = list(file.readline().strip().split())
stack3 = list(file.readline().strip().split())
start_state = State(stack1,stack2,stack3)
stack1 = list(file.readline().strip().split())
stack2 = list(file.readline().strip().split())
stack3 = list(file.readline().strip().split())
goal_state = State(stack1,stack2,stack3)
out = open("output.txt", "w")

if algo_code=='1':
    start_time = time.time()
    bfs(start_state,goal_state)
    print("Time taken(in sec):",time.time() - start_time)
elif algo_code=='2':
    start_time = time.time()
    hillclimbing(start_state,goal_state)
    print("Time taken(in sec):",time.time() - start_time)
