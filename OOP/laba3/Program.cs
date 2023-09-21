internal class Program
{
    private static void Main(string[] args)
    {
        var clocks = new List<Clock>();

        clocks.Add(new Stopwatch());

        clocks[0].PrintTime();
        clocks[0].Dispose();
        clocks[0].PrintTime();
    }
}