﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleTest4Points : ObstacleDefiner
{

	
	public override Vector2[][] GetObstaclePoints()
	{
		Vector2[] obstacles1 = new Vector2[] { new Vector2(2f, 1.5f), new Vector2(2f, 0.5f), new Vector2(1f, 0.5f), new Vector2(1f, 1.5f)};
        Vector2[] obstacles2 = new Vector2[] { new Vector2(2f, -1.5f), new Vector2(2f, -0.6f), new Vector2(1f, -0.6f), new Vector2(1f, -1.5f) };
        Vector2[] obstacles3 = new Vector2[] { new Vector2(-2f, -1.5f), new Vector2(-2f, -0.6f), new Vector2(-1f, -0.6f), new Vector2(-1f, -1.5f) };
        Vector2[] obstacles4 = new Vector2[] { new Vector2(-2f, 1.5f), new Vector2(-2f, 0.5f), new Vector2(-1f, 0.5f), new Vector2(-1f, 1.5f) };
        Vector2[] obstacles5 = new Vector2[] { new Vector2(0.5f, -0.65f), new Vector2(-0.65f, -0.65f), new Vector2(-0.65f, -0.25f), new Vector2(0.5f, -0.25f) };
        Vector2[] obstacles6 = new Vector2[] { new Vector2(0.5f, 0.65f), new Vector2(-0.65f, 0.65f), new Vector2(-0.65f, 0.25f), new Vector2(0.5f, 0.25f) };

        Vector2[][] arrayOfObstaclePoints = new Vector2[][] { obstacles1, obstacles2, obstacles3, obstacles4, obstacles5, obstacles6 };

		xBound = 2;
		yBound = 1;

		return arrayOfObstaclePoints;
	}
}
