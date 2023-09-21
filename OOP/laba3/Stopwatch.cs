internal sealed class Stopwatch: MechanicalClock {

    public Stopwatch(string buyer = "Unnamed", string manufacturer = "Not pointed"): base(buyer, manufacturer) {}

    public override void PrintTime()
    { 
        Console.WriteLine("Stopwatch: " + DateTime.Now.Second.ToString());
    }

    ~Stopwatch() {
        Console.WriteLine("Finalizing stopwatch");
    }

    public override void Dispose() {
        Console.WriteLine("Disposing stopwatch");
        GC.SuppressFinalize(this);
    }
}