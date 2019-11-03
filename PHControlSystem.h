#ifndef PHControlSystem_H
#define PHControlSystem_H

#include "PHSensor.h"
#include "StepMotor.h"

class PHControlSystem
{
    PHSensor m_phs;
    StepMotor m_r, m_l, m_mid; 
    PHSensor::PHLevel m_wishedLvl;
public:
    PHControlSystem(PHSensor ph, unsigned wishedLvl, StepMotor r, StepMotor l, StepMotor mid)
        : m_phs { ph }, m_r { r }, m_l { l }, m_mid{ mid }
    {
        m_wishedLvl.SetLevel(wishedLvl);
    }
    
    void Run()
    {
        m_r.Init();
        m_l.Init();
        m_mid.Init();
    }

    void Refresh()
    {
        uint8_t read = m_phs.Read();
        m_mid.Step(1.0);
        if(read > m_wishedLvl.GetLevel())
        {
            m_l.Stop();
            m_r.Continue();
        }
        else if(read < m_wishedLvl.GetLevel())
        {
            m_r.Stop();
            m_l.Continue();
        }
        else 
        {
            m_r.Stop();
            m_l.Stop();
        }
    }
};

#endif