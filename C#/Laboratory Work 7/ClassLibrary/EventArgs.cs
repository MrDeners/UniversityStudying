using System;
using System.Diagnostics;

namespace ClassLibrary
{
	public class doubleAndDouble : EventArgs
	{
        public double Result { get; set; }
        public string Time { get; set; }
        public doubleAndDouble(double result, string time)
		{
            Result = result;
            Time = time;
        }
	}
}