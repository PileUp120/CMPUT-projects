using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System.Collections.Specialized;

//Assignment 1 Script
public class GridHandler : NodeHandler
{
    private float gridSize;

    //Holds all of the nodes
    private Dictionary<string, GraphNode> nodeDictionary;
    public override void CreateNodes()
    {
        nodeDictionary = new Dictionary<string, GraphNode>();

        //ASSIGNMENT 1 EDIT BELOW THIS LINE

        gridSize = ObstacleHandler.Instance.GridSize;

        for (float x = ObstacleHandler.Instance.XBound * -1; x <= ObstacleHandler.Instance.XBound + gridSize; x += gridSize)
        {
            for (float y = ObstacleHandler.Instance.YBound * -1; y <= ObstacleHandler.Instance.YBound + gridSize; y += gridSize)
            { 
                Vector3 loc = new Vector3(x, y);
                Debug.Log(loc);
                Vector2 cellCenter = new Vector2(x, y);
                Vector2 ULeft = new Vector2((x - 0.5f * gridSize), (y - 0.5f * gridSize));
                Vector2 BLeft = new Vector2((x - 0.5f * gridSize), (y + 0.5f * gridSize));
                Vector2 URight = new Vector2((x + 0.5f * gridSize), (y - 0.5f * gridSize));
                Vector2 BRight = new Vector2((x + 0.5f * gridSize), (y + 0.5f * gridSize));
                bool LDiagIntersect = ObstacleHandler.Instance.AnyIntersect(BLeft, URight);
                bool RDiagIntersect = ObstacleHandler.Instance.AnyIntersect(ULeft, BRight);
                if (!ObstacleHandler.Instance.PointInObstacles(cellCenter))
                {
                    if (!LDiagIntersect)
                        {
                            if(!RDiagIntersect)
                                {
                                    nodeDictionary.Add(loc.ToString(), new GraphNode(loc));
                                }
                            
                        }
                }

            }
        }
        
        
        //ASSIGNMENT 1 EDIT ABOVE THIS LINE

        //Create Neighbors
        foreach (KeyValuePair<string, GraphNode> kvp in nodeDictionary)
        {
            //Left
            if (nodeDictionary.ContainsKey((kvp.Value.Location + (Vector3.left * gridSize)).ToString()))
            {
                kvp.Value.AddNeighbor(nodeDictionary[(kvp.Value.Location + (Vector3.left * gridSize)).ToString()]);
            }
            //Right
            if (nodeDictionary.ContainsKey((kvp.Value.Location + (Vector3.right * gridSize)).ToString()))
            {
                kvp.Value.AddNeighbor(nodeDictionary[(kvp.Value.Location + (Vector3.right * gridSize)).ToString()]);
            }
            //Up
            if (nodeDictionary.ContainsKey((kvp.Value.Location + (Vector3.up * gridSize)).ToString()))
            {
                kvp.Value.AddNeighbor(nodeDictionary[(kvp.Value.Location + (Vector3.up * gridSize)).ToString()]);
            }
            //Down
            if (nodeDictionary.ContainsKey((kvp.Value.Location + (Vector3.down * gridSize)).ToString()))
            {
                kvp.Value.AddNeighbor(nodeDictionary[(kvp.Value.Location + (Vector3.down * gridSize)).ToString()]);
            }
        }
    }

    public override void VisualizeNodes()
    {
        //Visualize grid points
        foreach (KeyValuePair<string, GraphNode> kvp in nodeDictionary)
        {
            //Draw left line
            Debug.DrawLine(kvp.Value.Location + Vector3.left * gridSize / 2f + Vector3.up * gridSize / 2f, kvp.Value.Location + Vector3.left * gridSize / 2f + Vector3.down * gridSize / 2f, Color.white);
            //Draw right line
            Debug.DrawLine(kvp.Value.Location + Vector3.right * gridSize / 2f + Vector3.up * gridSize / 2f, kvp.Value.Location + Vector3.right * gridSize / 2f + Vector3.down * gridSize / 2f, Color.white);
            //Draw top line
            Debug.DrawLine(kvp.Value.Location + Vector3.up * gridSize / 2f + Vector3.left * gridSize / 2f, kvp.Value.Location + Vector3.up * gridSize / 2f + Vector3.right * gridSize / 2f, Color.white);
            //Draw bottom line
            Debug.DrawLine(kvp.Value.Location + Vector3.down * gridSize / 2f + Vector3.left * gridSize / 2f, kvp.Value.Location + Vector3.down * gridSize / 2f + Vector3.right * gridSize / 2f, Color.white);
        }
    }

    //Find closest node (used for pathing)
    public override GraphNode ClosestNode(Vector3 position)
    {
        float minDist = 1000;
        GraphNode closest = null;
        foreach (KeyValuePair<string, GraphNode> kvp in nodeDictionary)
        {
            float dist = (kvp.Value.Location - position).sqrMagnitude;
            if (dist < minDist)
            {
                minDist = dist;
                closest = kvp.Value;
            }
        }
        return closest;
    }
}
