#ifndef PHSensor_H
#define PHSensor_H

#include <stdint.h>

class PHSensor
{
    unsigned m_pin;
    unsigned m_nSamples;
public:
    class PHLevel
    {
        uint8_t m_lvl : 4;
    public:
        uint8_t SetLevel(int8_t lvl)
        {
            m_lvl = (lvl < 0 ? 0 : (lvl > 14 ? 14 : lvl));
            return m_lvl;
        }
        uint8_t GetLevel() 
        {
            return m_lvl;
        }
    };
private: 
    PHLevel m_ph;
public:
    PHSensor(unsigned pin, unsigned nSamples = 10) : m_pin { pin }, m_nSamples{ nSamples } {}
    uint8_t Read()
    {
        int max = -1, min = 1030;

        for(int i = 0; i < m_nSamples; ++i) 
        { 
            int sample = analogRead(m_pin);
            max = ( max < sample ? sample : max );
            min = ( min > sample ? sample : min );
            delay(10);
        }

        double avgValue = (max + min) / 2;
        double pHVol = avgValue*5.0/1024/6;
        m_ph.SetLevel(-5.70 * pHVol + 21.34);
        
        return m_ph.GetLevel();
    }
};

#endif