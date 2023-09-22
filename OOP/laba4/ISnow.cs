internal interface ISnow {
    public abstract void Snow();
    public abstract void Combine();
}

internal sealed class ISnowImpl: ISnow {
    public int temperature;
    public bool isLoose;

    public ISnowImpl(int _temp = -10, bool _isLoose = true) {
        temperature = _temp;
        isLoose = _isLoose;
    }

    public void Snow() {
        Console.WriteLine("Snowing snowing snowing");
    }

    public void Combine() {
        Console.WriteLine("Snow combine");
    }
}