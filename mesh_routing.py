# IM
#
# Solution to mesh network routing. 
#


import sys
network_table = { "INTERNET": [] }
unique_nodes  = []


#Breadth-First-Search Algorithm, with Backtracking for stdout output 
def bfs( src,  target  ):
    
    #shortest path , store for later output to FD_1 (stdout) 
    path = []     
    prev = {} 
    visited =  {} 
   
    for node in unique_nodes:
        prev.setdefault( node, '-1')
        visited.setdefault(node, False)
     
    #Using a list to mirror a queue 
    #enqueue = append, dequeue = pop(0)
    queue = []
    visited[src] = True
  
    queue.append(src)

    while  queue:
        node = queue.pop(0)
        #check if target node (dest node) in adj_list(src) 
        if target in network_table[node]:
            prev[target] = node
            queue = []
        else:
            for neighbor in network_table[node]:
                #print( "neighbor value: " + str(visited[neighbor]) )
                if visited[neighbor] == False:
                    #print("visiting "+ neighbor) 
                    visited[neighbor] = True 
                    prev[neighbor] = node
                    queue.append(neighbor) 
  
    #Backtracking 
    n = target
    while n != src and n != '-1':
         
        n = prev[n]
        if( n != '-1'):
            path.append(n) 

    #Cleaning path for output
    if( src in path):
        path.remove(src) 
        path.sort()
        path.append(src)

    #If path exist for <src, target>, path list will be non-empty
    if( path):
        sys.stdout.write(target)
        sys.stdout.flush() 
        for node in path:
            sys.stdout.write(","+node)
          
        sys.stdout.write("\n")
        sys.stdout.flush() 


def generate_paths():

    #Alphabetical sort
    unique_nodes.sort()
 
    #INTERNET node not found in input. Pointless continuing for problem 
    if "INTERNET" not in unique_nodes:
        return 
    
    for node in network_table:
        if node != "INTERNET":
            #bfs( source, destination) 
            bfs(node, "INTERNET") 


def main():
  
    l = []
    line = sys.stdin  
    for line in sys.stdin:
        if( line == "\n"):
            break
   
        #tokenize line for readability
        l = line.split(",")
        node = l[0]
        neighbor = l[1].strip("\n")
        
        if node not in  unique_nodes:
            unique_nodes.append( node )

        if neighbor not in  unique_nodes:
            unique_nodes.append( neighbor )
   
        if( node not in network_table):
            network_table.setdefault(node, [])
 
        
        #hook into network table
        network_table[node].append(neighbor)  

   
    #Removing unnecessary data from network_table and unique_nodes list
    if( "Node Name" in network_table):
        network_table.pop("Node Name", None) 
    
    if( 'Node Name' in unique_nodes):
        unique_nodes.remove('Node Name') 
    if( 'Peer Name' in unique_nodes):
        unique_nodes.remove('Peer Name') 
    
    #now we have the table, call generate_paths
    generate_paths()


if __name__ == "__main__":
    main()   
