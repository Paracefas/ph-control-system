#ifndef StepMotor_H
#define StepMotor_H

#include <stdint.h>

class StepMotor
{
    enum Direction
    {
        Right,
        Left,
        NoDir
    } m_dir;

    using Velocity = double;
    Velocity m_vel;

    struct State
    {
        Direction dir = Right;
        Velocity  vel = 1.0;
    } m_state;

    State Stopped()
    {
        if(m_state.dir == NoDir) return m_state;
        m_vel = m_state.vel;
        m_dir = m_state.dir;
        m_state.vel = 0.0;
        m_state.dir = NoDir;
        return m_state;
    }
    uint8_t m_Steps;
    uint8_t m_Direction;
public:
    StepMotor(uint8_t steps, uint8_t dir)
        : m_Steps{ steps }, m_Direction{ dir } {}

    void Init(double vel = 0.5, uint8_t dir = 0)
    {
        pinMode(m_Steps, OUTPUT); 
        pinMode(m_Direction, OUTPUT); 
        m_state.dir = dir;
        m_state.vel = vel;
    }
    State ChangeDirection()
    {
        m_state.dir = (m_state.dir == Right ? Left : Right);
        m_state.vel *= (m_state.dir == Right ? 1 : -1);
        digitalWrite(m_Direction, (m_state.dir == Right ? 1023 : 0));        
        return m_state;
    }
    
    State Stop()
    {
        m_state = Stopped();
        return m_state;
    }

    State Step(double _delay)
    {
        digitalWrite(m_Steps, HIGH);
        delayMicroseconds(5);             
        digitalWrite(m_Steps, LOW); 
        _delay = map(_delay, 0.0, 1.0, 900.0, 2500.0);        
        delayMicroseconds(_delay); 
    }

    State Continue()
    {
        if(m_state.vel == 0.0)
        {
            m_state.dir = m_dir;
            m_state.vel = m_vel;
            Step(m_vel);
        }
        return m_state;
    }

    State ChangeVelocity(Velocity velocity)
    {
        m_state.vel = velocity;
        if(velocity < 0)  return ChangeDirection();
        if(velocity == 0) return Stop();
    }
};

#endif