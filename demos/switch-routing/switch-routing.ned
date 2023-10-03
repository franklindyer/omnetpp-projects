simple Host
{
    parameters:
        volatile double betweenMsg;
    gates:
        input in;
        output out;
}

simple Switch
{
    parameters:
        double expire;
        int numHosts;
    gates:
        input in[];
        output out[];
}

network SwitchRouting
{
    submodules:
        hosts[4]: Host;
        switches[2]: Switch;
    connections:
        hosts[0].out --> { delay = 100ms; } --> switches[0].in++;
        hosts[0].in <-- { delay = 100ms; } <-- switches[0].out++;

        hosts[1].out --> { delay = 100ms; } --> switches[0].in++;
        hosts[1].in <-- { delay = 100ms; } <-- switches[0].out++;

        hosts[2].out --> { delay = 100ms; } --> switches[1].in++;
        hosts[2].in <-- { delay = 100ms; } <-- switches[1].out++;

        hosts[3].out --> { delay = 100ms; } --> switches[1].in++;
        hosts[3].in <-- { delay = 100ms; } <-- switches[1].out++;

        switches[0].out++ --> { delay = 100ms; } --> switches[1].in++;
        switches[0].in++ <-- { delay = 100ms; } <-- switches[1].out++;
}
