# Traveling Salesman
#

# -----------------------------------
# Traveling Salesman: 
# Problem: We have a graph G(V,E) with Vertices (representing cities)
# and Edges (representing the travel cost between cities).
# We must find the minimum itinerary to visit every city and
# return to original city S.
#
# Dumb Solution: Greedy Solution: At every city, choose the route that is
# the least expensive to an untraveled city.

def_traveling_salesman_greedy(graph):
    # total cost counter
    cost = 0
    vertices = graph[0]
    edges = graph[1]
    # H: priority heap of V
    # H := {s : 0}
    H.insert(s)
    
    # Loop through each edge
    while H.empty is not False:
        v = H.deletemin()
        for each_edge in Graph(edges):
            if dist[w] > dist[v]+ length(v,w):
                dist[w] := dist[v] + length(v,w), prev[w] := v, H.insert(w,dist[w])
