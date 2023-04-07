using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrenzyState : State
{
    public FrenzyState() : base("Frenzy") { }

    public override void EnterState(FSMAgent agent)
    {
        agent.SetSpeedModifierDouble();
        agent.SetTimer(10f);
    }

    public override void ExitState(FSMAgent agent)
    {
        agent.SetSpeedModifierNormal();
    }

    public override State Update(FSMAgent agent)
    {
        //Handle Following Pacman
        Vector3 pacmanLocation = PacmanInfo.Instance.transform.position;

        if (agent.CloseEnough(pacmanLocation))
        {
            ScoreHandler.Instance.KillPacman();
        }
        
        if (agent.TimerComplete())
        {
            return new ScatterState(pacmanLocation, this);
        }

        //If Pacman ate a power pellet, go to Frightened State
        if (PelletHandler.Instance.JustEatenPowerPellet)
        {
            return new FrightenedState(this);
        }

        //If we didn't return follow Pacman
        agent.SetTarget(pacmanLocation);

        //Stay in this state
        return this;
    }
}
