using System;

namespace project
{
    public partial class Program
    {
        static void Main ()
        {
            Hostel hostel = new();
            Journal log = new(hostel);

            hostel.NewDell += log.NewDellHadler; 

            hostel.AddNewRoom(new(1, 130));
            hostel.AddNewRoom(new(2, 230));
            hostel.AddNewRoom(new(3, 370));
            hostel.AddNewRoom(new(4, 130));
            hostel.AddNewRoom(new(5, 230));
            hostel.AddNewRoom(new(6, 370));
            ProgramWork(ref hostel);
            
            log.GetAllLog();




            hostel.GetNumberOfRoomByPrice();
            Console.WriteLine($"Full price of All Roooms - {hostel.GetAllRoomsFullPrice()}$");
            Console.WriteLine($"The richest owner at our Hostel - {hostel.GetTheRichestOwner()}");
            Console.WriteLine($"The number of users on good price - {hostel.GetTheNumOfOwnersOnFilterByPrice()}");
            hostel.GetListOfRoomsOnPriceGroops();
        }
    }
}




