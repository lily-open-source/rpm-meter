sequenceDiagram
    participant Setup as setup()
    participant MainLoop as mainLoop()
    participant PulseInterrupt as pulseInterrupt()
    participant LCD as LCD Object
    participant HallSensor as Hall Sensor

    Setup->>LCD: Initialize LCD
    Setup->>LCD: Set cursor and print "RPM Meter"
    Setup->>HallSensor: Configure Hall Sensor
    Setup->>HallSensor: Attach Interrupt

    MainLoop->>MainLoop: Record current time
    MainLoop->>MainLoop: Check update interval

    alt Interval Passed
        MainLoop->>PulseInterrupt: Disable interrupts
        MainLoop->>MainLoop: Copy and reset pulse count
        MainLoop->>MainLoop: Calculate RPM
        MainLoop->>PulseInterrupt: Re-enable interrupts
        MainLoop->>LCD: Set cursor to second row
        MainLoop->>LCD: Print RPM
    end

    PulseInterrupt-->>MainLoop: Increment pulse count

