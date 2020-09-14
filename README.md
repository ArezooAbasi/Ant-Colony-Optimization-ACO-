# Ant-Colony-Optimization-ACO-

The Ant Colony Algorithm is a group of algorithms used to find the optimal path in a graph. Ants use pheromones to communicate. They pour some pheromone in each path and with its help, they can make the best decision and find the best path.

maxcit in my program refers to the maximum number of cities, which are 17 cities.

maxdist shows the maximum distance between cities in pairs, with a maximum of 100.

mtour is the worst turn signal for maxcit * maxdist.

mants Specifies the number of ants, to which any number can be assigned, here the number of ants is 10.

The values of alpha, beta, and pherin represent the amount of pheromone available, which is used to calculate the pheromones of the path and the pheromones of each ant.

rass is the amount of pheromone that evaporates from the path.

qval is also a constant value used to calculate the probability of ants choosing a path based on pheromones.

In this problem, the connection of cities, the distance between cities and the position of each ant is randomly determined, and each time, the algorithm is executed at maxtime and the best case is obtained.

In this case the maxtime value; 000,10.

If the number of ants is equal to the number of cities, an ant will be placed on each city and will start its journey from that city.

In the simuant function, we implement the ant colony for the traveling vendor problem.

In the snextcit function, select the next edge that the ant should select so that the path previously taken by the ant is not re-selected and the new selection path is based on the amount of pheromones and the probability of selecting the path is based on the amount of pheromones.

In the upmasir function, the amount of path pheromones is updated.

Better pathways take more pheromones, and pheromone evaporation is treated in the same way.
And finally, the best path that the ants have found is printed.
