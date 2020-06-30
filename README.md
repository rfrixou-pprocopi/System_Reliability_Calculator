# System_Reliability_Calculator
A reliability calculator (in terms of the system's MeanTimeToFailure (MTTF)) of a multi-component system model.

For the purposes of this project we have chosen to model the component system as a directional graph. The first node of the graph represents the system input and the last node the system output. Each transition between the nodes of the graph generated is analogous to a wire extending from one corresponding component to the other. All graphs are generated based on two parameters. Density and Nodes. Density corresponds to the probability of an edge being generated between two nodes. Nodes corresponds to the number of components present in the simulated system (graph). 

Our simulation run with the following parameter ranges:
  •	Density: 0.1 – 0.9 with a step-up of 0.1
  •	Nodes: 6 – 20 with a step-up of 2

We have modelled three different kinds of graphs in order to achieve a broader collection of data. The rules for generating the corresponding graphs are as follows:
1.	The Graph is generated randomly and has no additional checks implemented.
2.	The Graph is generated with the following rules in mind:
  a.	The Edges generated can only be generated from a smaller indexed node to a larger one (Nn -> Nm where n > m). E.g. N3 -> N5.
3.	The Graph is generated with the following rules in mind:
  a.	The Edges generated can only be generated from a smaller indexed node to a larger one (Nn -> Nm where n > m). E.g. N3 -> N5.
  b.	Each Node (excluding the Input and Output nodes, which respectively have only paths being led from and leading to them) must at least be led to and lead to another Node, which in conjunction with the first rule can guarantee that no dead ends exist in our Graph.

In order to calculate the Reliability of our generated component system we employ exhaustive search. We calculate all combinations of components working/not working and create a polynomial reliability which we transform to produce the MTTF of our system. The data presented, at the end of this report, has been averaged over n iterations of the algorithm.

In order to approximate the Reliability of our component system we make the following assumptions. Our approximation considers only the components present in each path from the Input to the Output Node. By employing an algorithm based on BFS (Breadth First Search) of our Graph we calculate all paths from Input to Output. To calculate the Rall we employ the same process we used in the exhaustive search implementation and transform it to produce the system’s MTTF.
