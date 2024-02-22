using System;
using System.Diagnostics;
using System.Threading;
using ClassLibrary;

namespace _253501_Maliush_Lab7;
public static class Program
{
    public static async Task Main()
    {
        var integralCalculator = new IntegralCalculator();

        //var TIntegralHighest = new Thread(() => integralCalculator.Calculate());

        //TIntegralHighest.Name = "TIntegral Higest";
        //TIntegralLowest.Name = "TIntegral Lowest";
        //TIntegralThird.Name = "TIntegral Third";
        //TIntegralFourth.Name = "TIntegral Fourth";
        //TIntegralFiveth.Name = "TIntegral Fiveth";

        integralCalculator.StepsComplited += progress => 
        {
            //string threadName = Thread.CurrentThread.Name;
            int threadID = Thread.CurrentThread.ManagedThreadId;
            //int threadID = Task.CurrentId.Value;
            short progressPercent = (short)(progress * 100); 
            var progressBar = new string("[");
            short numOfPart = (short)(progressPercent / 5 );
            if (numOfPart > 0) --numOfPart;

            for (int i = 0; i < numOfPart; i++)
            {
                progressBar += "=";
            }

            progressBar += ">";

            for (int i = 0; i < (20 - numOfPart-2); i++)
            {
                progressBar += " ";
            }

            progressBar += "]";
            //if (progressPercent == 99)
            Console.WriteLine($"[Thread]  " +
                $"[ID: {threadID}] : {progressBar} {progressPercent.ToString("R")}%");
        };

        integralCalculator.Result += (sender, e) =>
        {
            //string threadName = Thread.CurrentThread.Name;
            int threadID = Thread.CurrentThread.ManagedThreadId;
            Console.WriteLine($"[Thread]  " +
                $"[ID: {threadID}] was complited with result: {e.Result}   Elapsed time: {e.Time}");
        };

        var TIntegralHighest = Task.Run(integralCalculator.Calculate);
        var TIntegralLowest = Task.Run(integralCalculator.Calculate);
        var TIntegralThird = Task.Run(integralCalculator.Calculate);
        var TIntegralFourth = Task.Run(integralCalculator.Calculate);
        var TIntegralFiveth = Task.Run(integralCalculator.Calculate);

        await Task.WhenAll(
            TIntegralHighest, TIntegralLowest, TIntegralThird,
            TIntegralFourth, TIntegralFiveth);

        //TIntegralHighest.Priority = ThreadPriority.Highest;
        //TIntegralLowest.Priority = ThreadPriority.Lowest;
        //TIntegralHighest.Start();
        //TIntegralLowest.Start();
        //TIntegralThird.Start();
        //TIntegralFourth.Start();
        //TIntegralFiveth.Start();
    }
} 