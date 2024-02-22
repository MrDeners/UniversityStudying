using System.Numerics;
using _253501_Maliush_Lab3.Entities;

public class Hostel : IHostelProcessing
{

    public event EventHandler ChangeRoomList;
    public event EventHandler ChangeOwnerList;
    public event EventHandler NewDell;
    public event EventHandler<EventEventArgs> AddNewNote;

    private Dictionary<int, HostelRoom> Rooms = new();
    private List<Owner> Owners = new();

    public Hostel()
    {
        //ChangeRoomList += ChangeRoomListHandler;
        //ChangeOwnerList += ChangeOwnerListHandler;
        //NewDell += NewDellHadler;
    }

    public void AddNewRoom(HostelRoom newRoom)
    {
        Rooms.Add(newRoom.GetNumber(), newRoom);
        ChangeRoomList?.Invoke(newRoom, EventArgs.Empty);
    }

    public void DeleteRoom(short i)
    {
        HostelRoom delRoom = Rooms[i];
        Rooms.Remove(delRoom.GetNumber());
        ChangeRoomList.Invoke(delRoom, EventArgs.Empty);
    }

    public void Dell(short number, short amountDay, string owner)
    {
        HostelRoom tempRoom;
            tempRoom = Rooms[number];
            tempRoom.Registration(amountDay, owner);
            Console.WriteLine($"The cost of your stay will be {GetFullPrice(tempRoom.GetPrice(), amountDay)}$");
        Owner newOwner = new(owner, tempRoom, GetFullPrice(tempRoom.GetPrice(), amountDay));
        Owners.Add(newOwner);
        ChangeOwnerList.Invoke(tempRoom, EventArgs.Empty);
        NewDell.Invoke(tempRoom, EventArgs.Empty);
    }

    public void OutputAllRooms()
    {
        foreach(KeyValuePair<int, HostelRoom> i in Rooms)
        {
            i.Value.GetInformation();
        }
    }

    public void OutputAllOwners()
    {
        foreach (Owner i in Owners)
        {
            Console.WriteLine($"{i.GetName()}");
        }
    }

    public void OutputFreeRooms()
    {
        foreach (KeyValuePair<int, HostelRoom> i in Rooms)
        {
            if (i.Value.GetOwner() == "empty")
            {
                i.Value.GetInformation();
            }
        }
    }

    public void GetTheMostPopularRoom()
    {
        HostelRoom tempRoom = Rooms.First().Value;
        foreach (KeyValuePair<int, HostelRoom> i in Rooms)
        {
            if (tempRoom.GetAmountOfDell() < i.Value.GetAmountOfDell()) tempRoom = i.Value;
        }
        Console.WriteLine($"The most popular Room it's {tempRoom.GetNumber()} room: ");
        tempRoom.GetInformation();
    }

    public T GetFullPrice<T>(T Price, T AmountOfDay) where T : INumber<T>
    {
        T fullPrice = Price * AmountOfDay;
        return fullPrice;
    }

    public void GetNumberOfRoomByPrice()
    {
        Dictionary<int, HostelRoom> SortedRooms = Rooms.OrderByDescending(x => x.Value.GetPrice())
            .ToDictionary(x => x.Key, x => x.Value);
        foreach(KeyValuePair<int, HostelRoom> i in SortedRooms)
        {
            Console.WriteLine($"Room number {i.Value.GetNumber()} has price - {i.Value.GetPrice()}$");
        }
    }

    public int GetAllRoomsFullPrice()
    {
        int FullPrice = Rooms.Sum(x => x.Value.GetPrice());
        return FullPrice;

    }

    public string GetTheRichestOwner()
    {
        Owner TheRichestOwner = Owners.OrderByDescending(x => x.GetAllPrice()).FirstOrDefault();
        return TheRichestOwner?.GetName();
    }

    public short GetTheNumOfOwnersOnFilterByPrice()
    {
        short NumOfOwners = 0;
        int threshold = 300;
        NumOfOwners = (short)Owners.Aggregate(0, (total, owner) => owner.GetAllPrice() > threshold ? total + 1 : total);
        return NumOfOwners;
    }

    public void GetListOfRoomsOnPriceGroops()
    {
        List<List<HostelRoom>> GroppedRooms = Rooms.GroupBy(x => x.Value.GetPrice())
            .Select(g => g.Select(x => x.Value).ToList())
            .ToList();
        foreach (List<HostelRoom> iList in GroppedRooms)
        {
            foreach (HostelRoom i in iList)
            {
                i.GetInformation();
            }
        }
    }

    public void ChangeRoomListHandler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", "Room's List was changed");
        AddNewNote.Invoke(this, new EventEventArgs(newNote));
    }

    public void ChangeOwnerListHandler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", "Owner's List was changed");
        AddNewNote.Invoke(this, new EventEventArgs(newNote));
    }

    public void NewDellHadler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", $"New Dell on Hostel - {room.GetOwner()}");
        AddNewNote.Invoke(this, new EventEventArgs(newNote));
    }
}


