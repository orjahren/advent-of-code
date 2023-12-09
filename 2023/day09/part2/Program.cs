internal class Program
{
    private static List<int> GetDiffsForList(List<int> nums)
    {
        List<int> diffs = new();
        for (int i = 0; i < nums.Count - 1; i++)
        {
            int diff = nums[i + 1] - nums[i];
            diffs.Add(diff);
        }
        return diffs;
    }
    private static void PrintIntList(List<int> nums)
    {
        foreach (int i in nums)
        {
            Console.Write(i + " ");
        }
        Console.Write("\n");
    }
    private static int GetPrevNumberForList(List<int> nums)
    {
        Console.WriteLine("Skal processere denne listen: ");
        PrintIntList(nums);


        List<List<int>> histories = new();
        List<int> diffs = new(nums);
        List<int> lastHistory = new(nums);

        histories.Add(lastHistory);

        while (!diffs.All(x => x == 0))
        {
            diffs = GetDiffsForList(lastHistory);
            Console.WriteLine("Diffs: ");
            PrintIntList(diffs);
            lastHistory = new List<int>(diffs);
            histories.Add(lastHistory);
        }
        //lastHistory.Add(0);
        lastHistory.Insert(0, 0);
        for (int i = histories.Count - 1; i > 0; i--)
        {
            List<int> history = histories[i];
            Console.WriteLine("Skal behandle denne historyen: ");
            PrintIntList(history);
            Console.WriteLine("Neste for den er: ");
            List<int> nextHistory = histories[i - 1];
            PrintIntList(nextHistory);

            //int toApp = history.First() + nextHistory.First();
            int toApp = nextHistory.First() - history.First();
            Console.WriteLine("\t Legger til: " + toApp);
            //nextHistory.Add(toApp);
            //nextHistory.Insert(toApp, 0);
            nextHistory.Insert(0, toApp);
            PrintIntList(nextHistory);

        }
        int res = histories[0].First();
        Console.WriteLine("Resultatet er: " + res);
        Console.WriteLine("-----------------------------------------------");
        return histories[0].First();

        /*
                // sum last values of each history
                Console.WriteLine("The final histories: ");
                int sum = 0;
                foreach (List<int> history in histories)
                {
                    PrintIntList(history);
                    sum += history.Last();
                }
                Console.WriteLine("\tSum: " + sum);
                Console.WriteLine("-----------------------------------------------");
                return sum;
         */


    }
    private static void Main(string[] args)
    {
        int part2 = 0;
        using (var reader = new StreamReader(args[1]))
        {
            string? line = reader.ReadLine();
            while (line != null)
            {
                string[] split = line.Split(" ");
                List<int> lineNums = new();
                foreach (string s in split)
                    lineNums.Add(int.Parse(s));
                part2 += GetPrevNumberForList(lineNums);
                line = reader.ReadLine();
            }
        }
        Console.WriteLine("Part 2: " + part2);
    }
}
