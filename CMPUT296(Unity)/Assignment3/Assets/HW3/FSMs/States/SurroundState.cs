using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SurroundState : State
{
    private State returnState;
    //Private reference to the pinky ghost, if present
    private Pinky pinky;
    private int Score;

    public SurroundState(int _score, State _returnState) : base("Surround")
    {
        Score = _score;
        returnState = _returnState;
    }

    public override void EnterState(FSMAgent agent)
    {
        agent.SetSpeedModifierDouble();
        pinky = GameObject.FindObjectOfType<Pinky>();
    }

    public override void ExitState(FSMAgent agent)
    {
        agent.SetSpeedModifierNormal();
    }

    public override State Update(FSMAgent agent)
    {
        //Handle Following Pacman
        Vector3 pacmanLocation = PacmanInfo.Instance.transform.position;
        Vector3 ambushLocation = pacmanLocation - (0.4f * PacmanInfo.Instance.Facing);

        if (agent.CloseEnough(pacmanLocation))
        {
            ScoreHandler.Instance.KillPacman();
        }

        //If Pacman ate a power pellet, go to Frightened State
        if (PelletHandler.Instance.JustEatenPowerPellet)
        {
            return new FrightenedState(this);
        }

        //work with pinky to surround pacman if pinky is present
        if (pinky != null)
        {
            Vector3 pinkyToPacman = pacmanLocation - pinky.GetPosition();
            ambushLocation = pacmanLocation + 0.5f * pinkyToPacman;
        }

        //if pacman crossed the score threshhold, exit state
        if (Score >= 40)
        {
            return returnState;
        }
        
        //If we didn't return follow Pacman
        agent.SetTarget(ambushLocation);

        //Stay in this state
        return this;
    }
}
