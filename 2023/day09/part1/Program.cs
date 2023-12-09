internal class Program
{
    private static void Main(string[] args)
    {
        Console.WriteLine("Hello, World!");
        Console.WriteLine("The current time is " + DateTime.Now);
        Console.WriteLine("Args: " + string.Join(", ", args));


        List<string> listOfLines = new();

        // open file for reading
        using (var reader = new StreamReader(args[1]))
        {
            // read the first line from the file
            string line = reader.ReadLine();

            // loop over the lines in the file
            while (line != null)
            {
                // write the line to console window
                Console.WriteLine(line);
                listOfLines.Add(line);
                // read the next line
                line = reader.ReadLine();
            }
        }
        Console.WriteLine("Number of lines: " + listOfLines.Count);
    }
}