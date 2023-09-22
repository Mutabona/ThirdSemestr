internal class Program
{
    private static void Main(string[] args)
    {
        var snegurochka = new SnowWoman("Kate", 19, -12, true);
        var secondLady = new SnowWoman();
        snegurochka.Snow();
        snegurochka.Shop();
        snegurochka.Combine();
        snegurochka.PrintFields();
        secondLady.PrintFields();
    }
}