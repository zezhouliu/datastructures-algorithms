def traveling_salesman_dynamic (graph):



    
   
def all_pairs_shortest_path(graph):
    # shortest path from i->j has to go through intermediate nodes
    # are restricted from 1 to k
    D = []
    num_vertices = len(graph)
    for x in range(num_vertices):        
        D.append([])
        
    if k == 0:
        D[0][i][j] = dij if graph[i][j] else 99999999      
        
    for k = 1 to n:
        for i = 1 to n:
            for j = 1 to n:   
       
                # possibly D[k][i][j] = D[k-1][i][j] if I don't need to use vertex k
                # possibly D[k][i][j] = D[k-1][i][k] + D[k-1][k][j] if k is on the path
                D[k][i][j] = min (D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j])
