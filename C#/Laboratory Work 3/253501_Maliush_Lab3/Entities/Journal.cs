using System.Reflection;

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
        hostel.AddNewNote += AddNewNoteHandler;
        //hostel.ChangeRoomList += ChangeRoomListHandler;
        //hostel.ChangeOwnerList += ChangeOwnerListHandler;
        //hostel.NewDell += NewDellHadler;
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

    public void AddNewNoteHandler(object sender, EventEventArgs e)
    {
        Event newEvent = e.Event;
        AddNewNote(newEvent);
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

    public void NewDellHadler(object sender, EventArgs e)
    {
        var room = sender as HostelRoom;
        Event newNote = new(room, "Hostel", "New Dell on Hostel");
        Log.Add(newNote);
    }
}

public class EventEventArgs : EventArgs
{
    private readonly Event newEvent;

    public EventEventArgs(Event newEvent)
    {
        this.newEvent = newEvent;
    }

    public Event Event
    {
        get { return newEvent; }
    }
}