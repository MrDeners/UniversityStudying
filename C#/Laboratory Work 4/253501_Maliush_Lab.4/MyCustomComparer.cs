using System;
namespace _253501_Maliush_Lab._4
{
	public class MyCustomComparer : IComparer<Art>
	{
        public int Compare(Art? x, Art? y)
        {
            string FirstName = x.GetName();
            string SecondName = y.GetName();

            short Length = (short)FirstName.Length;
            if (SecondName.Length > Length) Length = (short)SecondName.Length;

            for (short i = 0; i < Length; i++)
            {
                if (FirstName[i] != SecondName[i]) return FirstName[i] < SecondName[i] ? -1 : 1;
            }
            return 0;
        }
    }
}

