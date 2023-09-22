internal sealed class SnowWoman: ISnow, IWoman {
    private ISnowImpl ISnowImpl;
    private IWomanImpl IWomanImpl;

    public string name {
        get { return IWomanImpl.name; }
        set { IWomanImpl.name = value; }
    }

    public int age {
        get { return IWomanImpl.age; }
        set { IWomanImpl.age = value; }
    }

    public int temperature {
        get { return ISnowImpl.temperature; }
        set { ISnowImpl.temperature = value; }
    }

    public bool isLoose {
        get { return ISnowImpl.isLoose; }
        set { ISnowImpl.isLoose = value; }
    }

    public SnowWoman(string _name = "Unnamed", int _age = 18, int _temp = -10, bool _isLoose = true) {
        IWomanImpl = new IWomanImpl(_name, _age);
        ISnowImpl = new ISnowImpl(_temp, _isLoose);
    }

    public void Snow() {
        ISnowImpl.Snow();
    }

    public void Shop() {
        IWomanImpl.Shop();
    }

    public void Combine() {
        ISnowImpl.Combine();
        IWomanImpl.Combine();
    }

    public void PrintFields() {
        Console.WriteLine("Name: " + name);
        Console.WriteLine("Age: " + age.ToString());
        Console.WriteLine("Temperature: " + temperature.ToString());
        Console.WriteLine("Is loose: " + isLoose.ToString());
    }
}