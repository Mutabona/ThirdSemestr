internal interface IWoman {
    public abstract void Shop();
    public abstract void Combine();
}

internal sealed class IWomanImpl: IWoman {

    public string name;
    public int age;

    public IWomanImpl(string _name = "Unnamed", int _age = 0) {
        name = _name;
        age = _age;
    }

    public void Shop() {
        Console.WriteLine("Shop shop shop");
    }

    public void Combine() {
        Console.WriteLine("Woman combine");
    }
}