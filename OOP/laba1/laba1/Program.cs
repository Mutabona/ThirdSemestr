using System.Windows.Markup;

internal class Program
{
    private static void Main(string[] args)
    {
        var clients = BankClient.BankClientController.instance;
        int choice = 0;
        do {
            Console.WriteLine("1 - Add client");
            Console.WriteLine("2 - Print all clients");
            Console.WriteLine("3 - Process all clients");
            Console.WriteLine("0 - Leave");
            choice = Convert.ToInt32(Console.ReadLine());

            switch (choice) {
                case 1:
                    clients.AddClient();
                    break;
                case 2:
                    clients.PrintAllClients();
                    break;
                case 3:
                    clients.ProcessAllClients();
                    break;
            }
        } while(choice != 0);
    }
}

internal sealed class BankClient
{
    private readonly int id;
    private string surname;
    public string? Surname
    {
        get => surname;
        private set => surname = value ?? "";
    }

    private string name;
    public string? Name
    {
        get => name;
        private set => name = value ?? "";
    }

    private string patronomic;
    public string? Patronomic
    {
        get => patronomic;
        private set => patronomic = value ?? "";
    }

    private string city;
    public string? City
    {
        get => city;
        private set => city = value ?? "";
    }

    private string street;
    public string? Street
    {
        get => street;
        private set => street = value ?? "";
    }

    public int House { get; private set; }
    public int Flat { get; private set; }

    private BankClient(int Id)
    {
        id = Id;
        Console.Write("Surname: "); Surname = Console.ReadLine();
        Console.Write("Name: "); Name = Console.ReadLine();
        Console.Write("Patronomic: "); Patronomic = Console.ReadLine();
        Console.Write("City: "); City = Console.ReadLine();
        Console.Write("Street: "); Street = Console.ReadLine();
        Console.Write("House: "); House = Convert.ToInt32(Console.ReadLine());
        Console.Write("Flat: "); Flat = Convert.ToInt32(Console.ReadLine());
    }

    private void PrintClient()
    {
        Console.WriteLine("Id: " + id.ToString());
        Console.WriteLine("Surname: " + surname);
        Console.WriteLine("Name: " + name);
        Console.WriteLine("Patronomice " + patronomic);
        Console.WriteLine("City: " + city);
        Console.WriteLine("Street: " + street);
        Console.WriteLine("House: " + House.ToString());
        Console.WriteLine("Flat: " + Flat.ToString());
    }

    internal sealed class BankClientController
    {
        private static int lastId = 0;
        private List<BankClient> clients = new List<BankClient>();
        private BankClientController() {}
        public static readonly BankClientController instance = new BankClientController();

        public void AddClient()
        {
            lastId++;
            clients.Add(new BankClient(lastId));
        }

        public void PrintAllClients() {
            foreach (var client in clients) {
                client.PrintClient();
            }
        }

        public void ProcessAllClients() {
            foreach (var client in clients)
                if (client.House == client.Flat)
                    Console.WriteLine(client.Surname + " " + client.Name);
                else
                    Console.WriteLine("They don't match");
        }
    }
}