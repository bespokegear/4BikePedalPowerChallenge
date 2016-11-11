#pragma once

#ifdef DEBUG
#include <Arduino.h>
#endif
#include <stdint.h>
#include <EEPROM.h>

template <class T>
class PersistentSetting {
public:
    PersistentSetting(uint16_t eepromOffset, T min, T max, T def) : 
        _eepromOffset(eepromOffset),
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
            ptr[i] = EEPROM.read(_eepromOffset+i);
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
#ifdef DEBUG
        Serial.print(F("EEPROM write at "));
        Serial.print(_eepromOffset);
#endif
        for (uint8_t i=0; i<sizeof(T); i++) {
#ifdef DEBUG
            Serial.print('+');
            Serial.print(i);
#endif
            EEPROM.update(_eepromOffset+i, ptr[i]);
        }
#ifdef DEBUG
        Serial.println('.');
#endif
    }

    T get() { return _value; }
    bool set(T v) { if (v >= _min && v<=_max) { _value = v; return true; } else { return false; } }

    // over-ride this in your child classes to get a representation
    // as a uint8_t
    virtual uint8_t getUi8Repr() { return (uint8_t)get(); }
    // over-ride this in your child classes to set from a representation
    // as a uint8_t
    virtual bool setUi8Repr(uint8_t v) { return set((T)v); }

    virtual void increment() {
        if (_value++ > _max) {
            _value = _min;
        }
    }

    size_t size() { return sizeof(T); }

private:
    uint16_t _eepromOffset;

protected:
    T _value;
    T _min;
    T _max;
    T _def;
};

class ScaledIntSetting : public PersistentSetting<int> {
public:
    ScaledIntSetting(uint16_t eepromOffset, int min, int max, int def, int scale) :
        PersistentSetting<int>(eepromOffset, min, max, def),
        _scale(scale) {;}
    uint8_t getUi8Repr() { return _value/_scale; }
    bool setUi8Repr(uint8_t v) { return set(v*_scale); }
    virtual void increment() {
        uint16_t r=getUi8Repr() + 1;
        if (!setUi8Repr(r)) {
            _value = _min;
        }
    }

private:
    int _scale;
};

