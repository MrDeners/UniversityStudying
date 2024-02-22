public class HostelRoom : IClassicRoom
{
    private short number;
    private int price;
    private short amountDay;
    private string owner;
    private short amountOfDell;

    public HostelRoom()
    {
        amountDay = 0;
        amountOfDell = 0;
        owner = "empty";
    }

    public HostelRoom(short number, int price)
    {
        this.number = number;
        this.price = price;
        amountDay = 0;
        amountOfDell = 0;
        owner = "empty";
    }

    public short GetNumber()
    {
        return number;
    }

    public int GetPrice()
    {
        return price;
    }

    public string GetOwner()
    {
        return owner;
    }

    public short GetAmountOfDell()
    {
        return amountOfDell;
    }

    public void GetInformation()
    {
        Console.WriteLine("<======================>");
        Console.WriteLine($"Number of Room: {number}");
        Console.WriteLine($"Price per Day: {price}$");
        Console.WriteLine($"Current Owner: {owner}");
        Console.WriteLine("<======================>");
    }

    public void Registration(short amountDay, string owner)
    {
        this.amountDay = amountDay;
        this.owner = owner;
        amountOfDell++;
    }
}

