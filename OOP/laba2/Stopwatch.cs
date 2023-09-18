internal sealed class Stopwatch: MechanicalClock {

    public Stopwatch(string buyer = "Unnamed", string manufacturer = "Not pointed"): base(buyer, manufacturer) {}

    public new void PrintTime()
    {
        Console.WriteLine("Stopwatch: " + DateTime.Now.Second.ToString());
    }
}