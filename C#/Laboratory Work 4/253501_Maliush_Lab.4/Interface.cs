using System;
namespace _253501_Maliush_Lab._4
{
    interface IFileService<T>
    {
        IEnumerable<T> ReadFile(string fileName);
        void SaveData(IEnumerable<T> data, string fileName);
    }
}

