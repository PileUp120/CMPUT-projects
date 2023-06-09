﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AStarPathFinder : GreedyPathFinder
{
    public static int nodesOpened = 0;

    //ASSIGNMENT 2: EDIT BELOW THIS LINE, IMPLEMENT A*
    public override Vector3[] CalculatePath(GraphNode startNode, GraphNode goalNode)
    {
        nodesOpened = 0;

        AStarNode start = new AStarNode(null, startNode, Heuristic(startNode, goalNode));
        float gScore = 0;

        List<GraphNode> closedset = new List<GraphNode>();
        PriorityQueue<AStarNode> openSet = new PriorityQueue<AStarNode>();
        openSet.Enqueue(start);
        Dictionary<string, float> gScores = new Dictionary<string, float>();

        int attempts = 0;
        while (openSet.Count() > 0 && attempts<10000)
        {
            attempts += 1;
            AStarNode currNode = openSet.Dequeue();

            //Did we find the goal?
            if (currNode.Location == goalNode.Location)
            {
                Debug.Log("CHECKED " + nodesOpened + " NODES");//Don't delete this line
                //Reconstruct the path?
                return ReconstructPath(start, currNode);
            }
            closedset.Add(currNode.GetGraphNode());
            //Check each neighbor
            foreach (GraphNode neighbor in currNode.GraphNode.Neighbors)
            {
                
                if (closedset.Contains(neighbor))
                {
                    continue;
                }

                gScore = currNode.GetGScore() + ObstacleHandler.Instance.GridSize;

                List<GraphNode> TempL = new List<GraphNode>();

                for (int i = 0; i < openSet.Count(); i++)
                {
                    GraphNode temp = openSet.Data[i].GetGraphNode();
                    TempL.Add(temp);
                }

                if (!TempL.Contains(neighbor))
                {
                    AStarNode aStarNeighbor = new AStarNode(currNode, neighbor, Heuristic(neighbor, goalNode));
                    openSet.Enqueue(aStarNeighbor);
                }

                List<GraphNode> ToRemove = new List<GraphNode>();

                else if (gScore < gScores[neighbor.Location.ToString()])
                {
                    foreach (AStarNode node in openSet.Data)
                    {
                        if (node.GetGraphNode() == neighbor)
                        {
                            ToRemove.Add(node);
                        }
                    }
                    foreach (GraphNode node in ToRemove)
                    {
                        if (openSet.contains(node))
                        {
                            openSet.Remove(node);
                        }
                    }
                    AStarNode aStarNeighbor = new AStarNode(currNode, neighbor, Heuristic(neighbor, goalNode));
                    openSet.Enqueue(aStarNeighbor); 
                }

                gScores[neighbor.Location.ToString()] = gScore;                    
                
            }
        }
        Debug.Log("CHECKED "+ nodesOpened + " NODES");//Don't delete this line
        return null;
    }
    //ASSIGNMENT 2: EDIT ABOVE THIS LINE, IMPLEMENT A*

    //EXTRA CREDIT ASSIGNMENT 2 EDIT BELOW THIS LINE
    public float Heuristic(GraphNode currNode, GraphNode goalNode)
    {
        return (Mathf.Abs(currNode.Location.x - goalNode.Location.x) + Mathf.Abs(currNode.Location.y - goalNode.Location.y));
    }
    //EXTRA CREDIT ASSIGNMENT 2 EDIT ABOVE THIS LINE

    //Code for reconstructing the path, don't edit this.
    private Vector3[] ReconstructPath(AStarNode startNode, AStarNode currNode)
    {
        List<Vector3> backwardsPath = new List<Vector3>();

        while (currNode != startNode)
        {
            backwardsPath.Add(currNode.Location);
            currNode = currNode.Parent;
        }
        backwardsPath.Reverse();

        return backwardsPath.ToArray();
    }
}



