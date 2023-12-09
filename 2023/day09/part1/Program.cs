// See https://aka.ms/new-console-template for more information
using System;

Console.WriteLine("Hello, World!");
Console.WriteLine("The current time is " + DateTime.Now);
Console.WriteLine("Args: " + string.Join(", ", args));


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
        // read the next line
        line = reader.ReadLine();
    }
}