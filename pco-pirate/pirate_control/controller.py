import rtmidi
import random

class MidiInterface:
    def __init__(self, listener):
        self.listener = listener
        self.intf = rtmidi.MidiIn()
        available_ports = self.intf.get_ports()
        print "Available MIDI ports: %d" % len(available_ports)
        if available_ports:
            self.intf.set_callback(self.callback)
            self.intf.open_port(0)

    InvalidType           = 0x00    # For notifying errors
    NoteOff               = 0x80    # Note Off
    NoteOn                = 0x90    # Note On
    AfterTouchPoly        = 0xA0    # Polyphonic AfterTouch
    ControlChange         = 0xB0    # Control Change / Channel Mode
    ProgramChange         = 0xC0    # Program Change
    AfterTouchChannel     = 0xD0    # Channel (monophonic) AfterTouch
    PitchBend             = 0xE0    # Pitch Bend
    SystemExclusive       = 0xF0    # System Exclusive
    TimeCodeQuarterFrame  = 0xF1    # System Common - MIDI Time Code Quarter Frame
    SongPosition          = 0xF2    # System Common - Song Position Pointer
    SongSelect            = 0xF3    # System Common - Song Select
    TuneRequest           = 0xF6    # System Common - Tune Request
    Clock                 = 0xF8    # System Real Time - Timing Clock
    Start                 = 0xFA    # System Real Time - Start
    Continue              = 0xFB    # System Real Time - Continue
    Stop                  = 0xFC    # System Real Time - Stop
    ActiveSensing         = 0xFE    # System Real Time - Active Sensing
    SystemReset           = 0xFF    # System Real Time - System Reset

    def callback(self, message, timestamp):
        data = message[0]
        status = data[0] & 0xf0
        if status == self.NoteOn:
            self.listener.handleNoteOn(data[1])
        elif status == self.PitchBend:
            # For Factory
            amount = float((data[2] << 7 | data[1]) - 0x1fff) / float(0x1fff)
            # For Player
            # amount = float(data[2] - 63) / 64
            self.listener.handlePitchBend(amount)
        elif status == self.ControlChange:
            if data[1] == 1:
                vibratoAmountMax = 100
                amount = int(data[2] * vibratoAmountMax / 127)
                self.listener.sendVibratoAmount(amount)

