internal abstract class Clock: IDisposable {
    private string? owner;
    public string? Owner {
        get => owner;
        private set => owner = value ?? "Unnamed";
    }

    public Clock(string buyer = "Unnamed") {
        Owner = buyer;
    }

    public abstract void PrintTime();

    ~Clock() {
        Console.WriteLine("Finalizing clock");
    }

    public abstract void Dispose();
}