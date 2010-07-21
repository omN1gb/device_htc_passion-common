/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_AKM_SENSOR_H
#define ANDROID_AKM_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include "nusensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/

struct input_event;

class AkmSensor : public SensorBase {
public:
    AkmSensor();
    ~AkmSensor();

    enum {
        Accelerometer   = 0,
        MagneticField   = 1,
        Orientation     = 2,
        Temperature     = 3,
        numSensors
    };

    int enable(int what, int enabled);
    int readEvents(sensors_event_t* data, int count);
    int setDelay(int64_t ns);
    void processEvent(int code, int value);

private:
    uint32_t mEnabled;
    InputEventCircularReader mInputReader;
    uint32_t mPendingMask;
    sensors_event_t mPendingEvents[numSensors];
    int mLastEventIndex;

};

/*****************************************************************************/

#endif  // ANDROID_AKM_SENSOR_H