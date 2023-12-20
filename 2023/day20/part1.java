import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

class Part1 {
    final static char NOOP = 'x';
    long nLowPulses = 0;
    long nHighPulses = 0;

    abstract protected class Module {
        String name;
        String lastSignal;
        List<String> outboundConnectionNames;
        char type = NOOP;
        boolean isOn = false;

        Module(String line) {
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

        public void voidReceivePulse(String pulseType) {
            this.lastSignal = pulseType;
        }

        protected void setOn(boolean val) {
            this.isOn = val;
        }

    }

    class FlipFlop extends Module {
        FlipFlop(String line) {
            super(line);
            this.type = '%';
        }

        @Override
        public void voidReceivePulse(String pulseType) {
            if (pulseType.equals("1")) {
                this.isOn = !this.isOn;
            }
        }
    }

    class DefaultModule extends Module {
        DefaultModule(String line) {
            super(line);
        }
    }

    class Conjunction extends Module {
        Conjunction(String line) {
            super(line);
            this.type = '&';
        }

        @Override
        public void voidReceivePulse(String pulseType) {
            this.lastSignal = pulseType;
        }
    }

    Module moduleFromLine(String line) {
        if (line.contains("%")) {
            return new FlipFlop(line);
        } else if (line.contains("&")) {
        }

        return new DefaultModule(line);
    }

    int solve() throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        HashMap<String, Module> moduleMap = new HashMap<String, Module>();
        while (line != null) {
            System.out.println(line);
            Module m = moduleFromLine(line);
            moduleMap.put(m.name, m);
            line = br.readLine();
        }
        System.out.println("Made " + moduleMap.size() + " modules");
        return 0;
    }

    public static void main(String[] args) {
        final Part1 p = new Part1();
        try {
            final long result = p.solve();
            System.out.println("Part1: " + result);
        } catch (IOException e) {
            System.err.println("IO error: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}