import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Part2 {
    final static char NOOP = 'x';
    long nLowPulses = 0;
    long nHighPulses = 0;
    HashMap<String, Module> moduleMap = new HashMap<String, Module>();
    // TODO: Bruk deque
    List<String> queOfModuleNamesToAct = new ArrayList<String>();
    boolean rxHasPulse = false;

    static protected enum PulseType {
        HIGH, LOW
    }

    abstract protected class Module {

        String name;
        List<String> outboundConnectionNames;
        char type = NOOP;
        protected boolean status = false;

        List<PulseType> pulseQue = new ArrayList<PulseType>();
        List<String> namesQue = new ArrayList<String>();
        PulseType lastSignal = PulseType.LOW;
        String nameOfLastSender;

        public boolean isOn() {
            return status;
        }

        Module(String line, char type) {
            this.type = type;
            final String[] pilSpl = line.split(" -> ");
            final String stem = pilSpl[0].strip();
            this.outboundConnectionNames = Arrays.asList(pilSpl[1].split(", "));
            this.name = type == NOOP ? stem : stem.substring(1);
        }

        public void sendPulse(PulseType pulseType) {
            for (String outboundConnectionName : this.outboundConnectionNames) {
                if (pulseType == PulseType.HIGH) {
                    nHighPulses++;
                } else {
                    nLowPulses++;
                }
                Module m = moduleMap.get(outboundConnectionName);
                // System.out.println("Sending pulse to: " + outboundConnectionName);
                if (outboundConnectionName.equals("output")) {
                    return;
                }
                if (m != null) {
                    queOfModuleNamesToAct.add(m.name);
                    m.receivePulse(pulseType, this.name);
                }
            }
        }

        public void receivePulse(PulseType pulseType, String nameOfSender) {
            this.pulseQue.add(pulseType);
            this.namesQue.add(nameOfSender);
        }

        public void actOnPulse() {
            if (this.name.equals("rx")) {
                rxHasPulse = true;
            }
            this.lastSignal = pulseQue.remove(0);
            this.nameOfLastSender = namesQue.remove(0);

        }

        public boolean isConjunction() {
            return this.type == '&';
        }

    }

    class Broadcaster extends Module {
        Broadcaster(String line) {
            super(line, NOOP);
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            this.sendPulse(this.lastSignal);
        }
    }

    class FlipFlop extends Module {
        FlipFlop(String line) {
            super(line, '%');
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            if (this.lastSignal == PulseType.LOW) {
                this.status = !this.status;
                this.sendPulse(this.isOn() ? PulseType.HIGH : PulseType.LOW);
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
                if (this.inputSignals.get(name) == PulseType.LOW && !name.equals(this.name)) {
                    return false;
                }
            }
            return true;
        }

        @Override
        public void receivePulse(PulseType pulseType, String nameOfSender) {
            super.receivePulse(pulseType, nameOfSender);
            this.nameOfLastSender = nameOfSender;
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            inputSignals.put(nameOfLastSender, this.lastSignal);
            this.sendPulse(remembersHighForAll() ? PulseType.LOW : PulseType.HIGH);
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

    long solve(int n) throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        final List<String> moduleNames = new ArrayList<>();
        final List<String> conjunctionNames = new ArrayList<>();
        while (line != null) {
            System.out.println(line);
            Module m = moduleFromLine(line);
            moduleMap.put(m.name, m);
            moduleNames.add(m.name);
            if (m.isConjunction()) {
                conjunctionNames.add(m.name);
            }

            line = br.readLine();
        }
        System.out.println("Made " + moduleMap.size() + " modules");
        // print names:
        for (String name : moduleMap.keySet()) {
            System.out.println(name);
        }

        // set defaults for all conjunctions:
        for (String name : conjunctionNames) {
            Conjunction c = (Conjunction) moduleMap.get(name);
            for (String moduleName : moduleNames) {
                Module candMod = moduleMap.get(moduleName);
                if (candMod.outboundConnectionNames.contains(name)) {
                    c.inputSignals.put(moduleName, PulseType.LOW);
                }
                // c.inputSignals.put(moduleName, PulseType.LOW);
            }
        }

        Module broadcaster = moduleMap.get("broadcaster");
        if (broadcaster == null) {
            System.err.println("No broadcaster found");
            System.exit(1);
        }
        // pressButtonNtimes(broadcaster, n, 4);
        long part2 = 0;
        while (!rxHasPulse) {
            part2++;
            nLowPulses++;
            broadcaster.sendPulse(PulseType.LOW);
            while (queOfModuleNamesToAct.size() > 0) {
                // System.out.println("\t\t\tBroadcasting pulse to: " + outboundConnectionName);
                String outboundConnectionName = queOfModuleNamesToAct.remove(0);
                Module m = moduleMap.get(outboundConnectionName);

                if (m == null) {
                    System.err.println("No module found with name: " + outboundConnectionName);

                    // System.exit(1);
                }
                if (m != null) {
                    m.actOnPulse();
                }
            }
        }
        System.out.println("nHighPulses: " + nHighPulses);
        System.out.println("nLowPulses: " + nLowPulses);
        return part2;
    }

    public static void main(String[] args) {
        final Part2 p = new Part2();
        try {
            final long result = p.solve(1000);
            System.out.println("Part 2: " + result);
        } catch (IOException e) {
            System.err.println("IO error: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}