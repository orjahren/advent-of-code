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
    private long nLowPulses = 0;
    private long nHighPulses = 0;
    final private Map<String, Module> moduleMap = new HashMap<String, Module>();
    final private Deque<String> queOfModuleNamesToAct = new LinkedList<String>();

    abstract private class Module {

        private String name;
        private List<String> outboundConnectionNames;
        public char type;
        protected boolean isOn;

        private Deque<Boolean> pulseQue = new LinkedList<Boolean>();
        private Deque<String> namesQue = new LinkedList<String>();
        protected boolean lastSignal;
        protected String nameOfLastSender;

        Module(String line, char type) {
            this.type = type;
            final String[] pilSpl = line.split(" -> ");
            final String stem = pilSpl[0].strip();
            this.outboundConnectionNames = Arrays.asList(pilSpl[1].split(", "));
            this.name = type == NOOP ? stem : stem.substring(1);
        }

        public void sendPulse(Boolean pulseType) {
            for (String outboundConnectionName : outboundConnectionNames) {
                if (pulseType) {
                    nHighPulses++;
                } else {
                    nLowPulses++;
                }
                if (moduleMap.containsKey(outboundConnectionName)) {
                    Module m = moduleMap.get(outboundConnectionName);
                    queOfModuleNamesToAct.add(m.name);
                    m.receivePulse(pulseType, name);
                }
            }
        }

        private void receivePulse(boolean pulseType, String nameOfSender) {
            this.pulseQue.add(pulseType);
            this.namesQue.add(nameOfSender);
        }

        protected void actOnPulse() {
            this.lastSignal = pulseQue.pop();
            this.nameOfLastSender = namesQue.pop();

        }
    }

    class Broadcaster extends Module {
        Broadcaster(String line) {
            super(line, NOOP);
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            this.sendPulse(lastSignal);
        }
    }

    class FlipFlop extends Module {
        FlipFlop(String line) {
            super(line, '%');
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            if (!this.lastSignal) {
                this.isOn = !this.isOn;
                this.sendPulse(this.isOn);
            }
        }
    }

    class Conjunction extends Module {
        Map<String, Boolean> inputSignals = new HashMap<String, Boolean>();

        Conjunction(String line) {
            super(line, '&');
        }

        private boolean remembersHighForAll() {
            for (String name : this.inputSignals.keySet()) {
                if (!this.inputSignals.get(name)) {
                    return false;
                }
            }
            return true;
        }

        @Override
        public void actOnPulse() {
            super.actOnPulse();
            inputSignals.put(nameOfLastSender, lastSignal);
            sendPulse(!remembersHighForAll());
        }
    }

    Module moduleFromLine(String line) {
        switch (line.charAt(0)) {
            case '%':
                return new FlipFlop(line);
            case '&':
                return new Conjunction(line);
        }
        return new Broadcaster(line);
    }

    long solve(int n) throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        final List<String> moduleNames = new ArrayList<>();
        final List<String> conjunctionNames = new ArrayList<>();
        String line = br.readLine();
        while (line != null) {
            final Module m = moduleFromLine(line);
            moduleMap.put(m.name, m);
            moduleNames.add(m.name);
            if (m.type == '&') {
                conjunctionNames.add(m.name);
            }
            line = br.readLine();
        }
        for (String name : conjunctionNames) {
            final Conjunction c = (Conjunction) moduleMap.get(name);
            for (String moduleName : moduleNames) {
                final Module candMod = moduleMap.get(moduleName);
                if (candMod.outboundConnectionNames.contains(name)) {
                    c.inputSignals.put(moduleName, false);
                }
            }
        }
        final Module broadcaster = moduleMap.get("broadcaster");
        for (int i = 0; i < n; i++) {
            nLowPulses++;
            broadcaster.sendPulse(false);
            while (queOfModuleNamesToAct.size() > 0) {
                String outboundConnectionName = queOfModuleNamesToAct.pop();
                Module m = moduleMap.get(outboundConnectionName);
                if (m != null) {
                    m.actOnPulse();
                }
            }
        }
        return nHighPulses * nLowPulses;
    }

    public static void main(String[] args) throws IOException {
        final Part1 p = new Part1();
        System.out.println("Part 1: " + p.solve(1000));
    }
}