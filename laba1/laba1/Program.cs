internal class Program
{
    private static void Main(string[] args)
    {
        var clients = new List<BankClient>();
        int choice = 0;
        do {
            Console.WriteLine("1 - Add client");
            Console.WriteLine("2 - Print all clients");
            Console.WriteLine("3 - Process all clients");
            Console.WriteLine("0 - Leave");
            choice = Convert.ToInt32(Console.ReadLine());

            switch (choice) {
                case 1:
                    clients.Add(new BankClient());
                    break;
                case 2:
                    foreach (var client in clients) {
                        client.PrintClient();
                    }
                    break;
                case 3:
                    break;
            }
        } while(choice != 0);
    }
}

internal class BankClient {
    private static int lastId = 0;
    private readonly int id;

    private string surname;
    public string Surname { 
        get { return surname; } 
        set {
            try { surname = value; }
            catch {
                Console.WriteLine("Surname error");
                return;
            }       
        } 
    }

    private string name;
    public string Name {
        get { return name; }
        set {
            try { name = value; }
            catch {
                Console.WriteLine("Name error");
                return;
            }
        }
    }

    private string patronomic;
    public string Patronomic {
        get { return patronomic; }
        set {
            try { patronomic = value; }
            catch {
                Console.WriteLine("Patronomic error");
                return;
            }
        }
    }

    private string city;
    public string City {
        get { return city; }
        set {
            try { city = value; }
            catch {
                Console.WriteLine("City error");
                return;
            }
        }
    }

    private string street;
    public string Street {
        get { return street; }
        set {
            try { street = value; } 
            catch {
                Console.WriteLine("Street error");
                return;
            }
        }
    }

    private int house { get; set;}

    private int flat { get; set;}

    public BankClient() {
        lastId++;
        this.id = lastId;
        Console.Write("Surname: "); this.Surname = Console.ReadLine();
        Console.Write("Name: "); this.Name = Console.ReadLine();
        Console.Write("Patronomic: "); this.Patronomic = Console.ReadLine();
        Console.Write("City: "); this.City = Console.ReadLine();
        Console.Write("Street: "); this.Street = Console.ReadLine();
        Console.Write("House: "); this.house = Convert.ToInt32(Console.ReadLine());
        Console.Write("Flat: "); this.flat = Convert.ToInt32(Console.ReadLine());
    }

    public void PrintClient() {
        Console.WriteLine("Id: " + id.ToString());
        Console.WriteLine("Surname: " + surname);
        Console.WriteLine("Name: " + name);
        Console.WriteLine("Patronomice " + patronomic);
        Console.WriteLine("City: " + city);
        Console.WriteLine("Street: " + street);
        Console.WriteLine("House: " + house.ToString());
        Console.WriteLine("Flat: " + flat.ToString());
    }
}

public class BankClientFactory {
    private List<BankClient> clients = new List<BankClient>;
    private BankClientFactory() {}
    private static BankClientFactory instance;
    public static BankClientFactory Instance {
        get {
            if (instance == null) {
                instance = new BankClientFactory();
            }
            return instance;;
        }
    }

    public void AddClient() {
        clients.Add(new BankClient());
    }
}