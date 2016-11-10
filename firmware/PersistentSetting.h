#pragma once

#include <stdint.h>
#include <EEPROM.h>

template <class T>
class PersistentSetting {
public:
    PersistentSetting(uint16_t eepromOffset, uint8_t disp, T min, T max, T def) : 
        _eepromOffset(eepromOffset),
        _disp(disp),
        _min(min),
        _max(max),
        _def(def)
    {
        this->load();
    }

    // Load value from EEPROM - return the loaded value
    T load() {
        uint8_t* ptr = (uint8_t*)(&_value);
        for (uint8_t i=0; i<sizeof(T); i++) {
            ptr[i] = EEPROM.read(i);
        }
        if (_value < _min || _value > _max) {
            _value = _def;
        }
        return _value;
    }

    // save the setting to EEPROM - only updates EEPROM if value
    // in member differs from value in EEPROM (courtesy of the 
    // EEPROM.update() function).
    void save()
    {
        uint8_t* ptr = (uint8_t*)(&_value);
        for (uint8_t i=0; i<sizeof(T); i++) {
            EEPROM.update(_eepromOffset+i, ptr[i]);
        }
    }

    uint8_t disp() { return _disp; }

    T get() { return _value; }
    bool set(T v) { if (v >= _min && v<=_max) { _value = v; return true; } else { return false; } }

    // over-ride this in your child classes to get a representation
    // as a uint8_t
    virtual uint8_t getUi8Repr() { return (uint8_t)get(); }
    // over-ride this in your child classes to set from a representation
    // as a uint8_t
    virtual bool setUi8Repr(uint8_t v) { return set((T)v); }

    size_t size() { return sizeof(T); }

private:
    uint16_t _eepromOffset;

protected:
    T _value;
    uint8_t _disp;
    T _min;
    T _max;
    T _def;
};

class ScaledIntSetting : public PersistentSetting<int> {
public:
    ScaledIntSetting(uint16_t eepromOffset, uint8_t disp, int min, int max, int def, int scale) :
        PersistentSetting<int>(eepromOffset, disp, min, max, def),
        _scale(scale) {;}
    uint8_t getUi8Repr() { return _value/_scale; }
    bool setUi8Repr(uint8_t v) { return set(v*_scale); }

private:
    int _scale;
};

