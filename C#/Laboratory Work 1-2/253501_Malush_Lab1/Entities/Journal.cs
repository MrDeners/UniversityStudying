public class Event
{
    private HostelRoom room;
    private string department;
    private string description;

    public Event(HostelRoom room, string department, string description)
    {
        this.room = room;
        this.department = department;
        this.description = description;
    }

    public void GetInformation()
    {
        Console.WriteLine($"{department} - {description}");
    }

    public string GetDepartment()
    {
        return department;
    }

    public string GetDescription()
    {
        return description;
    }


    public void Add(string department, string description)
    {
        this.department = department;
        this.description = description;
    }
}

public class Journal
{
    public Journal(Hostel hostel)
    {
        hostel.ChangeRoomList += ChangeRoomListHandler;
        hostel.ChangeOwnerList += ChangeOwnerListHandler;
    }
    private MyCustomCollection<Event> Log = new();

    public void AddNewNote(Event newNote)
    {
        Log.Add(newNote);
    }

    public void GetAllLog()
    {
        foreach(Event i in Log)
        {
            i.GetInformation();
        }
    }

    public void ChangeRoomListHandler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", "Room's List was changed");
        Log.Add(newNote);
    }

    public void ChangeOwnerListHandler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", "Owner's List was changed");
        Log.Add(newNote);
    }
}