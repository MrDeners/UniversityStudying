namespace project
{
    public partial class Program
    {
        public static void OutputMenu()
        {
            Console.WriteLine("<======================>");
            Console.WriteLine("1: Registration");
            Console.WriteLine("2: Get information about all Rooms and them Price");
            Console.WriteLine("3: Get information about free Rooms");
            Console.WriteLine("4: Get information about The Most Popular Room");
            Console.WriteLine("5: Close the Program");
            Console.WriteLine("========================");
            Console.WriteLine("6: ***Open AdminMenu***");
            Console.WriteLine("<======================>");
            Console.Write("Please, type number of your choice: ");
        }

        public static void GetAnswer(ref byte refOperand, byte FirstLimit, byte LastLimit)
        {
            bool successfully = false;
            while (!successfully)
            {
                try
                {
                    refOperand = Convert.ToByte(Console.ReadLine());
                    if (refOperand < FirstLimit || refOperand > LastLimit)
                        throw new ArgumentOutOfRangeException();
                    successfully = true;
                }
                catch (FormatException)
                {
                    Console.Write("You input not number! Try now: ");
                }
                catch (ArgumentOutOfRangeException)
                {
                    Console.Write($"You input wrong number! Input number on limits {FirstLimit} <= X <= {LastLimit} Try now: ");
                }
            }
        }

        private static void Processing(ref bool isContinue, Hostel hostel, byte operand)
        {
            switch (operand)
            {
                case 1:
                    NewDeelWithConsole(ref hostel);
                    break;
                case 2:
                    hostel.OutputAllRooms();
                    break;
                case 3:
                    hostel.OutputFreeRooms();
                    break;
                case 4:
                    hostel.GetTheMostPopularRoom();
                    break;
                case 5:
                    isContinue = false;
                    break;
                case 6:
                    OutputAdminMenu();
                    GetAnswer(ref operand, 1, 3);
                    switch (operand)
                    {
                        case 1:
                            AddingRoom(hostel);
                            break;
                        case 2:
                            DeletingRoom(hostel);
                            break;
                        case 3:
                            break;
                    }
                    break;
            }
        }

        private static void AddingRoom(Hostel hostel)
        {
            Console.Write("Input the number of new Room: ");
            short number = Convert.ToInt16(Console.ReadLine()); ;
            Console.Write("Enter the price of new Room: ");
            int price = Convert.ToInt16(Console.ReadLine());
            HostelRoom newRoom = new(number, price);
            hostel.AddNewRoom(newRoom);
        }

        private static void DeletingRoom(Hostel hostel)
        {
            Console.Write("Input the number of deleting Room (On List): ");
            short number = Convert.ToInt16(Console.ReadLine()); ;
            hostel.DeleteRoom(number);
        }

        private static void NewDeelWithConsole(ref Hostel hostel)
        {
            Console.Write("Input the number of you're future room: ");
            short number = Convert.ToInt16(Console.ReadLine());;
            Console.Write("Enter the number of days you are going to live: ");
            short amountDay = Convert.ToInt16(Console.ReadLine());
            Console.Write("Enter you're name: ");
            string owner = Console.ReadLine();
            hostel.Dell(number, amountDay, owner);
        } 

        public static void CheckForContinuation(ref bool IsContinue)
        {
            byte operand = 0;
            Console.WriteLine("Maby you want to continue?");
            Console.WriteLine("1. Yes, continue");
            Console.WriteLine("2. No, close the Program");
            Console.Write("Please, type number of your choice: ");
            GetAnswer(ref operand, 1, 2);
            if (operand == 2) IsContinue = false;
        }

        public static void OutputAdminMenu()
        {
            Console.WriteLine("<======================>");
            Console.WriteLine("1: Add new Room");
            Console.WriteLine("2: Delet Room");
            Console.WriteLine("3: Returt to Main menu");
            Console.WriteLine("<======================>");
            Console.Write("Please, type number of your choice: ");
        }


        private static void ProgramWork(ref Hostel hostel)
        {
            byte operand = 0;
            bool IsContinue = true;

            while (IsContinue == true)
            {
                OutputMenu();
                GetAnswer(ref operand, 1, 6);
                Processing(ref IsContinue, hostel, operand);
                if (IsContinue == false) break;
                CheckForContinuation(ref IsContinue);
            }
        }
    }
}