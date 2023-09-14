
internal class Program
{
    private static void Main(string[] args)
    {
        var clients = new List<bankClient>();
        int choice = 0;
        do {
            Console.WriteLine("1 - Add client");
            Console.WriteLine("2 - Print all clients");
            Console.WriteLine("3 - Process all clients");
            Console.WriteLine("0 - Leave");
            choice = Convert.ToInt32(Console.ReadLine());

            switch (choice) {
                case 1:
                    clients.Add(createClient(clients.Count + 1));
                    break;
                case 2:
                    printAllClients(clients);
                    break;
                case 3:
                    processAllClients(clients);
                    break;
            }
        } while(choice != 0);
    }

    private static bankClient createClient(int Id) {
        bankClient newClient;
        newClient.id = Id;
        Console.Write("Surname: "); newClient.surname = Console.ReadLine();
        Console.Write("Name: "); newClient.name = Console.ReadLine();
        Console.Write("Patronomic: "); newClient.patronomic = Console.ReadLine();
        Console.Write("City: "); newClient.city = Console.ReadLine();
        Console.Write("Street: "); newClient.street = Console.ReadLine();
        Console.Write("House: "); newClient.house = Convert.ToInt32(Console.ReadLine());
        Console.Write("Flat: "); newClient.flat = Convert.ToInt32(Console.ReadLine());
        return newClient;
    }

    private static void printClient(bankClient bankClient) {
        Console.WriteLine("Id: " + bankClient.id.ToString());
        Console.WriteLine("Surname: " + bankClient.surname);
        Console.WriteLine("Name: " + bankClient.name);
        Console.WriteLine("Patronomice " + bankClient.patronomic);
        Console.WriteLine("City: " + bankClient.city);
        Console.WriteLine("Street: " + bankClient.street);
        Console.WriteLine("House: " + bankClient.house.ToString());
        Console.WriteLine("Flat: " + bankClient.flat.ToString());
    }

    private static void printAllClients(IList<bankClient> clients) {
        foreach (var client in clients)
            printClient(client);
    }

    private static void processAllClients(IList<bankClient> clients) {
        foreach (var client in clients)
                if (client.house == client.flat)
                    Console.WriteLine(client.surname + " " + client.name);
                else
                    Console.WriteLine("They don't match");
    }

    private struct bankClient {
        public int id;
        public string surname;
        public string name;
        public string patronomic;
        public string city;
        public string street;
        public int house;
        public int flat;
    }
}

