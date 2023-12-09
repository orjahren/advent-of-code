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
    private static (int, int) GetPrevAndNextNumberForList(List<int> nums)
    {
        List<List<int>> histories = new() { nums };
        while (!histories.Last().All(x => x == 0))
            histories.Add(GetDiffsForList(histories.Last()));
        for (int i = histories.Count - 1; i > 0; i--)
        {
            List<int> currHist = histories[i];
            List<int> nextHist = histories[i - 1];

            int appPre = nextHist.First() - currHist.First();
            int appPost = currHist.Last() + nextHist.Last();

            nextHist.Insert(0, appPre);
            nextHist.Add(appPost);

        }
        return (nums.First(), nums.Last());
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
                (int prev, int next) = GetPrevAndNextNumberForList(lineNums);
                part1 += next;
                part2 += prev;
                line = reader.ReadLine();
            }
        }
        Console.WriteLine("Part 1: " + part1);
        Console.WriteLine("Part 2: " + part2);
    }
}