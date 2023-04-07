using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using UnityEngine;

public class ClydeState : State
{
    public ClydeState() : base("Clyde") { }

    public override void EnterState(FSMAgent agent)
    {
        agent.SetTimer(20f);
    }

    public override void ExitState(FSMAgent agent)
    { }

    public override State Update(FSMAgent agent)
    {
        //Handle Following Pacman
        Vector3 pacmanLocation = PacmanInfo.Instance.transform.position;
        float distanceToPacman = Mathf.Sqrt(Mathf.Pow((agent.GetPosition().x - pacmanLocation.x),2) + Mathf.Pow((agent.GetPosition().y - pacmanLocation.y),2));
        Vector3 scatterLocation = new Vector3(-1*ObstacleHandler.Instance.XBound, -1*ObstacleHandler.Instance.YBound);
        
        if (agent.CloseEnough(pacmanLocation))
        {
            ScoreHandler.Instance.KillPacman();
        }

        //If timer complete, go to Scatter State
        if (agent.TimerComplete())
        {
            return new ScatterState(scatterLocation, this);
        }

        //If within 8 grid blocks of Pacman, go to scatter location
        if (distanceToPacman <= 1.6f)
        {
            agent.SetTarget(scatterLocation);
        }
        else
        {
            agent.SetTarget(pacmanLocation);
        }

        //If Pacman ate a power pellet, go to Frightened State
        if (PelletHandler.Instance.JustEatenPowerPellet)
        {
            return new FrightenedState(this);
        }
        
        //Stay in this state
        return this;
    }
}
