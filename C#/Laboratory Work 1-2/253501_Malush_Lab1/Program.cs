using System;

namespace project
{
    public partial class Program
    {
        static void Main ()
        {
            Hostel hostel = new();
            Journal log = new(hostel);

            hostel.NewDell += (sender, e) =>
            {
                HostelRoom room = sender as HostelRoom;
                Event newDeel = new(room, "Hostel", "New Dell on Hostel");
                log.AddNewNote(newDeel);
            };

            hostel.AddNewRoom(new(1, 130));
            hostel.AddNewRoom(new(2, 230));
            hostel.AddNewRoom(new(3, 370));
            ProgramWork(ref hostel);
            
            log.GetAllLog();
        }
    }
}




