using System.Numerics;

public class Hostel : IHostelProcessing
{

    public event EventHandler ChangeRoomList;
    public event EventHandler ChangeOwnerList;
    public event EventHandler NewDell;

    private MyCustomCollection<HostelRoom> Rooms = new();
    private MyCustomCollection<string> Owners = new();

    public void AddNewRoom(HostelRoom newRoom)
    {
        Rooms.Add(newRoom);
        ChangeRoomList.Invoke(newRoom, EventArgs.Empty);
    }

    public void DeleteRoom(short i)
    {
        HostelRoom delRoom = Rooms[i];
        Rooms.Remove(delRoom);

        //HostelRoom delRoomForMyExceprion = new(30, 20);  //для теста исключения
        //Rooms.Remove(delRoomForMyExceprion);

        ChangeRoomList.Invoke(delRoom, EventArgs.Empty);
    }

    public void Dell(short number, short amountDay, string owner)
    {
        HostelRoom tempRoom;
        short i = 0;
        while (Rooms[i].GetNumber() != number)
        {
            i++;
            if (i == Rooms.Count)
            {
                Console.WriteLine("This room does not exist");
                return;
            }
        }
            tempRoom = Rooms[i];
            tempRoom.Registration(amountDay, owner);
            Console.WriteLine($"The cost of your stay will be {GetFullPrice(tempRoom.GetPrice(), amountDay)}$");
        Owners.Add(owner);
        ChangeOwnerList.Invoke(tempRoom, EventArgs.Empty);
        NewDell.Invoke(tempRoom, EventArgs.Empty);
    }

    public void OutputAllRooms()
    {
        foreach(HostelRoom i in Rooms)
        {
            i.GetInformation();
        }
    }

    public void OutputAllOwners()
    {
        foreach (string i in Owners)
        {
            Console.WriteLine($"{i}");
        }
    }

    public void OutputFreeRooms()
    {
        short fl = 0;
        short i = 0;
        while (i < Rooms.Count)
        {
            if (Rooms[i].GetOwner() == "empty")
            {
                Rooms[i].GetInformation();
                fl = 1;
            }

            i++;
        }

        if (fl == 0)
        {
            Console.WriteLine("There are no available rooms");
        }
    }

    public void GetTheMostPopularRoom()
    {
        HostelRoom tempRoom = Rooms[0];
        short i = 0;
        while (i < Rooms.Count)
        {
            if (tempRoom.GetAmountOfDell() < Rooms[i].GetAmountOfDell())
            {
                tempRoom = Rooms[i];
            }
            i++;
        }
        Console.WriteLine($"The most popular Room it's {tempRoom.GetNumber()} room: ");
        tempRoom.GetInformation();
    }

    public T GetFullPrice<T>(T Price, T AmountOfDay) where T : INumber<T>
    {
        T fullPrice = Price * AmountOfDay;
        return fullPrice; 
    }
}


