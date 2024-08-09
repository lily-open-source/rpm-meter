flowchart TD
    Start --> Setup

    subgraph Setup
        A1(Create LCD Object) --> A2(Initialize LCD)
        A2 --> A3(Set Cursor & Print "RPM Meter")
        A3 --> B1(Set Hall Sensor Pin)
        B1 --> B2(Attach Interrupt for Pulse Counting)
    end

    Setup --> MainLoop

    subgraph MainLoop
        C1(Record Current Time) --> C2{Is Update Interval Passed?}
        C2 -- Yes --> D1(Disable Interrupts)
        D1 --> D2(Copy Pulse Count & Reset)
        D2 --> D3(Calculate RPM)
        D3 --> D4(Re-enable Interrupts)
        D4 --> E1(Set Cursor to Second Row)
        E1 --> E2(Print RPM on LCD)
        E2 --> E3(Clear Remaining Characters)
        E3 --> C1
        C2 -- No --> C1
    end

    PulseInterrupt -.-> D2(Increment Pulse Count)

    style Start fill:#f9f,stroke:#333,stroke-width:2px
    style Setup fill:#bbf,stroke:#333,stroke-width:2px
    style MainLoop fill:#afa,stroke:#333,stroke-width:2px
    style PulseInterrupt fill:#faa,stroke:#333,stroke-width:2px

