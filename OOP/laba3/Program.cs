using System.IO.Compression;

internal class Program
{
    private static void Main(string[] args)
    {

        using (Clock clock = new Stopwatch()) {
            clock.PrintTime();
        }

        using (Clock clock = new MechanicalClock()) {
            clock.PrintTime();
        }
    }
}