using ClassLibrary;
using System.Diagnostics;

public class IntegralCalculator
{
    private const double Step = 0.0001; //0.00000001

    private const int Delay = 100000;

    public event EventHandler<doubleAndDouble> Result;
    public event Action<double> StepsComplited;

    private SemaphoreSlim semaphore = new(3);
    //private object lockObject = new();

    public async Task<double> Calculate()
    {
        await semaphore.WaitAsync();
        try
        {
            //lock(lockObject)
            //{ 
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            double result = 0;
            long i = 0;
            for (double x = 0; x <= 1; x += Step)
            {
                result += Math.Sin(x) * Step;
                DelayExecution();
                StepsComplited?.Invoke(x);
            }

            stopwatch.Stop();
            TimeSpan ts = stopwatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                ts.Hours, ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            Result?.Invoke(this, new doubleAndDouble(result, elapsedTime));
            return result;
            //}
        }

        finally
        {
            semaphore.Release();
        }
    }

    private void DelayExecution()
    {
        double delayResult = 0;
        for (int i = 0; i < Delay; i++)
        {
            delayResult += i * i;
        }
    }
}
