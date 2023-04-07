using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomGhostState : State
{
    public CustomGhostState() : base("CustomGhost") { }

    public override void EnterState(FSMAgent agent)
    {
        base.EnterState(agent);
    }

    public override void ExitState(FSMAgent agent)
    {
        base.ExitState(agent);
    }

    public override State Update(FSMAgent agent)
    {
        //Handle Following Pacman
        Vector3 pacmanLocation = PacmanInfo.Instance.transform.position;
        Vector3 ambushLocation = pacmanLocation + (0.6f * PacmanInfo.Instance.Facing);
        int CurrScore = ScoreHandler.Instance.Score;

        //If Pacman ate a power pellet, go to Frightened State
        if (PelletHandler.Instance.JustEatenPowerPellet)
        {
            return new FrightenedState(this);
        }

        if (agent.CloseEnough(pacmanLocation))
        {
            ScoreHandler.Instance.KillPacman();
        }

        if (CurrScore >= 27 && CurrScore <= 37)
        {
            return new SurroundState(CurrScore, this);
        }

        if (CurrScore >= 38)
        {
            return new FrenzyState();
        }

        //If we didn't return follow Pacman
        agent.SetTarget(ambushLocation);

        //Stay in this state
        return this;
    }
}
