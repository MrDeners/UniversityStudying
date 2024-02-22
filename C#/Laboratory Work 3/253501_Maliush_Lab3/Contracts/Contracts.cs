using System.Numerics;

interface IHostelProcessing
{
    public void Dell(short number, short amountDay, string owner);
    void AddNewRoom(HostelRoom newRoom);
    public void OutputAllRooms();
    public void OutputFreeRooms();
    public void GetTheMostPopularRoom();
    public T GetFullPrice<T>(T Price, T AmountOfDay) where T : INumber<T>;
}

interface IClassicRoom
{
    public short GetNumber();
    public int GetPrice();
    public string GetOwner();
    public short GetAmountOfDell();
    public void GetInformation();
    public void Registration(short amountDay, string owner);
}