class PcoController:

    # Messages

    CoarseNote          = 0x80  # [Semitones]
    FineNote            = 0x81  # [Semitones]  [Cents]
    GlobalDetune        = 0x82  # [MSB]        [LSB]   (14 bits signed)
    ModulationRange     = 0x83  # [MSB]        [LSB]   (14 bits unsigned)
    PortamentoAmount    = 0x84  # [MSB]        [LSB]   (14 bits unsigned)
    PortamentoMode      = 0x85  # [Mode]
    VibratoSpeed        = 0x86  # [MSB]        [LSB]   (14 bits unsigned)
    VibratoAmount       = 0x87  # [MSB]        [LSB]   (14 bits unsigned)
    VibratoWaveform     = 0x88  # [Waveform]
    PwmBaseLevel        = 0x89  # [MSB]        [LSB]   (14 bits signed)
    PwmSpeed            = 0x8A  # [MSB]        [LSB]   (14 bits unsigned)
    PwmAmount           = 0x8B  # [MSB]        [LSB]   (14 bits unsigned)
    PwmWaveform         = 0x8C  # [Waveform]
    EnableModulation    = 0x8D  # Status only
    DisableModulation   = 0x8E  # Status only
    EnableSync          = 0x8F  # Status only
    DisableSync         = 0x90  # Status only
    EnablePortamento    = 0x91  # Status only
    DisablePortamento   = 0x92  # Status only
    Mute                = 0x93  # Status only
    Unmute              = 0x94  # Status only
    ResetPhase          = 0x95  # Status only


    def __init__(self, interface):
        self.interface = interface
        self.midi = MidiInterface(self)
        self.currentDetune = float(0)
        self.currentBend = float(0)

    # --------------------------------------------------------------------------

    def handleNoteOn(self, pitch):
        self.sendNote(pitch, 0)

    def handlePitchBend(self, bend):
        self.currentBend = bend
        self.computeAndSendBend()

    def computeAndSendBend(self):
        bendRange = 1200.
        bendAmount = bendRange * self.currentBend + self.currentDetune
        self.sendGlobalDetune(int(bendAmount))

    # --------------------------------------------------------------------------

    def setGlobalDetune(self, detune):
        self.currentDetune = detune
        self.computeAndSendBend()

    # --------------------------------------------------------------------------

    def triggerPortamento(self):
        randomNote = int(random.randrange(0, 127))
        self.sendNote(randomNote, 0)

    # --------------------------------------------------------------------------

    def sendNote(self, coarse, fine):
        if fine:
            opcode = self.FineNote
            data1 = coarse
            data2 = fine
            self.interface.send([opcode, data1, data2])
            print "Note:                       %d %d" % (data1, data2)
        else:
            opcode = self.CoarseNote
            data1 = coarse
            self.interface.send([opcode, data1])
            print "Note:                       %d" % data1

    def sendFineNote(self, fine):
        opcode = self.FineNote
        data1 = fine / 100
        data2 = fine % 100
        self.interface.send([opcode, data1, data2])
        print "Note:                       %d %d" % (data1, data2)

    def sendGlobalDetune(self, inDetune):
        opcode = self.GlobalDetune
        data1 = (inDetune >> 7) & 0x7f
        data2 = inDetune & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "Global detune:              %d" % inDetune
        return None

    # --------------------------------------------------------------------------

    def sendModulationRangeSemi(self, semi):
        opcode = self.ModulationRange
        data1 = semi
        data2 = 0
        self.interface.send([opcode, data1, data2])
        print  "Modulation range:           %d" % (semi * 100)

    def sendEnableModulation(self, enable):
        opcode = self.EnableModulation if enable else self.DisableModulation
        self.interface.send([opcode])
        str =  "Modulation status:          "
        if enable:  str += "On"
        else:       str += "Off"
        print str

    # --------------------------------------------------------------------------

    def sendPortamentoAmount(self, amount):
        opcode = self.PortamentoAmount
        data1 = (amount >> 7) & 0x7f
        data2 = amount & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "Portamento amount:          %d" % amount

    def sendPortamentoMode(self, mode):
        opcode = self.PortamentoMode
        data1 = mode & 0x7f
        self.interface.send([opcode, data1])
        str =  "Portamento mode:            "
        if mode == 0:   str += "Linear"
        elif mode == 1: str += "Exponential"
        elif mode == 2: str += "Log"
        print str

    def sendEnablePortamento(self, enable):
        opcode = self.EnablePortamento if enable else self.DisablePortamento
        self.interface.send([opcode])
        str =  "Portamento status:          "
        if enable:  str += "On"
        else:       str += "Off"
        print str

    # --------------------------------------------------------------------------

    def sendVibratoSpeed(self, speed):
        opcode = self.VibratoSpeed
        data1 = (speed >> 7) & 0x7f
        data2 = speed & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "Vibrato speed:              %d" % speed

    def sendVibratoAmount(self, amount):
        opcode = self.VibratoAmount
        data1 = (amount >> 7) & 0x7f
        data2 = amount & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "Vibrato amount:             %d" % amount

    def sendVibratoWaveform(self, wave):
        opcode = self.VibratoWaveform
        data1 = wave & 0x7f
        self.interface.send([opcode, data1])
        str =  "Vibrato waveform:           "
        if wave:    str += "Square"
        else:       str += "Sine"
        print str

    # ------------------------------------------------------------------------------

    def sendPwmBaseLevel(self, level):
        opcode = self.PwmBaseLevel
        data1 = (level >> 7) & 0x7f
        data2 = level & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "PWM base level:             %d" % level

    def sendPwmSpeed(self, speed):
        opcode = self.PwmSpeed
        data1 = (speed >> 7) & 0x7f
        data2 = speed & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "PWM speed:                  %d" % speed

    def sendPwmAmount(self, amount):
        opcode = self.PwmAmount
        data1 = (amount >> 7) & 0x7f
        data2 = amount & 0x7f
        self.interface.send([opcode, data1, data2])
        print  "PWM amount:                 %d" % amount

    def sendPwmWaveform(self, wave):
        opcode = self.PwmWaveform
        data1 = wave & 0x7f
        self.interface.send([opcode, data1])

    # --------------------------------------------------------------------------

    def sendEnableSync(self, enable):
        opcode = self.EnableSync if enable else self.DisableSync
        self.interface.send([opcode])
        str =  "Sync status:                "
        if enable:  str += "On"
        else:       str += "Off"
        print str
