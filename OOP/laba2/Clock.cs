using System.Reflection.Metadata.Ecma335;

internal abstract class Clock {
    private string owner;
    public string? Owner {
        get => owner;
        private set => owner = value ?? "Unnamed";
    }

    public Clock(string buyer = "Unnamed") {
        Owner = buyer;
    }

    public void PrintTime() {
        Console.WriteLine("Clock: " + DateTime.Now.Hour.ToString());
    }
}