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
            Console.WriteLine(i);
        }
    }
    private static int GetNextNumberForList(List<int> nums)
    {
        Console.WriteLine("Skal processere denne listen: ");
        PrintIntList(nums);


        List<List<int>> histories = new();
        List<int> diffs = new(nums);
        List<int> lastHistory = new(nums);

        while (!diffs.All(x => x == 0))
        {
            diffs = GetDiffsForList(lastHistory);
            Console.WriteLine("Diffs: ");
            PrintIntList(diffs);
            lastHistory = new List<int>(diffs);
            histories.Add(lastHistory);
        }



        int sum = 0;
        foreach (int i in nums)
        {
            sum += i;
        }
        return sum;
    }
    private static void Main(string[] args)
    {
        Console.WriteLine("Hello, World!");
        Console.WriteLine("The current time is " + DateTime.Now);
        Console.WriteLine("Args: " + string.Join(", ", args));


        List<string> listOfLines = new();
        List<List<int>> nums = new();

        // open file for reading
        using (var reader = new StreamReader(args[1]))
        {
            // read the first line from the file
            string? line = reader.ReadLine();

            // loop over the lines in the file
            while (line != null)
            {
                // write the line to console window
                Console.WriteLine(line);
                listOfLines.Add(line);
                // split line at space 
                string[] split = line.Split(' ');
                List<int> lineNums = new();
                foreach (string s in split)
                {
                    // convert each number to an int
                    int num = int.Parse(s);
                    lineNums.Add(num);
                }
                nums.Add(lineNums);
                // read the next line
                line = reader.ReadLine();
            }
        }
        Console.WriteLine("Number of lines: " + listOfLines.Count);
        Console.WriteLine("Number of numbers: " + nums.Count);
        Console.WriteLine(nums);
        Console.WriteLine(nums[0]);

        List<int> processedVals = new();
        foreach (List<int> line in nums)
        {
            int sum = GetNextNumberForList(line);
            processedVals.Add(sum);
        }
        int res = processedVals.Sum();
        Console.WriteLine("Part 1: " + res);
    }
}