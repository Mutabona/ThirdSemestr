using System.Dynamic;
using System.Runtime.Serialization;

internal class MechanicalClock : Clock {
    private string manufacturer;
    public string? Manufacturer {
        get => manufacturer;
        private set => manufacturer = value ?? "Not pointed";
    }

    public MechanicalClock(string buyer = "Unnamed", string _manufacturer = "Not pointed"): base(buyer) {
        manufacturer = _manufacturer;
    }

    public override void PrintTime()
    {
        Console.WriteLine("Mechanical clock: " + DateTime.Now.Minute.ToString());
    }
}