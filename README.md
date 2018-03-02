# Hash-Code-2018
A solution for the 2018 Hash Code problem

# Approach:
Rides get sorted (once) based on their earliest time. For each one of them, we try to find the nearest car that will give the best score (i.e. be there on time to get the ride).

# Additional Notes:
Our initial approach was to loop through cars (not through rides) and for each car, we would try to find the nearest ride that it could take (using Breadth-First-Search, since we modeled the grid as a graph of the intersections in the map, and each node/intersection had a specific number of rides that start from there).
That didn't give satisfying results as it didn't account for the bonus as much as the current approach.

We also tried to direct the sorting of cars (in the initial approach) or rides (in the current approach) based on where most of them were in the map (You could think that as finding the center of mass in a plane if every car/ride on this plane accounted for the same mass). That didn't give us satisfying solutions either.

# Hash Code Team:
GeorgeLs            -     George Liontos

arisKoutsou         -     Aris Koutsouridis

souperk             -     Kostas Alexopoulos

stefanos-baziotis   -     Stefanos Baziotis
