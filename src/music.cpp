#include "music.hpp"

#include <portmidi.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

static PmError error = pmNoError;
static PortMidiStream* stream;

void music_init() {
    if ((error=Pm_Initialize())) {
        cout << "Error on initialisation: " << Pm_GetErrorText(error) << endl;
        exit(error);
    }

    int num_devices = Pm_CountDevices();
    cout << "Number of MIDI devices: " << num_devices << endl;

    for (int i = 0; i < num_devices; i++) {
        const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
        const char *name = info->name;
        const char *input = info->input ? "input" : "";
        const char *output = info->output ? "output" : "";
        const char *sep = info->input && info->output ? ", " : "";
        cout << "  [" << i << "] " << input << sep << output << " device: " << name << endl;
    }

    if (num_devices > 0) {
        int device_id = 0;
        if (num_devices > 1) {
            cout << "Select MIDI output [0";
            for (int i = 1; i < num_devices; i++) { cout << ", " << i; }
            cout << "]: ";
            cin >> device_id;
        }

        cout << "Opening device " << device_id << endl;

        if ((error=Pm_OpenOutput(&stream, device_id, NULL, 1, 0, 0, 0))) {
            cout << "Error opening device " << device_id << ":" << Pm_GetErrorText(error) << endl;
            exit(error);
        }
    }
}

void music_destroy() {
    if (stream != 0) {
        int notes[] = {60, 64, 67, 71};
        for (int i = 0; i < 4; i++) {
            PmEvent buffer = { Pm_Message(138, notes[i], 0), 0 };
            if (stream != 0) { Pm_Write(stream, &buffer, 1); }
        }
        Pm_Close(stream);
    }
    stream = 0;
    Pm_Terminate();
}


void music_beat(SoundID sound_id, int volume) {
    int note = 0;

    switch(sound_id) {
        case FIRST_DRUM:
            note = 60;
            break;
        case SECOND_DRUM:
            note = 64;
            break;
        case THIRD_DRUM:
            note = 67;
            break;
        case FOURTH_DRUM:
            note = 71;
            break;
    }

    PmEvent buffer = { Pm_Message(154, note, min(max(volume, 0), 128)), 0 };
    if (stream != 0) { Pm_Write(stream, &buffer, 1); }
}
