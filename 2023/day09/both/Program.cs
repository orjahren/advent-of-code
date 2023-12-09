﻿internal class Program
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
    private static int GetPrevNumberForList(List<int> nums)
    {
        List<List<int>> histories = new();
        List<int> diffs = nums;
        histories.Add(diffs);
        while (!diffs.All(x => x == 0))
        {
            diffs = GetDiffsForList(diffs);
            histories.Add(diffs);
        }
        for (int i = histories.Count - 1; i > 0; i--)
        {
            int a = histories[i].First();
            List<int> nextHistory = histories[i - 1];
            int toApp = nextHistory.First() - a;
            nextHistory.Insert(0, toApp);

        }
        return histories[0].First();
    }
    private static int GetNextNumberForList(List<int> nums)
    {
        List<List<int>> histories = new();
        List<int> diffs = new(nums);
        histories.Add(diffs);
        while (!diffs.All(x => x == 0))
        {
            diffs = GetDiffsForList(diffs);
            histories.Add(diffs);
        }
        for (int i = histories.Count - 1; i > 0; i--)
        {
            int a = histories[i].Last();
            List<int> nextHistory = histories[i - 1];
            int toApp = a + nextHistory.Last();
            nextHistory.Add(toApp);

        }
        return histories[0].Last();
    }
    private static void Main(string[] args)
    {
        int part1 = 0;
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
                part1 += GetNextNumberForList(lineNums);
                part2 += GetPrevNumberForList(lineNums);
                line = reader.ReadLine();
            }
        }
        Console.WriteLine("Part 1: " + part1);
        Console.WriteLine("Part 2: " + part2);
    }
}