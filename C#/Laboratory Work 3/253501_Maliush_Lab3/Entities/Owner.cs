using System;
namespace _253501_Maliush_Lab3.Entities
{
	public class Owner
	{
		private string name;
        private List<HostelRoom> rooms;
		private int allPrice;

        public Owner(string name, HostelRoom room, int allPrice)
		{
			rooms = new();
            this.name = name;
			this.allPrice = allPrice;
            rooms.Add(room);
        }

		public void OwnerAdd(string name, HostelRoom room)
		{
			this.name = name;
			rooms.Add(room);
		}

		public string GetName()
		{
			return name;
		}

        public List<HostelRoom> GetRooms()
        {
            return rooms;
        }

		public int GetAllPrice()
		{
			return allPrice;
		}
    }
}

