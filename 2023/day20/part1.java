import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Part1 {
    final static char NOOP = 'x';
    long nLowPulses = 0;
    long nHighPulses = 0;
    HashMap<String, Module> moduleMap = new HashMap<String, Module>();

    static protected enum PulseType {
        HIGH, LOW
    }

    abstract protected class Module {

        String name;
        PulseType lastSignal;
        List<String> outboundConnectionNames;
        char type = NOOP;
        boolean isOn = false;

        Module(String line, char type) {
            this.type = type;
            final String[] pilSpl = line.split(" -> ");
            System.out.println("\tWill make: " + Arrays.toString(pilSpl));
            final String stem = pilSpl[0].strip();
            System.out.println(stem);
            final String[] outboundConnectionNames = pilSpl[1].split(", ");
            this.outboundConnectionNames = Arrays.asList(outboundConnectionNames);
            System.out.println("outboundConnectionNames: " + this.outboundConnectionNames);
            System.out.println("outboundConnectionNames.size(): " + this.outboundConnectionNames.size());

            this.name = type == NOOP ? stem : stem.substring(1);
            System.out.println("\t\tLaget module with name: " + name);

        }

        public void sendPulse(PulseType pulseType) {
            for (String outboundConnectionName : this.outboundConnectionNames) {
                if (pulseType == PulseType.HIGH) {
                    // System.out.println("Sender en høy");
                    // System.out.println("For pulseType: " + pulseType);
                    nHighPulses++;
                } else {
                    // System.out.println("Sender en lav");
                    nLowPulses++;
                }
                if (outboundConnectionName.equals("output")) {
                    System.out.println("Skipping output pulse");
                    return;
                }
                // System.out.println("\t\t\tBroadcasting pulse to: " + outboundConnectionName);
                Module m = moduleMap.get(outboundConnectionName);

                System.out.println(this.name + " -" + pulseType + "-> " + m.name);

                if (m == null) {
                    System.err.println("No module found with name: " + outboundConnectionName);

                    // System.exit(1);
                }
                if (m != null) {
                    m.receivePulse(pulseType, this.name);
                }
            }
        }

        public void receivePulse(PulseType pulseType, String nameOfSender) {
            this.sendPulse(pulseType);
            this.lastSignal = pulseType;
        }

        protected void setOn(boolean val) {
            this.isOn = val;
        }

    }

    class FlipFlop extends Module {
        FlipFlop(String line) {
            super(line, '%');
        }

        @Override
        public void receivePulse(PulseType pulseType, String nameOfSender) {
            if (pulseType == PulseType.HIGH) {
                return;
            }
            if (pulseType == PulseType.LOW) {
                this.isOn = !this.isOn;
                this.sendPulse(this.isOn ? PulseType.HIGH : PulseType.LOW);
            } else {
                System.err.println("Unknown pulse type: " + pulseType);
                System.exit(1);
            }
        }
    }

    class Conjunction extends Module {
        Map<String, PulseType> inputSignals = new HashMap<String, PulseType>();

        Conjunction(String line) {
            super(line, '&');
        }

        private boolean remembersHighForAll() {
            for (String name : this.inputSignals.keySet()) {
                if (this.inputSignals.get(name) == PulseType.LOW) {
                    return false;
                }
            }
            return true;
        }

        @Override
        public void receivePulse(PulseType pulseType, String nameOfSender) {
            if (!inputSignals.containsKey(nameOfSender)) {
                inputSignals.put(nameOfSender, PulseType.LOW);
            }
            inputSignals.put(nameOfSender, pulseType);

            if (this.remembersHighForAll()) {
                this.sendPulse(PulseType.LOW);
            } else {
                this.sendPulse(PulseType.HIGH);
            }

            this.lastSignal = pulseType;
        }
    }

    class Broadcaster extends Module {
        Broadcaster(String line) {
            super(line, NOOP);
        }
    }

    Module moduleFromLine(String line) {
        if (line.contains("%")) {
            return new FlipFlop(line);
        } else if (line.contains("&")) {
            return new Conjunction(line);
        }
        return new Broadcaster(line);
    }

    void pressButtonNtimes(Module broadcaster, int n) {
        for (int i = 0; i < n; i++) {
            System.out.println("------------- Pressing button for " + i + " time");
            nLowPulses++;
            broadcaster.sendPulse(PulseType.LOW);
        }
    }

    long solve(int n) throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        while (line != null) {
            System.out.println(line);
            Module m = moduleFromLine(line);
            moduleMap.put(m.name, m);
            line = br.readLine();
        }
        System.out.println("Made " + moduleMap.size() + " modules");
        // print names:
        for (String name : moduleMap.keySet()) {
            System.out.println(name);
        }

        Module broadcaster = moduleMap.get("broadcaster");
        if (broadcaster == null) {
            System.err.println("No broadcaster found");
            System.exit(1);
        }
        pressButtonNtimes(broadcaster, n);
        System.out.println("nHighPulses: " + nHighPulses);
        System.out.println("nLowPulses: " + nLowPulses);

        return nHighPulses * nLowPulses;
    }

    public static void main(String[] args) {
        final Part1 p = new Part1();
        try {
            final long result = p.solve(1000);
            System.out.println("Part1: " + result);
        } catch (IOException e) {
            System.err.println("IO error: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}
// First res: 829159479. Too high.