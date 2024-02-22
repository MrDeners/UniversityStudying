using System.Text;
using System.Text.Json;

namespace Domain
{
    public class StreamService<T> where T : new()
    {
        private SemaphoreSlim semaphore = new(1);

        public async Task WriteToStreamAsync(Stream stream,
            IEnumerable<T> data, IProgress<string> progress, IProgress<ProgressReport> progressReport)
        {
            await semaphore.WaitAsync();

            try
            {
                using StreamWriter writer = new(stream, Encoding.UTF8, 1024, true);

                progress.Report($"[Thread]  {Thread.CurrentThread.ManagedThreadId}      " +
                    $"Start write to Stream [{stream}]");
                short current = 1;
                short total = 10;
                short counter = 0;
                short count = 0;
                foreach (T i in data)
                {
                    ++count;
                    var type = i.GetType();
                    var fields = type.GetProperties();
                    foreach (var field in fields)
                    {
                        var fieldValue = field.GetValue(i);
                        await writer.WriteAsync(fieldValue.ToString());
                        if (counter != fields.Length-1)
                        {
                            await writer.WriteAsync(">?");
                            ++counter;
                        }
                        else
                           counter = 0;

                    }
                    await writer.WriteLineAsync();
                    //progress.Report($"[Thread]  {Thread.CurrentThread.ManagedThreadId}      " +
                    //$"Object {count} was written to Stream [{stream}]");
                    progressReport.Report(new ProgressReport
                    {
                        ThreadId = Thread.CurrentThread.ManagedThreadId,
                        PercentageComplete = (double)current / total * 100
                    });
                    ++current;
                    Thread.Sleep(200);
                }
            }

            finally
            {
                semaphore.Release();
            }
        }

        public async Task CopyFromStreamAsync(Stream stream, string
            filename, IProgress<string> progress, IProgress<ProgressReport> progressReport)
        {
            await semaphore.WaitAsync();

            await JsonSerializer.SerializeAsync(File.OpenWrite(filename), stream);

            try
            {
                short current = 1;
                short total = 10;
                string line;
                using StreamWriter writer = new(filename);
                using StreamReader reader = new(stream, true);
                progress.Report($"[Thread]  {Thread.CurrentThread.ManagedThreadId}      " +
                    $"Start write to File ''{filename}''");

                stream.Position = 0;
                while ((line = await reader.ReadLineAsync()) != null)
                {
                    await writer.WriteLineAsync(line);
                    //progress.Report($"[Thread]  {Thread.CurrentThread.ManagedThreadId}      " +
                    //$"Line ''{line}'' was written to File ''{filename}''");
                    progressReport.Report(new ProgressReport
                    {
                        ThreadId = Thread.CurrentThread.ManagedThreadId,
                        PercentageComplete = (double)current / total * 100
                    });
                    ++current;
                    Thread.Sleep(200);
                }
            }

            finally
            {
                semaphore.Release();
            }
        }

        public async Task<int> GetStatisticsAsync(string fileName,
            Func<T, bool> filter)
        {
            int counter = 0;
            Task<List<T>> taskData = GetCollectionFromFile(fileName);
            List<T> data = await taskData;
            foreach (T i in data)
            {
                if (filter(i))
                    ++counter;
            }
            return counter;
        }

        private async Task<List<T>> GetCollectionFromFile(string fileName)
        {
            List<T> data = new();
            string line;
            var type = typeof(T);
            var fields = type.GetProperties();
            using StreamReader reader = new(fileName);
            while ((line = await reader.ReadLineAsync()) != null)
            {
                T example = new();
                List<string> elementsOfLine = line.Split(">?").ToList();
                foreach (var i in fields)
                {
                    var typeOfField = i.PropertyType;
                    i.SetValue(example,
                        Convert.ChangeType(elementsOfLine.FirstOrDefault(), typeOfField));
                    elementsOfLine.RemoveAt(0);
                }
                data.Add(example);
            }
            return data;
        }
    }
}

