using System;
namespace _253501_Maliush_Lab._4
{
	public class Art
	{
		public string Name { get; set; }
		private int yearOfCreating;
		private bool isItHas;

		public Art(string name, int yearOfCreating, bool isItHas)
		{
			this.name = name;
			this.yearOfCreating = yearOfCreating;
			this.isItHas = isItHas;
		}

		public string GetName()
		{
			return name;
		}

		public int GetYearOfCreating()
		{
			return yearOfCreating;
		}

        public bool GetIsItHas()
        {
            return isItHas;
        }

        public void GetInformation()
        {
            Console.WriteLine($"{name} {yearOfCreating} {isItHas}");
        }
    }
}

