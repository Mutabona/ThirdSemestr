internal class Program
{
    private static void Main(string[] args)
    {
        var clocks = new List<Clock>();

        clocks.Add(new Stopwatch());
        clocks.Add(new Stopwatch("Andrey", "Stopwatch entertainment"));

        foreach (Stopwatch clock in clocks)
            Console.WriteLine("Owner: " + clock.Owner + " Manucaturer: " + clock.Manufacturer);
        
        ((Stopwatch)clocks[0]).PrintTime();
        ((MechanicalClock)clocks[1]).PrintTime();
        ((Clock)clocks[1]).PrintTime();
    }
}