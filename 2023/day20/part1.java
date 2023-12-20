import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

class Part1 {
    final static char NOOP = 'x';
    long nLowPulses = 0;
    long nHighPulses = 0;
    HashMap<String, Module> moduleMap = new HashMap<String, Module>();
    Deque<String> queOfModuleNamesToAct = new LinkedList<String>();

    static protected enum PulseType {
        HIGH, LOW
    }

    abstract protected class Module {

        String name;
        List<String> outboundConnectionNames;
        char type = NOOP;
        protected boolean status = false;

        Deque<PulseType> pulseQue = new LinkedList<PulseType>();
        Deque<String> namesQue = new LinkedList<String>();
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
                if (m != null && !outboundConnectionName.equals("output")) {
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
            this.lastSignal = pulseQue.pop();
            this.nameOfLastSender = namesQue.pop();

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

    void pressButtonNtimes(Module broadcaster, int n, int debugN) {
        for (int i = 0; i < n; i++) {
            nLowPulses++;
            broadcaster.sendPulse(PulseType.LOW);
            while (queOfModuleNamesToAct.size() > 0) {
                String outboundConnectionName = queOfModuleNamesToAct.pop();
                Module m = moduleMap.get(outboundConnectionName);
                if (m != null) {
                    m.actOnPulse();
                }
            }
            if (debugN > 0 && i >= debugN)
                return;
        }
    }

    long solve(int n) throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        final List<String> moduleNames = new ArrayList<>();
        final List<String> conjunctionNames = new ArrayList<>();
        while (line != null) {
            Module m = moduleFromLine(line);
            moduleMap.put(m.name, m);
            moduleNames.add(m.name);
            if (m.isConjunction()) {
                conjunctionNames.add(m.name);
            }

            line = br.readLine();
        }
        for (String name : conjunctionNames) {
            Conjunction c = (Conjunction) moduleMap.get(name);
            for (String moduleName : moduleNames) {
                Module candMod = moduleMap.get(moduleName);
                if (candMod.outboundConnectionNames.contains(name)) {
                    c.inputSignals.put(moduleName, PulseType.LOW);
                }
            }
        }

        Module broadcaster = moduleMap.get("broadcaster");
        pressButtonNtimes(broadcaster, n, -1);
        System.out.println("nHighPulses: " + nHighPulses);
        System.out.println("nLowPulses: " + nLowPulses);

        return nHighPulses * nLowPulses;
    }

    public static void main(String[] args) {
        final Part1 p = new Part1();
        try {
            final long result = p.solve(1000);
            System.out.println("Part 1: " + result);
        } catch (IOException e) {
            System.err.println("IO error: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}